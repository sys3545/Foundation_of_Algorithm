#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100
#define TRUE 1
#define FALSE 0
#define CALLOC(p,n,s)\
 if(!((p)=calloc(n,s))){\
    fprintf(stderr,"Insufficient memory");\
    exit(EXIT_FAILURE);\
    }

// 마감시간이 있는 스케쥴 짜기 알고리즘

void scheduling(int n, int** deadline, int** reward, int **S, int **K);
void copyToFrom(int len, int*** K, int*** S);
void insert(int i, int len, int*** K, int** deadline);
int isFeasible(int len, int** K, int** deadline);

int main() {
    int n, i;
    int* deadline;
    int* reward;
    int* S, * K;
    FILE* f = fopen("input.txt", "r");

    fscanf(f, "%d", &n);
    CALLOC(deadline, (n + 1), sizeof(int));
    CALLOC(reward, (n + 1), sizeof(int));
    CALLOC(S, (n + 1), sizeof(int));
    CALLOC(K, (n + 1), sizeof(int));

    for (i = 1; i <= n; i++) fscanf(f, "%d", &deadline[i]);
    for (i = 1; i <= n; i++) fscanf(f, "%d", &reward[i]);

    printf("Result of Scheduling:\n");
    scheduling(n, &deadline, &reward, &S, &K);

    free(deadline);  free(reward);  free(S);  free(K);
    fclose(f);

    return 0;
}

void scheduling(int n, int** deadline, int** reward, int** S, int** K) {
    int i, total = 0, len = 1;
    (*S)[len++] = 1;
    
    for (i = 2; i <= n; i++) {
        copyToFrom(len, &K, &S);
        insert(i, len, &K, deadline);
        if (isFeasible(len, K, deadline))
            copyToFrom(len++, &S, &K);
    }

    for (i = 1; i < len; i++) {
        if (i == len - 1) printf("%d]\n", (*S)[i]);
        else if (i == 1) printf("[%d, ", (*S)[i]);
        else
            printf("%d, ", (*S)[i]);
        total += (*reward)[(*S)[i]];
    }

    printf("Total Reward : %d\n", total);
}

void copyToFrom(int len, int*** K, int*** S) {
    int i;
    for (i = 1; i <= len; i++) {
        (**K)[i] = (**S)[i];
    }
}

void insert(int i, int len, int*** K, int** deadline) {
    int j;
    for (j = len; j > 0; j--) {
        if ((*deadline)[i] >= (*deadline)[(**K)[j - 1]]) break;
        (**K)[j] = (**K)[j - 1];
    }
    (**K)[j] = i;
}

int isFeasible(int len, int** K, int** deadline) {
    int i;
    for (i = 1; i <= len; i++) {
        if ((*deadline)[(*K)[i]] < i) return FALSE;
    }
    return TRUE;
}