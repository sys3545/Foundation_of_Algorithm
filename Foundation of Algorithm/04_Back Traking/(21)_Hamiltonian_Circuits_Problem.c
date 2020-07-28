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

// 해밀턴 회로 ( 한 곳에서 출발하여 모든 정점을 한번씩 들르고 다시 첫 정점으로 돌아오는 경로 ) 

int n, e;
int** W;
int* vindex;

//functions
void hamiltonian(int i);
int promising(int i);


int main() {
	int i, j ,k;
	FILE* f = fopen("input.txt", "r");
	fscanf(f, "%d %d", &n, &e);

	CALLOC(vindex, n ,sizeof(*vindex));
	CALLOC(W, (n + 1) ,sizeof(*W));
	vindex[0] = 1;

	for (i = 0; i <= n; i++) CALLOC(W[i], (n + 1) ,sizeof(**W));

	for (k = 0; k < e; k++) {
		fscanf(f, "%d %d", &i, &j);
		W[i][j] = 1;
		W[j][i] = 1;
	}

	hamiltonian(0);

	for (i = 0; i <= n; i++) free(W[i]);
	free(W);
	free(vindex);   fclose(f);
	return 0;
}

void hamiltonian(int i) {
	int j, k;

	if (promising(i)) {
		if (i == n - 1) { // 출력
			for (k = 0; k < n; k++) {
				printf("%3d", vindex[k]);
			}
			printf("  1\n");
		}
		else {
			for (j = 2; j <= n; j++) {
				vindex[i + 1] = j;
				hamiltonian(i + 1);
			}
		}
	}
}


int promising(int i) {
	int j;
	int boolean;

	if (i == n - 1 && !W[vindex[n - 1]][vindex[0]]) // 마지막 정점은 첫번째 정점과 인접해야한다.
		boolean = FALSE;
	else if (i > 0 && !W[vindex[i - 1]][vindex[i]]) // i정점은 i-1정점과 인접해야 한다.
		boolean = FALSE;
	else {
		boolean = TRUE;
		j = 1;
		while (j < i && boolean) {
			if (vindex[i] == vindex[j]) boolean = FALSE;
			j++;
		}
	}

	return boolean;
}