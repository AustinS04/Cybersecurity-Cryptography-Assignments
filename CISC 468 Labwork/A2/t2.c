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

// e initialized and n calculated above

BIGNUM *m = BN_new();
BIGNUM *result = BN_new();

BN_hex2bn(&m, "693c3363727970746f");
BN_mod_exp(result, m, e, n, ctx);

printf("ciphertext: %s\n", BN_bn2hex(result));

}
