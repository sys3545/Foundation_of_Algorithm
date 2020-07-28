#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define COMPARE(x,y) (((x)>(y))? 1 : ((x)==(y))? 0 : -1 )

// 이진탐색

int binsearch(int left, int right, int searchnum, int S[]);

int main() {
	int S[9] = {12,34,37,45,57,82,99,120,134 };
	
	int result;

	result = binsearch(0, 8, 134, S);

	printf("%d", result);



	return 0;
}




int binsearch(int left, int right, int searchnum, int S[]) {
	int mid;
	if (left > right) return -1;

	else {
		mid = (left + right) / 2;
		switch (COMPARE(S[mid], searchnum)) {
		case -1:
			return binsearch(mid + 1, right, searchnum, S);
			
		case 0:
			return mid;
		case 1:
			return binsearch(left, mid - 1, searchnum, S);
		}
	}
	
}