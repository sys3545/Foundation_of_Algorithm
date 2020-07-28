#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define MALLOC(p,s)\
 if(!((p)=malloc(s))){\
    fprintf(stderr,"Insufficient memory");\
    exit(EXIT_FAILURE);\
    }

// knapsack 알고리즘 ( 탐욕 vs 동적계획 )

typedef struct node* treePointer;
typedef struct node {
    int n, w, price;
    treePointer left;
    treePointer right;
}node;
treePointer root;

int* weight; //무게 배열
int* value; //값어치 배열
int* P_0;
int P[MAX][MAX];

//functions
void knapsack(treePointer root); // 트리를 이용한 knapsack 알고리즘
void knapsack_origin(int n, int W); // original knapsack 알고리즘
treePointer createTree(int n, int W);
treePointer createNode(int n, int W);

int main() {
    int n, W, i;
    FILE* f = fopen("input.txt", "r");
    fscanf(f, "%d %d", &n, &W);

    MALLOC(P_0, (W + 1) * sizeof(int));
    MALLOC(weight, (n + 1) * sizeof(int));
    MALLOC(value, (n + 1) * sizeof(int));
    for (i = 1; i <= n; i++) fscanf(f, "%d", &value[i]);
    for (i = 1; i <= n; i++) fscanf(f, "%d", &weight[i]);
    for (i = 0; i <= W; i++) P_0[i] = 0;

    root = createTree(n, W);

    //트리 이용
    knapsack(root);
    printf("The result is: %d\n", root->price);

    /*
    knapsack_origin(n, W);
    printf("The result is: %d\n", P[n][W]);
    */

    free(weight);   free(value);   free(P_0);
    fclose(f);

    return 0;
}

void knapsack(treePointer root) {
    if (root) {
        knapsack(root->left);
        knapsack(root->right);

        if (weight[root->n] <= root->w) { // w_i <= w 일 때
            if (root->left || root->right) // leaf가 아닌 노드면
                root->price = max(root->left->price, root->right->price + value[root->n]);
            else root->price = max(P_0[root->w], P_0[root->w - weight[root->n]] + value[root->n]);// leaf 노드일때
        }
        else { // w_i > w 일 때
            if (root->left || root->right)
                root->price = root->left->price;
            else root->price = P_0[root->w];
        }
    }
}

void knapsack_origin(int n, int w) {
    int i, j;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= w; j++) {
            if (weight[i] > j)
                P[i][j] = P[i - 1][j];
            else
                P[i][j] = max(P[i - 1][j], P[i - 1][j - weight[i]] + value[i]);
        }
    }
}

treePointer createTree(int n, int W) {
    treePointer temp;
    temp = createNode(n, W);

    if (n > 1) {
        temp->left = createTree(n - 1, W);
        temp->right = createTree(n - 1, W - weight[n]);
    }

    return temp;
}

treePointer createNode(int n, int w) {
    treePointer temp;

    MALLOC(temp, sizeof(*temp));

    temp->n = n;  temp->w = w;  temp->price = -1;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}