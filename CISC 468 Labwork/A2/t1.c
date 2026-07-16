#include <stdio.h>
#include <openssl/bn.h>

int main() {

BN_CTX *ctx = BN_CTX_new();

BIGNUM *p = BN_new();
BIGNUM *q = BN_new();
BIGNUM *e = BN_new();
BIGNUM *n = BN_new();

BN_hex2bn(&p, "5adb09bdbee704d048da9");
BN_hex2bn(&q, "14738741a1260adf78815");
BN_hex2bn(&e, "10001");

BN_mul(n, p, q, ctx);

printf("n length: %d\n", BN_num_bits(n));

// p2

BIGNUM *d = BN_new();
BIGNUM *phi = BN_new();
BN_sub_word(q, 1);
BN_sub_word(p, 1);
BN_mul(phi, p, q, ctx);

BN_mod_inverse(d, e, phi, ctx);

printf("private key d: %s\n", BN_bn2hex(d));

}
