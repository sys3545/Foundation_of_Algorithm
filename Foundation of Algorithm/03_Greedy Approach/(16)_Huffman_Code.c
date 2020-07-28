#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 200
#define TRUE 1
#define FALSE 0
#define HEAP_FULL(n) (n == MAX-1)
#define MALLOC(p,s)\
 if(!((p)=malloc(s))){\
    fprintf(stderr,"Insufficient memory");\
    exit(EXIT_FAILURE);\
    }

// 허프만 코드 ( 코드 암호화, 복호화 )

//Tree
typedef struct node* nodePointer;
typedef struct node {
	char symbol;
	int freq;
	nodePointer left;
	nodePointer right;
}nodeType;
nodePointer root;
nodeType tempArr[26]; //각 단어에 해당하는 빈도수를 임시저장 해놓는 배열
int tempIndex = 0; // tempArr배열에 단어를 추가할 때 그 index를 가르쳐줌

//Min Heap
nodePointer heap[MAX];
int n = 0; // size

char huffmanCode[26][MAX]; // 알파벳에 해당하는 허프만 코드를 저장 ( 1~26 = a~z )
char input[MAX]; // input
char output[MAX]; // output
char codestr[MAX]; //각 문자에 해당하는 허프만코드를 일시적으로 저장
char original[MAX]; // 복호화시킨 원래 문자열
int codeN = -1;

//Functions
nodePointer huffman(); // min heap에서 pop하면서 허프만 트리 구조 생성
void traverse(nodePointer node, char codestr[], int codeN); // 트리를 순회하며 각 문자에 해당하는 허프만코드를 저장
void encode(char input[], char output[]); // 암호화
void decode(nodePointer root, char input[], char output[]); //복호화
nodePointer createNode(nodeType item);
int isIn(char symbol, nodeType tmepArr[]); // tempArr에 symbo;이 존재하는가?
int find(char symbol); // tempArr배열에서 symbol이 위치한 index를 반환
int sizeofTemp(nodeType tempArr[]); // 배열의 사이즈를 반환
void push(nodePointer item, int* n);
nodePointer pop(int* n);

int main() {

	printf("Enter the words : ");  gets_s(input, MAX - 1);

	encode(input, output);

	decode(root, input, output);

	return 0;
}

void encode(char input[], char output[]) {
	int index, i = 0;
	nodePointer temp;

	while (input[i] != '\0') { // input을 순회하면서 make tempArr
		if (isIn(input[i], tempArr)) { // input[i]가 tempArr에 존재하면 그 녀석의 인덱스를 찾고 해당 빈도수를 증가
			index = find(input[i]);
			tempArr[index].freq++;
		}
		else { // input[i]가 tempArr에 존재하지 않으면 추가
			tempArr[tempIndex].symbol = input[i];
			tempArr[tempIndex++].freq++;
		}
		i++;
	}

	for (i = 0; i < sizeofTemp(tempArr); i++) { // tempArr에 있는 요소들을 순회하면서 초기 min heap 구성(빈도수가 적은 것들이 상위에 존재해야함)
		temp = createNode(tempArr[i]);
		push(temp, &n);
	}

	root = huffman(); // make tree

	printf("\nHuffman code\n");
	traverse(root, codestr, codeN); // 트리를 순회하며 각 문자에 해당하는 허프만코드를 저장

	index = strlen(input);
	for (i = 0; i < index; i++) //input을 순회하며 해당 문자에 일치하는 허프만코드를 output에 이어 붙혀서 이진 코드 완성
		strcat(output, huffmanCode[input[i] - 'A']);

	printf("\n\nResult of Encoding :\n");
	printf("%s\n\n", output);
	
}

nodePointer huffman() {
	int i;
	nodePointer p, q, r;
	nodeType item;

	for (i = 1; i <= sizeofTemp(tempArr) - 1; i++) {
		p = pop(&n);
		q = pop(&n);
		item.freq = p->freq + q->freq;
		r = createNode(item);
		r->left = p;
		r->right = q;
		push(r, &n);
	}

	return pop(&n);
}

void decode(nodePointer root, char input[], char output[]) {
	int i = 0, j = 0; // j는 original의 인덱스
	nodePointer current;

	current = root;
	while (output[i] != '\0') {
		if (output[i] == '0')
			current = current->left;
		else if (output[i] == '1')
			current = current->right;

		if (!current->left && !current->right) { //leaf에 도착하면 original배열에 저장
			original[j++] = current->symbol;
			current = root; //다시 루트로 간다
		}
		i++;
	}

	printf("Result of Decoding: \n");
	printf("%s\n", original);
}

void traverse(nodePointer node, char codestr[], int codeN) {
	if (node) {
		codeN++;
		codestr[codeN] = '0';
		traverse(node->left, codestr, codeN);
		codestr[codeN] = '1';
		traverse(node->right, codestr, codeN);
		codestr[codeN] = '\0';
		if (node->left == NULL || node->right == NULL) { // leaf노드에 도착하면
			printf("%c : ", node->symbol); // 해당하는 문자 출력
			for (int i = 0; i < codeN; i++) 
				printf("%c", codestr[i]); // 문자에 해당하는 허프만 이진코드 출력
			printf("\n");
			strcpy(huffmanCode[(node->symbol) - 'A'], codestr); //허프만코드를 각 알파벳에 해당하는 인덱스에 저장
		}
	}
}

nodePointer createNode(nodeType item) {
	nodePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->freq = item.freq;
	temp->symbol = item.symbol;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

/////////////// heap operation////////////////////
void push(nodePointer item, int* n) {
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "Heap is full.\n");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);
	while ((i != 1) && item->freq < heap[i / 2]->freq) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

nodePointer pop(int* n) {
	int parent, child;
	nodePointer item, temp;

	if (!(*n)) {
		fprintf(stderr, "Heap is empty\n");
		exit(EXIT_FAILURE);
	}
	item = heap[1]; // 우선순위가 제일 높은 요소
	temp = heap[(*n)--]; // 우선순위가 제일 낮은 요소
	parent = 1;  child = 2;
	while (child <= *n) {
		// 자식 중에서 더 값이 더 작은 자식을 찾는다.
		if ((child < *n) && (heap[child]->freq > heap[child + 1]->freq)) child++;
		// 레벨을 따라 temp가 들어갈 위치를 지정
		if (temp->freq <= heap[child]->freq) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;

	return item;
}

int isIn(char symbol, nodeType tempArr[]) {
	int i;
	for (i = 0; i < sizeofTemp(tempArr); i++)
		if (tempArr[i].symbol == symbol) return TRUE;

	return FALSE;
}

int find(char symbol) {
	int i;

	for (i = 0; i < sizeofTemp(tempArr); i++)
		if (tempArr[i].symbol == symbol) break;

	return i;
}

int sizeofTemp(nodeType tempArr[]) {
	int i = 0;

	while (1) {
		if (tempArr[i].freq == 0)break;
		i++;
	}

	return i;
}