#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define HEAP_FULL(num) (num == MAX-1)
#define MAX 100
#define TRUE 1
#define FALSE 0
#define MALLOC(p,s)\
 if(!((p)=malloc(s))){\
    fprintf(stderr,"Insufficient memory");\
    exit(EXIT_FAILURE);\
    }

// 0-1 knapsack of Branch and Bound

typedef struct {
    int level;
    int profit;
    int weight;
    float bound;
	int items[MAX];
}node;

node heap[MAX]; //Max Heap
int num = 0; // Heap size
int n, W, maxprofit, * bestitems;

//functions 
void knapsack(int n, int W, int* p, int* w); // knapsack
float bound(node u, int* p, int* w); // bound 계산
void push(node item, int* num); // heap push
node pop(int* num); //heap pop

int main() {
    int i;
    int* p, * w;
    FILE* f = fopen("input.txt", "r");

    fscanf(f, "%d %d", &n, &W);
    MALLOC(p, (n + 1) * sizeof(*p));
	MALLOC(w, (n + 1) * sizeof(*w));
	MALLOC(bestitems, (n + 1) * sizeof(*bestitems));
    for (i = 1; i <= n; i++) fscanf(f, "%d", &p[i]);
    for (i = 1; i <= n; i++) fscanf(f, "%d", &w[i]);
	
    knapsack(n, W, p, w);

    return 0;
}

void knapsack(int n, int W, int* p, int* w) {
	int i;
    node u, v;

	maxprofit = 0;
	for (i = 0; i <= n; i++) { // 초기화
		u.items[i] = FALSE;
		v.items[i] = FALSE;
	}

	v.level = 0;  v.profit = 0;  v.weight = 0;  v.bound = bound(v, p, w);  // root node
	push(v, &num);

	while (num != 0) {
		v = pop(&num);
		printf("level : %d (%2d %3d %7.2f) maxprofit = %d \n", v.level, v.profit, v.weight, v.bound, maxprofit);

		if (v.bound > maxprofit) {
			u.level = v.level + 1;  
			u.weight = v.weight + w[u.level];
			u.profit = v.profit + p[u.level];
			for (i = 1; i <= n; i++) u.items[i] = v.items[i]; //아이템 복사
			u.items[u.level] = TRUE;
			u.bound = bound(u, p, w);
			if (u.weight <= W && u.profit > maxprofit) {
				maxprofit = u.profit;
				for (i = 1; i <= n; i++) bestitems[i] = u.items[i];
			}
			if (u.bound > maxprofit) push(u, &num); // 아이템을 담은 경우
			
			u.level = v.level + 1;
			u.weight = v.weight;
			u.profit = v.profit;
			for (i = 1; i <= n; i++) u.items[i] = v.items[i]; //아이템 복사
			u.items[u.level] = FALSE;
			u.bound = bound(u, p, w);
			if (u.bound > maxprofit) push(u, &num); // 아이템을 담지 않은 경우
		}
	}
	printf("maxprofit = %d\n", maxprofit);
	printf("bestitems : ");
	for (i = 1; i <= n; i++)
		if (bestitems[i] == TRUE)
			printf("(%d, %d) ", w[i], p[i]);
}

float bound(node u, int *p, int *w) {
	int j, k, totweight;
	float result;

	if (u.weight >= W) return 0;
	else {
		result = (float)u.profit;
		j = u.level + 1;
		totweight = u.weight;
		while (j <= n && totweight + w[j] <= W) {
			totweight = totweight + w[j];
			result += p[j];
			j++;
		}
		k = j;
		if (k <= n)
			result += (W - totweight) * (p[k] / w[k]);

		return result;
	}
}

/////////////// heap operation ////////////////////
void push(node item, int* num) {
	int i;
	if (HEAP_FULL(*num)) {
		fprintf(stderr, "Heap is full.\n");
		exit(EXIT_FAILURE);
	}
	//printf("push %d\n", item.level);
	i = ++(*num);
	while ((i != 1) && item.bound > heap[i / 2].bound) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

node pop(int* num) {
	int parent, child;
	node item, temp;

	if (!(*num)) {
		fprintf(stderr, "Heap is empty\n");
		exit(EXIT_FAILURE);
	}

	item = heap[1]; // 우선순위가 제일 높은 요소
	temp = heap[(*num)--]; // 우선순위가 제일 낮은 요소
	parent = 1;  child = 2;
	while (child <= *num) {
		// 자식 중에서 값이 더 큰 자식을 찾는다.
		if ((child < *num) && (heap[child].bound < heap[child + 1].bound)) child++;
		// 레벨을 따라 temp가 들어갈 위치를 지정
		if (temp.bound >= heap[child].bound) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	//printf("pop %d\n", item.level);
	return item;
}