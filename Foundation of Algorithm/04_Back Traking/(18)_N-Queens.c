#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX 100

// N-Queens 알고리즘 ( n개의 퀸을 서로 죽이지 않게 배치 ) 

int row[MAX];
int col[MAX];

void queens(int i, int n);
int promising(int i);
void print(int n, int row[], int arr[]);

int main() {
    int n;

    printf("Enter the number of n = "); scanf("%d", &n);

    queens(0, n);

    return 0;
}

void queens(int i, int n) {
    int j;

    if (promising(i))
        if (i == n) { // 리프노드 도착
            print(n, row, col);
        }
        else
            for (j = 1; j <= n; j++) { // 각각 n번
                row[i + 1] = i + 1;
                col[i + 1] = j;
                queens(i + 1, n); // 한칸 더 내려가기
            }
}

int promising(int i) {
    int k = 1;
    int flag = TRUE;
    while (k < i && flag) { // k를 한칸씩 내려가면서 검사
        if (col[i] == col[k] || abs(col[i] - col[k]) == i - k) flag = FALSE;
        k++;
    }

    return flag;
}

void print(int n, int row[], int col[]) {
    int i;
    for (i = 1; i <= n; i++) {
        printf("(%d, %d) ", row[i], col[i]);
    }
    printf("\n");
}