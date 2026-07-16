#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/conf.h>

int decrypt(unsigned char *ciphertext, int ciphertext_len,
            unsigned char *key, unsigned char *iv,
            unsigned char *plaintext) {
    int len;
    int plaintext_len;
    EVP_CIPHER_CTX *ctx;

    if(!(ctx = EVP_CIPHER_CTX_new())) {
        return -1;
    }

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        return -1; // initialization failed
    }

    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    plaintext_len = len;

    // Finalize decryption; check for padding errors
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    plaintext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}

int is_printable_ascii(const unsigned char *text, int length) {
    for(int i = 0; i < length; i++) {
        if(text[i] < 32 || text[i] > 126) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    time_t start, end;
    start = time(NULL);

    const char *cipher_hex = "2a94d3a3df0a72b3535c1bbcd873f09f5f9dd18d68d240e662190bb3627720498faa86b2cc0ff0d6cf8334a279d482b8";
    const char *iv_hex = "aabbccddeeff00998877665544332211";

    size_t cipher_len = strlen(cipher_hex)/2;
    unsigned char *cipher = malloc(cipher_len);
    size_t iv_len = strlen(iv_hex)/2;
    unsigned char *iv = malloc(iv_len);

    for(int i = 0; i < cipher_len; i++) {
        sscanf(cipher_hex + 2*i, "%2hhx", &cipher[i]);
    }

    for(int i = 0; i < iv_len; i++) {
        sscanf(iv_hex + 2*i, "%2hhx", &iv[i]);
    }

    FILE *dict = fopen("/usr/share/dict/words", "r");
    if (!dict) { perror("fopen"); free(iv); free(cipher); return 1; }

    char **words = NULL;
    size_t num_words = 0;
    char line[256];

    while (fgets(line, sizeof(line), dict)) {
        line[strcspn(line, "\r\n")] = 0; // strip newline
        if (strlen(line) > 0 && strlen(line) <= 15) {
            words = realloc(words, (num_words + 1) * sizeof(char *));
            words[num_words] = strdup(line);
            num_words++;
        }
    }
    fclose(dict);

    size_t *word_lengths = malloc(num_words * sizeof(size_t));
    for (size_t i = 0; i < num_words; i++) {
        word_lengths[i] = strlen(words[i]);
    }

    unsigned char decryptedtext[128];
    unsigned char key[17] = {0};

    for (size_t i = 0; i < num_words; i++){
        for (size_t j = 0; j < num_words; j++){
            size_t len1 = word_lengths[i];
            size_t len2 = word_lengths[j];
            if (len1 + len2 > 15) continue;

            memset(key, 0, 16);
            memcpy(key, words[i], len1);
            memcpy(key+len1, words[j], len2);
            for(int k = 0; k < 16 - (len1+len2); k++) key[len1+len2+k] = '#';

            int decrypted_len = decrypt(cipher, cipher_len, key, iv, decryptedtext);

            if (decrypted_len > 0 && is_printable_ascii(decryptedtext, decrypted_len)) {
                printf("Found a word!\n");
                printf("Key (hex): ");
                for(int k = 0; k < 16; k++) {
                    printf("%02x", key[k]);
                }
                printf("\n");

                printf("Plaintext: ");
                for(int k = 0; k < decrypted_len; k++) {
                    printf("%c", decryptedtext[k]);
                }
                printf("\n");
                }
        } 
    }

    end = time(NULL);
    printf("Time taken: %ld seconds\n", end - start);
    return 0;
}
