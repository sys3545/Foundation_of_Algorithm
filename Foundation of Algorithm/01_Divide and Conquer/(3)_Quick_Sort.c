#include<stdio.h>
#define SWAP(x,y,t) ( (t)=(x) , (x)=(y) , (y)=(t) )

// 퀵 소트

int S[] = { -1,15,22,13,27,12,10,20,25 }; // 1 ~ 8

void quickSort(int low, int high);
void partition(int low, int high, int *pivotPoint);


int main() {
	int i;
	for (i = 1; i <= 8; i++) {
		printf("%d ", S[i]);
	}
	printf("\n");

	quickSort(1, 8);

	for (i = 1; i <= 8; i++) {
		printf("%d ", S[i]);
	}
	printf("\n");

	return 0;
}

void quickSort(int low, int high) {
	int pivotPoint;

	if (low < high) {
		partition(low, high, &pivotPoint);
		quickSort(low, pivotPoint - 1);
		quickSort(pivotPoint + 1, high);
	}
}

void partition(int low, int high, int* pivotPoint) {
	int i, j, temp;
	int pivotItem = S[low];
	j = low;
	for (i = low + 1; i <= high; i++) {
		if (S[i] < pivotItem) {
			j++;
			SWAP(S[i], S[j], temp);
		}
	}
	*pivotPoint = j;
	SWAP(S[low], S[*pivotPoint], temp); // 피봇을 가운데로 옮긴다.
}