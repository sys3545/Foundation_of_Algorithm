#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) ((a)<=(b))? a : b

// 이항 계수 알고리즘

int bin3(int n, int k);

int main() {
	int n, k, result;

	printf("Enter the Number of n: "); scanf("%d", &n);
	printf("Enter the Number of k: "); scanf("%d", &k);

	if (n / 2 > k)
		result = bin3(n, k);
	else
		result = bin3(n, n - k);
	
	printf("binomial coeiffient of(%d,%d) = %d\n", n, k, result);

	return 0;
}

int bin3(int n, int k) {
	int i, j, result;
	int* B;

	B = (int*)calloc((k + 1), sizeof(int));

	for (i = 0; i <= n; i++) {
		for (j = MIN(i,k); j >= 0; j--) {
			if (j == 0 || j == i)
				B[j] = 1;
			else
				B[j] = B[j - 1] + B[j];
		}
	}
	

	result = B[k];

	
	free(B);

	return result;
}