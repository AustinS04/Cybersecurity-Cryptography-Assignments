#include <stdlib.h>
#include <stdio.h>
#define LEN 32 // 128 bits

int main(void){
unsigned char *key = (unsigned char *) malloc(sizeof(unsigned char)*LEN);
FILE* random = fopen("/dev/urandom", "r");
fread(key, sizeof(unsigned char)*LEN, 1, random);

for (int i = 0; i < LEN; i++) {
	printf("%02x", key[i]);
}
printf("\n");

fclose(random);
}
