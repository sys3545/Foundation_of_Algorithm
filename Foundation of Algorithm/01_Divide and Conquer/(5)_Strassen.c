#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h.>
#include <stdlib.h>

// 스트라센의 행렬곱셈

int** makeMatrix(int n); // 행렬 생성 (동적 할당)
void strassen(int n, int** A, int** B, int** C); // 행렬 곱셈 (슈트라센)
void matrixMult(int n, int** A, int** B, int** C); // 행렬 곱셈(표준 알고리즘)
int** matrixAdd(int n, int** A, int** B); // 행렬 덧셈
int** matrixSub(int n, int** A, int** B); // 행렬 뺄셈
int** devideMatrix(int n, int** A, int x_index, int y_index); // 행렬 분해
void mergeMatrix(int n, int** C11, int** C12, int** C21, int** C22,int** C);// 배열 합병
void freeArray(int** arr, int n); // 메모리 해제

int main() {
	int** A;
	int** B;
	int** C;
	int i, j, n;

	FILE* f = fopen("input.txt", "r");
	fscanf(f,"%d", &n);

	A = makeMatrix(n);
	B = makeMatrix(n);
	C = makeMatrix(n);

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(f, "%d", &A[i][j]);
		}
	}

	fscanf(f, "%d", &n);

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(f, "%d", &B[i][j]);
		}
	}


	strassen(n, A, B, C);


	printf("Result of multiplication: \n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%-4d ", C[i][j]);
		}
		printf("\n");
	}

	freeArray(A, n);
	freeArray(B, n);
	freeArray(C, n);

	return 0;
}

// 행렬 곱셈 (슈트라센)
void strassen(int n, int** A, int** B, int** C) {
	int** M1, ** M2, ** M3, ** M4, ** M5, ** M6, ** M7;
	int** C11, ** C12, ** C21, ** C22;
	int** X1, ** X2, **X3, **X4, **X5, **X6, **X7, **X8, **X9, **X10;
	int h_n = n / 2;

	if (n <= 2) {
		matrixMult(n, A, B, C);
		return;
	}
	
	X1 = makeMatrix(h_n);  X2 = makeMatrix(h_n);  X3 = makeMatrix(h_n);  X4 = makeMatrix(h_n);  X5 = makeMatrix(h_n);
	X6 = makeMatrix(h_n);  X7 = makeMatrix(h_n);  X8 = makeMatrix(h_n);  X9 = makeMatrix(h_n);  X10 = makeMatrix(h_n);
	X1 = matrixAdd(h_n, devideMatrix(h_n, A, 0, 0), devideMatrix(h_n, A, h_n, h_n));
	X2 = matrixAdd(h_n, devideMatrix(h_n, B, 0, 0), devideMatrix(h_n, B, h_n, h_n));
	X3 = matrixAdd(h_n, devideMatrix(h_n, A, h_n, 0), devideMatrix(h_n, A, h_n, h_n));
	X4 = matrixSub(h_n, devideMatrix(h_n, B, 0, h_n), devideMatrix(h_n, B, h_n, h_n));
	X5 = matrixSub(h_n, devideMatrix(h_n, B, h_n, 0), devideMatrix(h_n, B, 0, 0));
	X6 = matrixAdd(h_n, devideMatrix(h_n, A, 0, 0), devideMatrix(h_n, A, 0, h_n));
	X7 = matrixSub(h_n, devideMatrix(h_n, A, h_n, 0), devideMatrix(h_n, A, 0, 0));
	X8 = matrixAdd(h_n, devideMatrix(h_n, B, 0, 0), devideMatrix(h_n, B, 0, h_n));
	X9 = matrixSub(h_n, devideMatrix(h_n, A, 0, h_n), devideMatrix(h_n, A, h_n, h_n));
	X10 = matrixAdd(h_n, devideMatrix(h_n, B, h_n, 0), devideMatrix(h_n, B, h_n, h_n));

	M1 = makeMatrix(h_n);
	M2 = makeMatrix(h_n);
	M3 = makeMatrix(h_n);
	M4 = makeMatrix(h_n);
	M5 = makeMatrix(h_n);
	M6 = makeMatrix(h_n);
	M7 = makeMatrix(h_n);
	
	//M1
	strassen(h_n, X1, X2, M1);
	//M2
	strassen(h_n, X3, devideMatrix(h_n, B, 0, 0), M2);
	//M3
	strassen(h_n, devideMatrix(h_n, A, 0, 0), X4, M3);
	//M4
	strassen(h_n, devideMatrix(h_n, A, h_n, h_n), X5, M4);
	//M5
	strassen(h_n, X6, devideMatrix(h_n, B, h_n, h_n), M5);
	//M6
	strassen(h_n, X7, X8, M6);
	//M7
	strassen(h_n, X9, X10, M7);
	
	C11 = makeMatrix(h_n);
	C12 = makeMatrix(h_n);
	C21 = makeMatrix(h_n);
	C22 = makeMatrix(h_n);

	C11 = matrixAdd(h_n, M1, M4);  C11 = matrixSub(h_n, C11, M5);  C11 = matrixAdd(h_n,C11, M7);
	C12 = matrixAdd(h_n, M3, M5);
	C21 = matrixAdd(h_n, M2, M4);
	C22 = matrixAdd(h_n, M1, M3);  C22 = matrixSub(h_n, C22, M2);  C22 = matrixAdd(h_n, C22, M6);

	mergeMatrix(h_n, C11, C12, C21, C22, C);
}

// 행렬 곱하기 (표준 알고리즘)
void matrixMult(int n, int** A, int** B, int** C) {
	int i, j, k;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// 행렬 덧셈
int** matrixAdd(int n, int** A, int** B) {
	int i, j;
	int** x;

	x = makeMatrix(n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
				x[i][j] = A[i][j] + B[i][j];
		}
	}
	return x;
}

// 행렬 뺄셈
int** matrixSub(int n, int** A, int** B) {
	int i, j;
	int** x;

	x = makeMatrix(n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			x[i][j] = A[i][j] - B[i][j];
		}
	}
	return x;
}

// 행렬 분해
int** devideMatrix(int n, int** A, int x_index, int y_index) {
	int** x, i, j;

	x = makeMatrix(n);

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			x[i][j] = A[x_index + i][y_index + j];
		}
	}
	
	return x;
}

// 행렬 생성 (동적 할당)
int** makeMatrix(int n) {
	int** x, i;

	x = (int**)calloc(n,sizeof(int*));
	for (i = 0; i < n; i++) {
		x[i] = (int*)calloc(n, sizeof(int));
	}

	return x;
}

// 배열 합병
void mergeMatrix(int n, int** C11, int** C12, int** C21, int** C22,int **C) {
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			C[i][j] = C11[i][j];

	for (i = 0; i < n; i++)
		for (j = n; j < 2 * n; j++)
			C[i][j] = C12[i][j-n];

	for (i = n; i < 2 * n; i++)
		for (j = 0; j < n; j++)
			C[i][j] = C21[i - n][j];

	for (i = n; i < 2 * n; i++)
		for (j = n; j < 2 * n; j++)
			C[i][j] = C22[i - n][j - n];
}


//메모리 해제
void freeArray(int** arr,int n) {
	int i;
	for (i = 0; i < n; i++) {
		free(arr[i]);
	}
	free(arr);
}