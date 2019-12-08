
![](https://repository-images.githubusercontent.com/165332391/de95dc00-7cec-11e9-8fcb-d42fbd8e3577)

# Skycoin C library

[![Build Status](https://travis-ci.com/fibercrypto/libskycoin.svg)](https://travis-ci.com/fibercrypto/libskycoin)

Skycoin C library (a.k.a `libskycoin`) exports the Skycoin API to DApps using the C programming language.
It is also the foundation to build client libraries for other programming languages.

## Links

* [skycoin.net](https://www.skycoin.net)
* [Skycoin Blog](https://www.skycoin.net/blog)
* [Skycoin Docs](https://www.skycoin.net/docs)
* [Skycoin Blockchain Explorer](https://explorer.skycoin.net)
* [Skycoin Development Telegram Channel](https://t.me/skycoindev)
* [Skycoin Github Wiki](https://github.com/SkycoinProject/skycoin/wiki)

## Subprojects

The Skycoin C library is made of the following components

- `lib/cgo`     : C wrappers for the Skycoin core API
- `lib/swig`    : SWIG interfaces to generate wrappers around the Skycoin core API for other programming languages
- `lib/swagger` : Swagger specifications for generating REST API clients
- `lib/curl`    : C REST client for the Skycoin HTTP API. Generated by [openapi-generator](https://github.com/OpenAPITools/openapi-generator). Powered by [libcurl](https://curl.haxx.se/libcurl/c/).

Consult respective `README` files for further details.

<!-- MarkdownTOC levels="1,2,3,4,5" autolink="true" bracket="round" -->
- [Make rules](#make-rules)
- [Development setup](#development-setup)
  - [Running tests](#running-tests)
  - [Releases](#releases)
    - [Update the version](#update-the-version)
    - [Pre-release testing](#pre-release-testing)
    - [Creating release builds](#creating-release-builds)
<!-- /MarkdownTOC -->

## Make Rules

All these make rules require skycoin to be a git submodule of libskycoin

|Target                        |Help|
| :-------------               | :----------: | 
|build-libc-static             |Build libskycoin C static library|
|build-libc-shared             |Build libskycoin C shared library|
|build                         |Build all C libraries
|build-libc                    |Build libskycoin C client libraries|
|build-skyapi                  |Build skyapi(libcurl based) library|
|test                          |Run all test for libskycoin|
|test-libc                     |Run tests for libskycoin C client library|
|test-skyapi                   |Run test for skyapi(libcurl based) library|
|docs                          |Generate documentation for all libraries|
|docs-libc                     |Generate libskycoin documentation|
|docs-skyapi                   |Generate SkyApi (libcurl) documentation|
|lint                          |Run linters. Use make install-linters first.|
|check                         |Run tests and linters|
|install-deps                  |Install deps for libc and skyapi|
|install-deps-libc             |Install deps for libc|
|install-deps-skyapi           |Install skyapi(libcurl based) library.|  
|install-linters               |Install linters|
|format                        |Formats the code. Must have goimports installed (use make install-linters).|
|clean                         |Clean all files generated by libraries(libcurl based and libc)|
|clean-libc                    |Clean files generated by libc|
|clean-skyapi                  |Clean files generated by skyapi| 

## Development setup

### Running tests

```sh
$ make test-libc
```

### Releases

#### Update the version

0. If the `master` branch has commits that are not in `develop` (e.g. due to a hotfix applied to `master`), merge `master` into `develop` (and fix any build or test failures)
0. Switch to a new release branch named `release-X.Y.Z` for preparing the release.
0. If the release process needs modifications, edit these steps before moving forward
0. Ensure that the submodule at `vendor/github.com/SkycoinProject/skycoin` is in sync with respect to the corresponding tag in https://github.com/SkycoinProject/skycoin repository.
0. Update `CHANGELOG.md`: move the "unreleased" changes to the version and add the date.
0. Run `make docs` to regenerate documentation for all libraries and ensure they ar up-to-date.
0. Follow the steps in [pre-release testing](#pre-release-testing)
0. Make a PR merging the release branch into `master`
0. Review the PR and merge it
0. Tag the `master` branch with the version number. Version tags start with `v`, e.g. `v0.20.0`. Sign the tag. If you have your GPG key in github, creating a release on the Github website will automatically tag the release. It can be tagged from the command line with `git tag -as v0.20.0 $COMMIT_ID`, but Github will not recognize it as a "release".
0. Release builds are created and uploaded by travis. To do it manually, checkout the master branch and make release.
0. Merge changes in `master` back into `develop` branch to start working towards next stable version.

#### Pre-release testing

Perform these actions before releasing:

```sh
make check
```
#### Release signing

Releases are signed with this PGP key:

`0x5801631BD27C7874`

The fingerprint for this key is:

```
pub   ed25519 2017-09-01 [SC] [expires: 2023-03-18]
      10A7 22B7 6F2F FE7B D238  0222 5801 631B D27C 7874
uid                      GZ-C SKYCOIN <token@protonmail.com>
sub   cv25519 2017-09-01 [E] [expires: 2023-03-18]
```

Keybase.io account: https://keybase.io/gzc 

##### Alternative signing keys:

Keybase.io account: https://keybase.io/olemis

The fingerprint for this key is:

```
pub   rsa4096 2019-01-17 [SC] [expires: 2024-01-16]
uid           Olemis Lang <olemis@simelo.tech>
sub   rsa4096 2019-01-17 [E] [expires: 2024-01-16]
```

Follow the [Tor Project's instructions for verifying signatures](https://www.torproject.org/docs/verifying-signatures.html.en).

If you can't or don't want to import the keys from a keyserver, the signing key is available in the repo: [gz-c.asc](gz-c.asc).

Releases and their signatures can be found on the [releases page](https://github.com/SkycoinProject/skycoin/releases).

Instructions for generating a PGP key, publishing it, signing the tags and binaries:
https://gist.github.com/gz-c/de3f9c43343b2f1a27c640fe529b067c

## Development

We have two branches: `master` and `develop`.

- `develop` is the default branch and will always have the latest code.
  The submodule at `gopath/src/github.com/SkycoinProject/skycoin` has to be
  in sync with `SkycoinProject/skycoin` `develop` branch.
- `master` will always be equal to the current stable release on the website, and should correspond with the latest release tag.
  The submodule at `gopath/src/github.com/SkycoinProject/skycoin` has to be
  in sync with `SkycoinProject/skycoin` `master` branch.

Separate stable development branches will be created to work on releases for supporting the
most recent stable version of Skycoin. The name of these branches should be the Skycoin
major and minor version numbers followed by `dev` suffix e.g. `0.25dev`.
These branches may be forked out of either `master` or `develop` branches, and 
the submodule at `gopath/src/github.com/SkycoinProject/skycoin` has to be
in sync with the corresponding tag of `SkycoinProject/skycoin` official repository.

Stable development branches are created most of the time for the following reasons:

- A Skycoin release increasing [patch version number](https://semver.org/).
- Enhanced support and bug fixes for a version of the library compiled against an
  stable version of Skycoin
- Backporting useful features added in `develop`.

### General development guidelines

The following rules are enforced

- Contributions must comply to the development guidelines documented in the [Skycoin wiki](https://github.com/SkycoinProject/skycoin/wiki).
- C / C++ code must comply to the [Bitcoin C coding style](https://github.com/bitcoin/bitcoin/blob/master/doc/developer-notes.md#coding-style-c) (enforced by `clang-format`).

### SkyApi libcurl client for Skycoin REST API

This wrapper is auto-generated by `openapi-generator` directly from [Skycoin REST API code](https://github.com/SkycoinProject/skycoin/tree/master/src/api).

For further instructions see [Autogenerated documentation](./lib/curl/README.md).

### Doxygen comment syntax

If you want to continue with `the doxygen way`(we recommend it) of coding and document functions, structs, and functions, you should follow the specifications found in the [Doxygen official site](http://www.doxygen.nl/manual/docblocks.html).

An example of documentation using `doxygen` is the next:

```c
/**
 * Addresses of Bitcoin accounts
 */
typedef struct {
    GoUint8_ Version;      ///< Address version identifier.
                           ///< Used to differentiate testnet
                           ///< vs mainnet addresses, for instance.
    cipher__Ripemd160 Key; ///< Address hash identifier.
} cipher__BitcoinAddress;
```
This code example can be found at `include/cipher.bitcoin.go.h`.

Inside `/* */`  we found struct documentation, meanwhile `//<` symbol is used to describe fields of the struct.

After that, run `make docs` for a new docs generation. You can found the api documentation at `docs/libc` folder.

