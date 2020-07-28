#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INF 999
#define MAX 100
#define MALLOC(p,s)\
 if(!((p)=malloc(s))){\
    fprintf(stderr,"Insufficient memory");\
    exit(EXIT_FAILURE);\
    }

// 프림 알고리즘 (최소비용 신장트리를 찾는다) - 신장트리 :  모든 정점을 연결하지만 사이클은 없는 트리
typedef struct {
    int v1;
    int v2;
    int weight;
}edge;

int** W;
edge F[MAX];
int* Y;

int** InitMatrix(int n);
void prim(int n);
void print(int* distance, int* nearest, int n);

int main() {
    int n, i, j, k;
    int total = 0;
    FILE* f = fopen("input.txt", "r");

    fscanf(f, "%d", &n);

    MALLOC(Y, (n + 1) * sizeof(int));
    W = InitMatrix(n + 1);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            fscanf(f, "%d", &k);
            W[i][j] = k; 
        }       
    }

    prim(n);

    printf("\nEdge list of MST:\n");
    i = 0;
    while (F[i].v1 != 0 && F[i].v2 != 0) {
        printf("       (%d  %d) (w=%d)\n", F[i].v1, F[i].v2, F[i].weight);
        total += F[i].weight;
        i++;
    }
    printf("Total cost of MST : %d\n", total);

    for (i = 0; i < n + 1; i++) free(W[i]);
    free(W);
    free(Y);
    fclose(f);

    return 0;
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
        }
    }

    return temp;
}

void prim(int n) {
    int i, vnear, vertex;
    int min, yIndex = 0, fIndex = 0;
    edge e;
    int* nearest;
    int* distance;

    MALLOC(nearest, (n + 1) * sizeof(int));
    MALLOC(distance, (n + 1) * sizeof(int));

    //초기화
    Y[1] = 1;  yIndex = 1;
    for (i = 2; i <= n; i++) {
        nearest[i] = 1;
        distance[i] = W[1][i];
    }

    print(distance, nearest, n);

    for (vertex = 2; vertex <= n; vertex++) {
        min = INF;
        for (i = 2; i <= n; i++)
            if (0 <= distance[i] && distance[i] < min) {
                min = distance[i];
                vnear = i;
            }
        e.v1 = nearest[vnear];
        e.v2 = vnear;
        e.weight = W[nearest[vnear]][vnear];
        Y[++yIndex] = vnear;
        F[fIndex++] = e;

        distance[vnear] = -1; // 추가시킨 마디의 인덱스는 -1로 변경

        //Y에 속하지 않은 각 마디에 대하여 distance를 갱신
        for (i = 2; i <= n; i++) {
            if (W[i][vnear] < distance[i]) { 
                distance[i] = W[i][vnear];
                nearest[i] = vnear;
            }
        }
        print(distance, nearest, n);
    }

    free(nearest);
    free(distance);
}

void print(int *distance, int *nearest, int n) {
    int i;

    printf("distance:   ");
    for (i = 2; i <= n; i++)
        printf("%6d", distance[i]);
    printf("\nnearest:    ");
    for (i = 2; i<= n; i++)
        printf("%6d", nearest[i]);

    printf("\n");
}