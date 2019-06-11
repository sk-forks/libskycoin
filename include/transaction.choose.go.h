/**
 * Skycoin transaction.
 *
 * Instances of this struct are included in blocks.
 */
typedef struct {
    cipher__SHA256 Hash;     ///< Hash of underlying UxOut.
    GoUint64_ BkSeq;         ///< Block height corresponding to the
                             ///< moment balance calculation is performed at.
    cipher__Address Address; ///< Account holder address.
    GoUint64_ Coins;         ///< Coins amount (e.g. in SKY).
    GoUint64_ Hours;         ///< Balance of Coin Hours generated by underlying UxOut, depending on UxOut's head time.
    GoUint64_ InitialHours;
    cipher__SHA256 SrcTransaction;
} transaction__UxBalance;
