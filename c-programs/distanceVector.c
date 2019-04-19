#include <stdio.h>
#include <stdlib.h>
#define inf 999

struct RouteTable {
	int cost, via;
} rt[20][20];

int n;

void readRouteTable(){
	printf("Enter the number of routers: ");
	scanf("%d", &n);
	
	printf("Enter the routing table(if there is no path then enter 999): \n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i != j){
				printf("Enter the cost from %c-->%c: ", ('A' + i), ('A' + j));
				scanf("%d", &rt[i][j].cost);
			} else {
				rt[i][j].cost = 0;
			}
			
			if(rt[i][j].cost != inf)
				rt[i][j].via = j;
			else
				rt[i][j].via = inf;
		}
	}
}

void computeRouteTable(int src){
	int newCost = 0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(src != i && rt[src][i].cost != inf){
				newCost = rt[src][i].cost + rt[i][j].cost;
				if(newCost < rt[src][j].cost){
					rt[src][j].cost = newCost;
					rt[src][j].via = rt[src][i].via;
				}
			}
		}
	}
}

void displayRouteTable(int src){
	printf("\n\nRouting table for %c: ", ('A' + src));
	printf("\nDestination\tCost\tVia");
	for(int i=0;i<n;i++){
		if(rt[src][i].cost == inf)
			printf("\n%c\t\t%d\t-", ('A' + i), (rt[src][i].cost));
		else
			printf("\n%c\t\t%d\t%c", ('A' + i), (rt[src][i].cost), ('A' + rt[src][i].via));
	}
}

void findPath(int x, int y){
	printf("%c", ('A' + x));
	if(x != y){
		printf("-->");
		findPath(rt[x][y].via, y);
	}
}

void main(){
	readRouteTable();
	
	for(int i=0;i<n;i++)
		computeRouteTable(i);

	for(int i=0;i<n;i++)
		displayRouteTable(i);	
	printf("\n");
	
	int ch = 1, src, dest;
	while(ch){
		printf("\nEnter the source (0-%d): ", n - 1);
		scanf("%d", &src);
		printf("Enter the destination (0-%d): ", n - 1);
		scanf("%d", &dest);
		if(src > (n - 1) || dest > (n - 1))
			printf("Router doesn't exist!");
		else {
			if(rt[src][dest].cost == inf)
				printf("No path exists!\n");
			else{
				printf("Shortest path: ");
				findPath(src, dest);
				printf("\nTotal cost: %d\n", rt[src][dest].cost);	
			}
		}
		printf("\nDo you want to continue? (0-No 1-Yes): ");
		scanf("%d", &ch);
	}
}
