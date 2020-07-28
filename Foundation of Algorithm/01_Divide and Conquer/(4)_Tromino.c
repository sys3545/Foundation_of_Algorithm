#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// 트로미노 알고리즘

void InitBoard(int size);
void fillBoard(int tile_x, int tile_y, int h_x, int h_y, int size);

int** board;
int tilecnt = 0;

int main() {
	int n, size;	
	int i, j;
	int holeX, holeY;
	int k;

	printf("Enter the number of n : ");  scanf_s("%d", &n);
	size = (int)pow(2, n);

	board = (int**)malloc(sizeof(int*)*size);
	for (i = 0; i < size; i++) {
		board[i] = (int*)malloc(sizeof(int)*size);
	}
	InitBoard(size);

	for (k = 0; k < 2; k++) {
		printf("The location of hole : ");  scanf_s("%d %d", &holeX, &holeY);
		tilecnt++;
		fillBoard(0, 0, holeX, holeY, size);
		printf("Floor : \n");
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				printf("%3d ", board[i][j]);
			}
			printf("\n");
		}
		InitBoard(size);
	}

	return 0;
}

void fillBoard(int tile_x, int tile_y, int h_x, int h_y, int size) {
	int i, j;
	int findX, findY;
	int hsize;

	board[h_x][h_y] = 0; // 구멍 설정

	if (size == 2) { // 색칠하는 기본과정
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				if (board[tile_x + i][tile_y + j] != -1) continue; // 구멍이거나 이미 칠해진곳은 제외
				board[tile_x + i][tile_y + j] = tilecnt; //색칠
			}
		}
		tilecnt++;
		return;
	}

	// 주어진 size내에서 구멍의 좌표를 찾는다
	findX = tile_x;
	findY = tile_y;
	for (; findX < tile_x + size; findX++) {
		findY = tile_y;
		for (; findY < tile_y + size; findY++) {
			if (board[findX][findY] != -1) goto EXIT;
		}
	}

EXIT:
	hsize = size / 2; // 분할

	if (!(findX < tile_x + hsize && findY < tile_y + hsize)) board[tile_x + hsize - 1][tile_y + hsize - 1] = tilecnt; // 좌상단에 구멍이 없다면 중앙에 한칸 칠한다.
	if (!(findX >= tile_x + hsize && findY < tile_y + hsize)) board[tile_x + hsize][tile_y + hsize - 1] = tilecnt; // 좌하단에 구멍이 없다면 중앙에 한칸 칠한다.
	if (!(findX < tile_x + hsize && findY >= tile_y + hsize)) board[tile_x + hsize - 1][tile_y + hsize] = tilecnt; // 우상단에 구멍이 없다면 중앙에 한칸 칠한다.
	if (!(findX >= tile_x + hsize && findY >= tile_y + hsize)) board[tile_x + hsize][tile_y + hsize] = tilecnt; // 우하단에 구멍이 없다면 중앙에 한칸 칠한다.
	
	tilecnt++;

	// 재귀 호출
	fillBoard(tile_x, tile_y, h_x, h_y, hsize); // 좌상단 재귀
	fillBoard(tile_x + hsize, tile_y, h_x, h_y, hsize); // 좌하단 재귀
	fillBoard(tile_x, tile_y + hsize, h_x, h_y, hsize); // 우상단 재귀
	fillBoard(tile_x + hsize, tile_y + hsize, h_x, h_y, hsize); // 우하단 재귀
}

void InitBoard(int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			board[i][j] = -1;
		}
	}
	tilecnt = 0;
}