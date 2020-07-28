#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) ((a)<=(b))? a : b
#define MALLOC(p,s)\
 if(!((p)=malloc(s))){\
    fprintf(stderr,"Insufficient memory");\
    exit(EXIT_FAILURE);\
    }

// 프로이드의 최단경로 알고리즘 (전체 정점에 대하여 각각의 최단경로를 다 구한다)

int** P;

int** InitMatrix(int n);
void floyd2(int** D, int n);
void initP(int n);
void path(int i, int j);
void print(int** D, int n);

int main() {
    int i, j, k, n, e, c;
    int** D;
    FILE* f = fopen("input.txt", "r");

    fscanf(f, "%d %d", &n, &e);

    D = InitMatrix(n);

    for (c = 0; c < e; c++) {
        fscanf(f, "%d %d %d", &i, &j, &k);
        D[i][j] = k;
    }

    printf("Enter the source node : "); scanf("%d", &i);
    printf("Enter the destination node : "); scanf("%d", &j);

    floyd2(D, n);
    
    printf("Path from %d to %d is : ", i, j);
    printf("%d ", i);  path(i, j);  printf("%d\n", j);

    for (i = 0; i < n + 1; i++) {
        free(D[i]);
        free(P[i]);
    }

    free(D);
    free(P);

    return 0;
}

void floyd2(int** D, int n) {
    int i, j, k;

    initP(n);

    for (k = 1; k <= n; k++)
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                if (D[i][j] > D[i][k] + D[k][j]) {
                    P[i][j] = k;
                    D[i][j] = D[i][k] + D[k][j];
                }
}

int** InitMatrix(int n) {
    int** temp;
    int i, j;

    MALLOC(temp, (n + 1) * sizeof(int*));
    for (i = 0; i < (n + 1); i++)
        MALLOC(temp[i], (n + 1) * sizeof(int));

    for (i = 1; i < n + 1; i++) {
        for (j = 1; j < n + 1; j++) {
            if (i == j)temp[i][j] = 0;
            else temp[i][j] = 500;
        }
    }


    return temp;
}

void initP(int n) {
    int i;

    P = (int**)calloc(n + 1, sizeof(int));

    for (i = 0; i < (n + 1); i++) P[i] = (int*)calloc(n + 1, sizeof(int));

}

void path(int i, int j) {
    int k = P[i][j];
    if (k != 0) {
        path(i, k);
        printf("%d ", k);
        path(k, j);
    }
}

void print(int** D, int n) {
    int i, j;

    printf("D = \n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            printf("%5d", D[i][j]);
        }
        printf("\n");
    }
}