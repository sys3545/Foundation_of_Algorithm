#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#define INF INT_MAX/10
#define MAX 100
#define CALLOC(p,n,s)\
		if(!((p)=calloc(n,s))) {\
			fprintf(stderr,"insufficient momory");\
			exit(EXIT_FAILURE);\
			}

// 최적 이진 탐색 트리 (평균 탐색 시간이 최소가 되는 BST 찾기)

typedef struct nodeType* nodePointer;
typedef struct nodeType {
	int key;
	nodePointer left;
	nodePointer right;
}nodeType;

int *Keys;
int *p;
int A[MAX][MAX];
int R[MAX][MAX];

void optSearchTree(int n);
int minimum(int i, int j, int* mink);
int sum(int i, int j, int* p);
void print(int a[][MAX], int n);
void inorder(nodePointer ptr);
void preorder(nodePointer ptr);
nodePointer tree(int i, int j);


int main() {
	int i, n;
	nodePointer ptr;
	FILE* f = fopen("input.txt", "r");
	fscanf(f, "%d", &n);

	CALLOC(Keys, n + 1, sizeof(int));
	CALLOC(p, n + 1, sizeof(int));

	for (i = 0; i <= n; i++) fscanf(f, "%d", &Keys[i]);
	for (i = 0; i <= n; i++) fscanf(f, "%d", &p[i]);

	optSearchTree(n);
	printf("The result of A :\n");
	print(A, n);
	printf("The optimal value is : %d\n\n\n", A[1][n]);
	printf("The result of R :\n");
	print(R, n);

	ptr = tree(1, n);
	printf("\nThe optimal BST is : \n");
	printf("PreOrder : ");   preorder(ptr);  printf("\n");
	printf("InOrder : ");   inorder(ptr);  printf("\n");

	free(ptr);
	free(Keys);
	free(p);
	return 0;
}

void optSearchTree(int n) {
	int i, j, k, diagonal;
	for (i = 1; i <= n; i++) {
		A[i][i - 1] = 0;
		A[i][i] = p[i];
		R[i][i - 1] = 0;
		R[i][i] = i;
	}
	A[n + 1][n] = 0;
	R[n + 1][n] = 0;

	for (diagonal = 1; diagonal <= n - 1; diagonal++)
		for (i = 1; i <= n - diagonal; i++) {
			j = i + diagonal;
			A[i][j] = minimum(i, j, &k);
			R[i][j] = k;
		}
}

int minimum(int i, int j, int* mink) {
	int m,k;
	int min = INF;

	for (k = i; k < j; k++) {
		m = A[i][k - 1] + A[k + 1][j] + sum(i, j, p);
		if (min > m) {
			min = m;
			*mink = k;
		}
	}
	return min;
}

int sum(int i, int j, int* p) {
	int k, result = 0;
	for (k = i; k <= j; k++) {
		result += p[k];
	}

	return result;
}

void print(int a[][MAX], int n) {
	int i, j;

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {			
			if (i > j)printf("    ");
			else printf("%4d", a[i][j]);
		}
		printf("\n");
	}
}

void inorder(nodePointer ptr) {
	if (ptr) {
		inorder(ptr->left);
		printf("%d ", ptr->key);
		inorder(ptr->right);
	}
}

void preorder(nodePointer ptr) {
	if (ptr) {
		printf("%d ", ptr->key);
		preorder(ptr->left);
		preorder(ptr->right);
	}
}

nodePointer tree(int i, int j) {
	int k;
	nodePointer ptr;

	k = R[i][j];
	if (k == 0) return NULL;
	else {
		CALLOC(ptr, 1, sizeof(nodeType));
		ptr->key = Keys[k];
		ptr->left = tree(i, k - 1);
		ptr->right = tree(k + 1, j);
		return ptr;
	}
}