#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100
#define MALLOC(p,s)\
 if(!((p)=malloc(s))){\
    fprintf(stderr,"Insufficient memory");\
    exit(EXIT_FAILURE);\
    }

// 크루스칼 알고리즘 ( 최소비용 신장트리를 찾는다 )

typedef struct {
    int v1;
    int v2;
    int weight;
}edge;

edge F[MAX]; // E의 부분집합
edge E[MAX]; // 전체 이음선의 집합
int* U; //서로소 집합

void kruscal(int n, int m);
void initEdge(int n, FILE* f);
int* initial(int n);
int find(int index);
void merge(int p, int q);
void printSet(int* U, int n);

int main() {
    int i = 1;
    int n, m;
    FILE* f = fopen("input.txt", "r");

    fscanf(f, "%d %d", &n, &m);


    initEdge(n, f); // E를 초기화

    kruscal(n, m);
   
    printf("\nEdge list of MST:\n");
    while (F[i].v1 != 0 && F[i].v2 != 0) {
        printf("    (%d  %d) (w=%d)\n", F[i].v1, F[i].v2, F[i].weight);
        i++;
    }
    printf("\n");

    free(U);
    fclose(f);

    return 0;
}

void kruscal(int n, int m) {
    int i, j, p, q;
    int currentFIndex = 1;
    int currentEIndex = 1;
    edge temp;
    int count = 0;

    U = initial(n); // U 초기화

    while (F[n - 1].v1 == 0 && F[n - 1].v2 == 0) { // F의 이음선 수가 n-1보다 작을 때
        printSet(U, n);
        temp = E[currentEIndex++]; // temp는 가중치가 가장 작은 이음선 
        i = temp.v1;
        j = temp.v2;
        p = find(i);
        q = find(j);

        if (p != q) {
            merge(p, q);
            F[currentFIndex++] = temp;

        }
    }
    printSet(U, n);
}

void initEdge(int n, FILE* f) {
    int i = 1;
  
    while (!feof(f)) {
        if (feof(f)) break;
        fscanf(f, "%d %d %d", &E[i].v1, &E[i].v2, &E[i].weight);
        i++;
    }
}

int* initial(int n) {
    int* temp;
    int i;
    MALLOC(temp, sizeof(int) * (n + 1));

    for (i = 1; i <= n; i++) {
        temp[i] = i;
    }

    return temp;
}

int find(int index) {
    int j;
    j = index;
    while (U[j] != j) {
        j = U[j];
    }

    return j;
}

void merge(int p, int q) {
    U[p] = q;
}

void printSet(int* U,int n) {
    int i;

    printf("disjoint sets:");
    for (i = 1; i <= n; i++) {
        printf("%6d", U[i]);
    }
    printf("\n");
}