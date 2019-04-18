#include <stdio.h>
#include <stdlib.h>
#define BUCKETSIZE 250
#define OUTRATE 25

struct packet{
    int arrivalTime, weight;
} pkt[15];

void runLeakyBucket(int listenTime, int outTime){
    int t, pktno = 0, remaining = 0, freeSpace = BUCKETSIZE;
    for(t=1;t<=listenTime;t++){
        if(pkt[pktno].arrivalTime == t){
            if(pkt[pktno].weight <= freeSpace){
                remaining += pkt[pktno].weight;
                freeSpace -= pkt[pktno].weight;
                printf("At time = %d: packet%d is added to the bucket!", t, (pktno + 1));
                printf("\nFree space available in the bucket: %d\n\n", freeSpace);
            } else {
                printf("At time = %d: packet%d is discarded because the size of the packet exceeds the free space in the bucket!\n\n", t, (pktno + 1));
            }
            pktno++;
        }
        if((t % outTime) == 0){
            if(remaining >= OUTRATE){
                remaining -= OUTRATE;
                freeSpace += OUTRATE;
                printf("At time = %d: %dKb is transferred!", t, OUTRATE);
            } else if(remaining > 0){
                freeSpace += remaining;
                printf("At time = %d: %dKb is transferred!", t, remaining);
                remaining = 0;
            }
            printf("\nFree space available in the bucket: %d\n\n", freeSpace);
        }
    }
    while((t % outTime) != 0)
        t++;
    while(remaining > 0){
        if(remaining < OUTRATE){
            freeSpace += remaining;
            printf("At time = %d: %dKb is transferred!", t, remaining);
            t += outTime;
            printf("\nFree space available in the bucket: %d\n\n", freeSpace);
            break;
        }
        remaining -= OUTRATE;
        freeSpace += OUTRATE;
        printf("At time = %d: %dKb is transferred!", t, OUTRATE);
        printf("\nFree space available in the bucket: %d\n\n", freeSpace);
        t += outTime;
    }
    printf("Bucket is empty!\n");
}

void main(){
    int n, listenTime, outTime;
    printf("Enter the number of packets: ");
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        printf("Enter the arrival time and weight of packet%d: ", (i + 1));
        scanf("%d%d", &pkt[i].arrivalTime, &pkt[i].weight);
    }
    printf("Enter the time till when to listen for packet arrival: ");
    scanf("%d", &listenTime);
    printf("Enter the constant duration when the packets are to be transmitted: ");
    scanf("%d", &outTime);
    runLeakyBucket(listenTime, outTime);
    printf("\n");
}