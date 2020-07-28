#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX 100
#define MALLOC(p,s)\
		if(!((p)=malloc(s))) {\
			fprintf(stderr,"insufficient momory");\
			exit(EXIT_FAILURE);\
		}

// 부분 집합의 합 구하기 알고리즘

int n, W, weight, total = 0;
int include[MAX];
int* w;

// functions
void sumOfSubsets(int i, int weight, int total);
int promising(int i);
void print(int n, int arr[]);

int main() {
    int i;
    FILE* f = fopen("input.txt", "r");

    fscanf(f, "%d %d", &n, &W);
    MALLOC(w, (n + 1) * sizeof(int));

    for (i = 1; i <= n; i++) {
        fscanf(f, "%d", &w[i]);
        total += w[i];
    }

    weight = 0;

    printf("The subsets are:\n");
    sumOfSubsets(0, weight, total);

    free(w);

    fclose(f);

    return 0;
}

void sumOfSubsets(int i, int weight, int total) {
    if (promising(i))
        if (weight == W) {
            print(i, w);
        }
        else {
            include[i + 1] = TRUE; // w[i+1]를 포함한다.
            sumOfSubsets(i + 1, weight + w[i + 1], total - w[i + 1]);
            include[i + 1] = FALSE; // w[i+1]를 포함하지 않는다.
            sumOfSubsets(i + 1, weight, total - w[i + 1]);
        }
}

int promising(int i) {
    return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}

void print(int n, int arr[]) {
    int i;
    for (i = 1; i <= n; i++) {
        if (include[i])
            printf("%d ", arr[i]);
    }
    printf("\n");
}