#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int nof, frmsz, seq[100];

struct frame{
    int seqno;
    char msg[100];
} frms[100], shuffrms[100];

char s[100];

void assignSeqNo(){
    int i, j, k = 0, l;
    l = strlen(s);
    i = 0;
    while(i < l){
        frms[k].seqno = k;
        j = 0;
        while(j < frmsz && s[i] != '\0'){
            frms[k].msg[j] = s[i];
            j++;
            i++;
        }
        k++;
    }   

    printf("After assigning sequence numbers: \n");
    for(i=0;i<k;i++)
        printf("%d: %s\n", frms[i].seqno, frms[i].msg);
}

void shuffle(){
    for(int i=0;i<nof;i++){
        shuffrms[i].seqno = seq[i];
        for(int k=0;k<frmsz;k++)
            shuffrms[i].msg[k] = frms[seq[i]].msg[k];
    }

    printf("After shuffling: \n");
    for(int i=0;i<nof;i++)
        printf("%d: %s\n", shuffrms[i].seqno, shuffrms[i].msg);
}

void sort(){
    for(int i=0;i<nof-1;i++)
        for(int j=0;j<nof-i-1;j++)
            if(shuffrms[j].seqno > shuffrms[j + 1].seqno){
                struct frame temp = shuffrms[j];
                shuffrms[j] = shuffrms[j + 1];
                shuffrms[j + 1] = temp;
            }

    printf("After sorting: \n");
    for(int i=0;i<nof;i++)
        printf("%d: %s\n", shuffrms[i].seqno, shuffrms[i].msg);
}

void main(){
    printf("Enter the string: ");
    gets(s);
    printf("Enter the number of frames: ");
    scanf("%d", &nof);
    frmsz = ceil(strlen(s) / (float)nof);
    printf("Enter the sequence (enter numbers from 0 to %d in any order): \n", nof - 1);
    for(int i=0;i<nof;i++)
        scanf("%d", &seq[i]);
    assignSeqNo();
    shuffle();
    sort();
    printf("Received message: \n");
    for(int i=0;i<nof;i++)
        printf("%s", shuffrms[i].msg);
    printf("\n");
}