#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INF 999
#define MAX 100
#define CALLOC(p,n,s)\
 if(!((p)=calloc(n,s))){\
    fprintf(stderr,"Insufficient memory");\
    exit(EXIT_FAILURE);\
    }

// 다익스트라 알고리즘 ( 두 정점 간의 최단경로를 찾는다 )

typedef struct {
    int v1;
    int v2;
    int weight;
}edge;

int** W;
edge F[MAX];
int* Y;

int** InitMatrix(int n);
void dijkstra(int n);
void print(int* touch, int* length, int n);
void path(int destination, int* touch);
int lengthOfPath(int destination, int* touch);

int main() {
    int n, i, j, k;
    FILE* f = fopen("input.txt", "r");

    fscanf(f, "%d", &n);
    CALLOC(Y, (n + 1), sizeof(int));
    W = InitMatrix(n + 1);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            fscanf(f, "%d", &k);
            W[i][j] = k;
        }
    }

    dijkstra(n);

    free(Y);
    fclose(f);
    return 0;
}

void dijkstra(int n) {
    int i, vnear, min, yIndex, destination, fIndex = 0;
    edge e;
    int* touch;
    int* length;

    CALLOC(touch, (n + 1) ,sizeof(int));
    CALLOC(length, (n + 1) ,sizeof(int));

    Y[1] = 1;  yIndex = 1;
    for (i = 2; i <= n; i++) {
        touch[i] = 1;
        length[i] = W[1][i];
    }

    while (Y[n] == 0) {
        print(touch, length, n);
        min = INF;
        for (i = 2; i <= n; i++) {
            if (0 <= length[i] && length[i] < min) {
                min = length[i];
                vnear = i;
            }
        }
        e.v1 = touch[vnear];
        e.v2 = vnear;
        e.weight = W[touch[vnear]][vnear];
        F[++fIndex] = e;

        for (i = 2; i <= n; i++) {
            if (length[vnear] + W[vnear][i] < length[i]) {
                length[i] = length[vnear] + W[vnear][i];
                touch[i] = vnear;
            }
        }
        length[vnear] = -1;
        Y[++yIndex] = vnear;
    }

    print(touch, length, n);
    printf("Enter the destination: ");  scanf("%d", &destination);
    printf("The length of shortest path = %d\n",lengthOfPath(destination,touch));
    printf("The shortest path from 1 to %d : ", destination);
    path(destination, touch);  printf("v%d\n", destination);

    free(touch);   free(length);
}

int lengthOfPath(int destination, int* touch) {
    int length = 0;
    int vertex;
    int Wlength = W[1][destination];

    vertex = touch[destination];
    while (vertex != 1) {
        length += W[vertex][destination];
        destination = vertex;
        vertex = touch[vertex];
    }
    length += W[vertex][destination];

    return length >= Wlength ? Wlength : length;
}

void path(int destination, int* touch) {
    int vertex;
    vertex = touch[destination];

    if (vertex == 1) {
        printf("v%d ", vertex);
        return;
    }
    path(vertex, touch);
    printf("v%d ", vertex);
}

int** InitMatrix(int n) {
    int** temp;
    int i, j;

    CALLOC(temp, (n + 1) ,sizeof(int*));
    for (i = 0; i < (n + 1); i++)
        CALLOC(temp[i], (n + 1) ,sizeof(int));

    for (i = 1; i < n + 1; i++) {
        for (j = 1; j < n + 1; j++) {
            if (i == j)temp[i][j] = 0;
        }
    }

    return temp;
}

void print(int* touch, int* length, int n) {
    int i;

    printf("touch:    ");
    for (i = 2; i <= n; i++)
        printf("%6d", touch[i]);
    printf("\nlength:   ");
    for (i = 2; i <= n; i++)
        printf("%6d", length[i]);

    printf("\n");
}