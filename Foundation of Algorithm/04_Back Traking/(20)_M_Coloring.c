#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define CALLOC(p,n,s)\
		if(!((p)=calloc(n,s))){\
		fprintf(stderr,"error\n");\
		exit(EXIT_FAILURE);\
		}
#define TRUE 1
#define FALSE 0

// M Coloring ( 서로 인접한 지역엔 같은 색이 오지않게 m개의 색을 칠하는 알고리즘 )

int n, m , e; // n : 정점의 갯수 , m : 색의 갯수 , e: 간선의 갯수
int** W;
int* vcolor;

//functions
void coloring(int i);
int promising(int i);

int main() {
	int i, j, k;
	FILE* f = fopen("input.txt", "r");

	fscanf(f, "%d %d %d", &m, &n, &e);

	CALLOC(vcolor, (n + 1) ,sizeof(*vcolor));
	CALLOC(W, (n + 1) ,sizeof(*W));
	for (i = 0; i <= n; i++) 
		CALLOC(W[i], (n + 1) ,sizeof(*W));

	for (k = 0; k < e; k++) {
		fscanf(f, "%d %d", &i, &j);
		W[i][j] = 1;
		W[j][i] = 1;
	}

	coloring(0);

	for (i = 0; i <= n; i++) free(W[i]);
	free(W);
	free(vcolor);   fclose(f);
	return  0;
}

void coloring(int i) {
	int color, k;

	if (promising(i)) {
		if (i == n) {
			for (k = 1; k <= n; k++) printf("%3d", vcolor[k]);
			printf("\n");
		}
		else {
			for (color = 1; color <= m; color++) {
				vcolor[i + 1] = color;
				coloring(i + 1);
			}
		}
	}
}

int promising(int i) {
	int j = 1;
	int boolean = TRUE;

	while (j < i && boolean) {
		if (W[i][j] && vcolor[i] == vcolor[j]) boolean = FALSE;
		j++;
	}

	return boolean;
}