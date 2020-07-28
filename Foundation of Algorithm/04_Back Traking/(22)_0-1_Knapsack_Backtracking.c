#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define CALLOC(p,n,s)\
		if(!((p)=calloc(n,s))){\
		fprintf(stderr,"error\n");\
		exit(EXIT_FAILURE);\
		}

// 0 1 knapsack of Backtraking

int n, W, maxprofit, numbest;
int* bestset, * include, *p, *w;

//functions
void knapsack(int i, int profit, int weight);
int promising(int i, int profit, int weight);
void print(int numbest);

int main() {
	int i;
	FILE* f = fopen("input.txt", "r");
	fscanf(f, "%d %d", &n, &W);

	CALLOC(bestset, n + 1, sizeof(*bestset));
	CALLOC(include, n + 1, sizeof(*include));
	CALLOC(w, n + 1, sizeof(*w));
	CALLOC(p, n + 1, sizeof(*p));

	for (i = 1; i <= n; i++) fscanf(f, "%d", &p[i]);
	for (i = 1; i <= n; i++) fscanf(f, "%d", &w[i]);

	knapsack(0, 0, 0);
	
	print(numbest);

	free(include);  free(bestset);  free(p);  free(w);
	fclose(f);

	return 0;
}

void knapsack(int i, int profit, int weight) {
	if (weight <= W && profit > maxprofit) {
		maxprofit = profit;
		numbest = i;
		for (int k = 1; k <= i; k++) bestset[k] = include[k];
	}
	if (promising(i, profit, weight)) {
		include[i + 1] = TRUE;
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		include[i + 1] = FALSE;
		knapsack(i + 1, profit, weight);
	}
}

int promising(int i, int profit, int weight) {
	int j, k, totweight;
	float bound;

	if (weight >= W) return FALSE;
	else {
		j = i + 1;
		bound = (float)profit;
		totweight = weight;
		while (j <= n && totweight + w[j] <= W) {
			totweight += w[j];
			bound += p[j];
			j++;
		}
		k = j;
		if (k <= n)
			bound += (W - totweight) * (p[k] / w[k]);

		return bound > maxprofit;
	}
}

void print(int numbest) {
	int i;

	printf("maxprofit = %d\n", maxprofit);
	for (i = 1; i <= numbest; i++) {
		if(bestset[i])
			printf("(%d, %d) ", w[i], p[i]);
	}
}