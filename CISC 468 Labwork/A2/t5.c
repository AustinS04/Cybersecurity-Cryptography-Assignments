#include <stdio.h>
#include <openssl/bn.h>

int main() {

BN_CTX *ctx = BN_CTX_new();

BIGNUM *e = BN_new();
BIGNUM *n = BN_new();
BIGNUM *sig = BN_new();

BN_hex2bn(&e, "10001");
BN_hex2bn(&n, "ae1cd4dc432798d933779fbd46c6e1247f0cf1233595113aa51b450f18116115");
BN_hex2bn(&sig, "643d6f34902d9c7ec90cb0b2bca36c47fa37165c0005cab026c0542cbdb6803f");

BIGNUM *plain = BN_new();
BN_mod_exp(plain, sig, e, n, ctx);

printf("signature: %s\n", BN_bn2hex(sig));
printf("plain    : %s\n", BN_bn2hex(plain));

}
