#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KEYSIZE 16

void main()
{
int i;
char key[KEYSIZE];
time_t t = time(NULL);
printf("%lld\n", (long long) t);
srand (1);
for (i = 0; i< KEYSIZE; i++){
key[i] = rand()%256;
printf("%.2x", (unsigned char)key[i]);
}
printf("\n");
}
