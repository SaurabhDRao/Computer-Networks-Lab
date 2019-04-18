#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ull unsigned long long
#define max 100

ull e, d, n;
ull C[max], D[max];
char msg[max];

ull gcd(ull a, ull b){
    return (b == 0) ? a : gcd(b, a % b);
}

int checkRelative(ull x, ull y){
    return (gcd(x, y) == 1) ? 1 : 0;
}

void computeKeys(ull p, ull q){
    n = p * q;
    ull z = (p - 1) * (q - 1);
    for(ull i=z-1;i>=2;i--){
        if(checkRelative(i, z)){
            int found = 0;
            e = i;
            for(ull j=1;j<=n && j != e;j++){
                ull mod = ((j % z) * (e % z)) % z;
                if(mod == 1){
                    d = j;
                    found = 1;
                    break;
                }
            }
            if(found)
                break;
        }
    }
    printf("All values: \n");
    printf("N: %llu\tZ: %llu\tE: %llu\tD: %llu\t", n, z, e, d);
}

int xPowYModN(ull x, ull y, ull n){
    ull r = 1;
    while(y > 0){
        if((y % 2) == 1)
            r = (r * x) % n;
        x = (x * x) % n;
        y = y / 2;
    }
    return(r);
}

void displayArray(ull a[], int size){
    for(int i=0;i<size;i++)
        printf("%c", a[i]);
    printf("\n");
}

void main(){
    ull p, q;
    printf("Enter two large prime numbers: ");
    scanf("%llu%llu", &p, &q);
    computeKeys(p, q);

    printf("\nPublic key: { %llu, %llu }", e, n);
    printf("\nPrivate key: { %llu, %llu }", d, n);

    printf("\nEnter the message to encrypt: ");
    scanf("%d", msg);
    scanf("%[^\n]", msg);

    int count = 0;
    for(int i=0;msg[i]!='\0';i++){
        int ptxt = (int)msg[i];
        C[i] = xPowYModN(ptxt, e, n);
        count++;
    }

    printf("Encrypted message: ");
    displayArray(C, count);

    for(int i=0;i<count;i++){
		ull ctxt = C[i];
		D[i] = xPowYModN(ctxt, d, n);
	}

	printf("Decrypted message: ");
	displayArray(D,count);
}