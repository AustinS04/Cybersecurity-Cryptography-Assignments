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

BIGNUM *d = BN_new();
BIGNUM *phi = BN_new();
BN_sub_word(q, 1);
BN_sub_word(p, 1);
BN_mul(phi, p, q, ctx);
BN_mod_inverse(d, e, phi, ctx);


// d and n are same values as previously calculated
BIGNUM *cipher = BN_new();
BN_hex2bn(&cipher, "12e6c403952e461afd626e2c81d7b53d0cfe043f3");

BIGNUM *result = BN_new();

BN_mod_exp(result, cipher, d, n, ctx);

printf("plaintext: %s\n", BN_bn2hex(result));

}
