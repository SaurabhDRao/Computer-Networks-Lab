#include <stdio.h>
#include <stdlib.h>

int n, r[16], inp[20];

void crc(){
	for(int i=0;i<16;i++)
		r[i] = 0;
	for(int i=0;i<n+16;i++){
		int lmb = r[15];
		for(int j=15;j>=0;j--)
			r[j] = r[j - 1];
		r[0] = inp[i];
		if(lmb == 1){
			r[12] ^= lmb;
			r[5] ^= lmb;
			r[0] ^= lmb;
		}
	}

	printf("Register contents: ");
	for(int i=15;i>=0;i--)
		printf("%d", r[i]);
	printf("\n");

	int i = n, j = 15;
	while(j >= 0)
		inp[i++] = r[j--];
}

int checkError(){
	for(int i=15;i>=0;i--)
		if(r[i] != 0)
			return i;
	return -1;
}

void main(){
	printf("---Sender---\n");
	printf("Enter the number of bits in the input: ");
	scanf("%d", &n);
	printf("Enter %d bits (0 or 1): ", n);
	for(int i=0;i<n;i++){
		scanf("%d", &inp[i]);
		if(inp[i] > 1 || inp[i] < 0){
			printf("Invalid bit!");
			exit(0);
		}
	}
	for(int i=n;i<n+16;i++)
		inp[i] = 0;
	crc();
		
	printf("Transmitted data: ");
	for(int i=0;i<n+16;i++)
		printf("%d", inp[i]);
	printf("\n");

	printf("\n---Induce error---\n");
	printf("Do you want to corrupt the transmitted message? (0-no, 1-yes): ");
	int ch, cpos;
	scanf("%d", &ch);
	if(ch){
		printf("Enter the position to corrupt(%d-%d): ", n, (n + 15));
		scanf("%d", &cpos);
		inp[cpos] = !(inp[cpos]);
	}

	printf("\n---Receiver---\n");

	printf("Received data: ");
	for(int i=0;i<n+16;i++)
		printf("%d", inp[i]);
	printf("\n");

	crc();
	int epos = checkError();
	if(epos == -1)
		printf("No error!");
	else
		printf("Error detected at position: %d", n + 15 - epos);
	printf("\n");
}