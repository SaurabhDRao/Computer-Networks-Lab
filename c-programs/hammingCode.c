#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max 50

int data[max], hamCode[max];

int computeHammingCode(int k){
    int r = 0, j = 0;
    for(int i=1;i<=k+r;i++){
        if(i == pow(2, r))
            hamCode[i] = 0, r++;
        else
            hamCode[i] = data[j++];
    }
    return r;
}

int findParityBits(int k, int r){
    int t = 0, errpos = 0;
    for(int i=1;i<k+r;i++){
        int xor = hamCode[i];
        if(i == pow(2, t)){
            for(int j=i+1;j<=k+r;j++){
                if((i & j) != 0)
                    xor ^= hamCode[j];
            }
            t++;
            hamCode[i] = xor;
            if(xor)
                errpos += i;
        }
    }
    return errpos;
}

int checkErrorType(int errpos, int r){
    for(int i=1;i<pow(2, r);i*=2)
        if(errpos == i)
            return 1;
    return 0;
}

void main(){
    int k, r;
    printf("---Sender---\n");
    printf("Enter the number of input bits: ");
    scanf("%d", &k);
    printf("Enter %d bits: ", k);
    for(int i=0;i<k;i++){
        scanf("%d", &data[i]);
        if(data[i] > 1 || data[i] < 0){
            printf("Invalid bit!\n");
            exit(0);
        }
    }
    r = computeHammingCode(k);
    printf("Number of redundant bits: %d\n", r);
    findParityBits(k, r);
    printf("Transmitted data: ");
    for(int i=1;i<=k+r;i++)
        printf("%2d", hamCode[i]);
    printf("\n");

    int ch, pos;
    printf("\n---Induce Error---\n");
    printf("Do you want to corrupt the data? (0-No 1-Yes): ");
    scanf("%d", &ch);
    if(ch){
        printf("Enter the position to corrupt (1-%d): ", (k+r));
        scanf("%d", &pos);
        if(pos > k+r || pos < 1){
            printf("Invalid position!\n");
            exit(0);
        }
        hamCode[pos] = !(hamCode[pos]);
    }

    printf("\n---Receiver---\n");
    printf("Received data: ");
    for(int i=1;i<=k+r;i++)
        printf("%2d", hamCode[i]);
    printf("\n");
    int errpos = findParityBits(k, r);
    if(errpos){
        if(checkErrorType(errpos, r))
            printf("Parity bit at position %d is corrupted but data is fine!\n", errpos);
        else{
            printf("Data bit at position %d is corrupted!\n", errpos);
            hamCode[errpos] = !(hamCode[errpos]);
            printf("Correct data bits with new parity bits: ");
            for(int i=1;i<=k+r;i++)
                printf("%2d", hamCode[i]);
        }
    } else 
        printf("No error!");
    printf("\n");
}