#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/conf.h>

int encrypt(unsigned char *plaintext, int plaintext_len,
	unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
	
	int len;
	int ciphertext_len;
	EVP_CIPHER_CTX *ctx;

	if(!(ctx = EVP_CIPHER_CTX_new())) {
		return -1;
	}

	if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) {
		EVP_CIPHER_CTX_free(ctx);
		return -1;
	}

	if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
		EVP_CIPHER_CTX_free(ctx);
		return -1;
	}

	ciphertext_len = len;

	if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) { 
		EVP_CIPHER_CTX_free(ctx);
		return -1;
	}

	ciphertext_len += len;
	EVP_CIPHER_CTX_free(ctx);
	return ciphertext_len;

}

void hex_to_bytes(const char *hex, unsigned char *out) {
	size_t len = strlen(hex);
	for (size_t i=0; i<len/2; i++) {
	sscanf(hex + 2*i, "%2hhx", &out[i]);
	}
}

void generate_key(unsigned char *key, int seed) {
	srand(seed);
	for (int i=0; i<16; i++) {
	key[i] = rand()%256;
	}
}

int main(void) {
	unsigned char *plaintext = "255044462d312e350a25bff7a2fe0a33";
	unsigned char *iv = "6f6d6567616c756c3132333435363738";
	unsigned char *desired_ciphertext = "b644d7961944854b655f40caadb30eda";

	unsigned char plaintext_bytes[16];
	unsigned char desired_bytes[16];
	unsigned char iv_bytes[16];
	unsigned char key_bytes[16];

	hex_to_bytes(plaintext, plaintext_bytes);
	hex_to_bytes(iv, iv_bytes);
	hex_to_bytes(desired_ciphertext, desired_bytes);

	

	unsigned char new_ciphertext[128];

	int start_time = 1767628800;
	int end_time = 1767762000;
	unsigned char key[16];

	for (int i=start_time; i<end_time; i++) {
	generate_key(key, i); 
	int encrypted_len = encrypt(plaintext_bytes, sizeof(plaintext_bytes), key, iv_bytes, new_ciphertext);
	
	if (memcmp(new_ciphertext, desired_bytes, 16)==0) {
	printf("Found seed! Seed = %d\n", i);
}
}
}
