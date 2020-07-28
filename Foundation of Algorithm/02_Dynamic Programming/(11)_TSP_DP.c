#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100
#define TRUE 1
#define FALSE 0
#define INF INT_MAX/10

// 외판원 알고리즘 ( 한 정점에서 출발하여 모든 도시를 한번씩만 거친 후 다시 돌아오는 최적 경로 찾기 ) - 동적계획법 

int W[MAX][MAX];
int P[MAX][MAX];
int D[MAX][MAX];
int printCount = 0;

void travel(int n);
int contain(int A, int k, int n);
int isIn(int i, int A);
int diff(int A, int j);
int minimum(int i, int A, int* minJ, int n);
void init(int W[][MAX], int n, FILE* f);
void path(int v, int A);


int main() {
	int n, last;
	FILE* f = fopen("input.txt", "r");
	
	fscanf(f, "%d", &n);
	init(W, n, f);

	travel(n);

	last = ((int)pow(2, n - 1)) - 1;
	printf("Total weights of optimal tour =  %d\n", D[1][last]);

	printf("Path of optimal tour: ");
    path(1, last);

	return 0;
}

void travel(int n) {
	int i, j, k, A;
	int size = (int)pow(2, n - 1);

	for (i = 2; i <= n; i++) D[i][0] = W[i][1];
	
	for (k = 1; k <= n - 2; k++)
		for (A = 1; A < size; A++) {
			if (contain(A, k, n) != k) continue; // A가 k개의 원소를 포함하는가?
			for (i = 2; i <= n; i++) {
				if (isIn(i, A)) continue; // i가 A에 포함되어 있는가?  (포함되어 있으면 넘어간다)
				D[i][A] = minimum(i, A, &j, n);
				P[i][A] = j;
			}
		}
	A = size - 1;
	D[1][A] = minimum(1, A, &j, n);
	P[1][A] = j;
}

int minimum(int i, int A, int* minJ, int n) {
	int j, m, min;
	min = INF;
	for (j = 2; j <= n; j++) {
		if (!isIn(j, A) || !W[i][j] || !D[j][diff(A, j)]) continue; // j가 A에 포함되고 경로가 있어야 진행가능
		m = W[i][j] + D[j][diff(A, j)];
		if (min > m) {
			min = m;
			*minJ = j;
		}
	}
	return min;
}

// A는 몇개의 원소를 가지는 집합인가?
int contain(int A, int k, int n) {
	int i, count = 0;
	
	for (i = 0; i < n-1; i++) 
		if (A & (1 << i)) count++;
	
	return count;
}

// i가 A에 포함되어 있는가?
int isIn(int i, int A) {
	if (A & (1 << (i - 2)))
		return TRUE;

	return FALSE;
}

int diff(int A, int j) {
	return A & ~(1 << (j - 2));
}

void init(int W[][MAX], int n, FILE* f) {
	int i, j;

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			fscanf(f, "%d", &W[i][j]);
		}
	}
}

void path(int v, int A) {
	int next;
	if (printCount == 0) {
		printf("v%d ",v);
		printCount++;
	}
	if (A == 0) {
		printf("v1\n");
		return;
	}

	next = P[v][A];
	printf("v%d ", next);
	path(next, diff(A, next));
}
