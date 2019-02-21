#include <check.h>
#include "test_main.h"
// run suite
int main(void)
{
    int number_failed;
    SRunner *sr = srunner_create(cipher_address());
    srunner_add_suite(sr, cipher_bitcoin());
    // srunner_add_suite(sr, cipher_testsuite());
    srunner_add_suite(sr, cipher_crypto());
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    sr = NULL;
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}