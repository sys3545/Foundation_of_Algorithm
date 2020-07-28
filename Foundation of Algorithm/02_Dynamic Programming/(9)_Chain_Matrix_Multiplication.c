#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#define INF INT_MAX/10
#define MAX 100

// 연쇄 행렬 곱셈 알고리즘 ( 가장 적게 곱셈을 하는 방법을 찾는다)

int M[MAX][MAX];
int P[MAX][MAX];
int d[MAX];

int minMult(int n);
int minimum(int i, int j, int* mink);
void print(int a[][MAX], int n, int version);
void order(int i, int j);

int main(){
	int n, i, result=0;
	FILE* f = fopen("input.txt", "r");
	
	fscanf(f, "%d", &n);
	for (i = 0; i <= n; i++) fscanf(f, "%d", &d[i]);

	result = minMult(n);
	printf("The result of M:\n");   print(M, n, 1);
	printf("The optimal value is %d\n\n\n", result);
	printf("The result of P:\n");   print(P, n, 2);

	printf("The optimal order of multiplication is\n");
	order(1, n);
	printf("\n");

	
	return 0;
}

int minMult(int n) {
	int i, j, k, diagonal;
	
	for (i = 1; i <= n; i++) M[i][i] = 0;

	for (diagonal = 1; diagonal <= n - 1; diagonal++) {
		for (i = 1; i <= n - diagonal; i++) {
			j = i + diagonal;
			M[i][j] = minimum(i, j, &k);
			P[i][j] = k;
		}
	}

	return M[1][n];
}


int minimum(int i, int j, int* mink) {
	int m,k;
	int min = INF;
	for (k = i; k < j; k++) {
		m = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
		if (min > m) {
			min = m;
			*mink = k;
		}
	}

	return min;
}

void order(int i, int j) {
	int k;
	if (i == j) printf("A%d", i);
	else {
		k = P[i][j];
		printf("(");
		order(i, k);
		order(k + 1, j);
		printf(")");
	}
}

void print(int a[][MAX], int n, int version) {
	int i, j;

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (version == 1) {
				if (i > j)printf("      ");
				else printf("%6d", a[i][j]);
			}
			else {
				if (i >= j)printf("      ");
				else printf("%6d", a[i][j]);
			}
		}
		printf("\n");
	}
}