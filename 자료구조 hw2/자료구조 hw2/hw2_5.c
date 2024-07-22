#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct DListNode {
	char* word;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

DListNode* head=NULL;

const char* fname = "sample.txt";
void text2dlist(const char*);
void print_node();
void print_surrounding_words(char*, int);

int main() {
	text2dlist(fname);
	print_node();
	//print_surrounding_words("data", 2);
	//print_surrounding_words("in", 2);
	//print_surrounding_words("in", 0);
	print_surrounding_words("and", 5);
	// test case, ���μ��� ���� ���Ƽ� �ѹ��� ����
}

void text2dlist(const char* fname) {
	FILE* fp;
	fp = fopen(fname, "r+");

	char paragraph[1500]; // 1500�� ���� ���ڸ� ������ �� �ִ� ���ڿ�, ������ ������ �����ؼ� �����´�.
	fscanf(fp, "%[^\t]s", paragraph);
	// �ܾ�� space�� newline���� ���еǱ� ������ \t�� �Էµ��� �ʴ��� ��� �޾Ƶ��δ�.

	int size = strlen(paragraph);
	for (int i = 0; i<size; i++) {
		if (paragraph[i] == '\n') {
			paragraph[i] = ' ';
		}
	}
	printf("%s\n", paragraph);
	// ���ڿ��� ���Ե� �ٹٲ��� �������� �ٲ� strtok �Լ��� �������� ���ڸ� �ڸ� �� �ֵ��� �����Ѵ�.

	char* ptr = strtok(paragraph, " "); // ������ �������� ���ڿ��� �߶� �ܾ�� �����Ѵ�
	DListNode* new = (DListNode*)malloc(sizeof(DListNode));
	head = new;
	new->word = ptr;
	new->llink = head;
	new->rlink = head;
	ptr = strtok(NULL, " ");
	// �ܾ� �Ѱ��� Node�� ����� �Ҵ��Ѵ�.
	while (ptr != NULL) { // ���̻� ���ڿ��� ������ ���� �� ���� �ݺ��Ѵ�.
		new = (DListNode*)malloc(sizeof(DListNode));
		new->word = malloc(sizeof(char) * strlen(ptr));
		strcpy(new->word, ptr);
		// ������ ���ڿ��� ũ�⸸ŭ word�� ũ�⸦ �����ϰ� ���縦 �����Ѵ�.
		// �����Ҵ��� �����ʰ� new->word = ptr�� �������� �� ptr�� ���� ������ ���� ����� ������ �ִ�.
		new->llink = head->llink;
		new->rlink = head;
		new->llink->rlink = new;
		head->llink = new;

		ptr = strtok(NULL, " ");
	}
	fclose(fp);
}

void print_node() {
	DListNode* tmp;
	tmp = head;

	do {
		printf("word : %s\n", tmp->word);
		tmp = tmp->rlink;
	} while (tmp != head);
}

void print_surrounding_words(char* word, int k) {
	printf("********* Find [%s], Surrounding: %d *******\n", word, k);
	DListNode* tmp;
	tmp = head;
	for (int i = 0; i < k; i++) {
		tmp = tmp->rlink;
	} // �� �ڷ� k���� �ܾ ����ؾ� �Ǳ� ������ k��° Node�� ������ ���ڿ��� ����� �� ����.

	do {
		int is_capitalize = 0; // ù���ڰ� �빮�� �̾����� Ȯ���ϴ� ����
		if (isalpha(tmp->word[0]) == 1) {
			is_capitalize = 1; // ù���ڰ� �빮�ڿ��ٸ� 1�� �Է��Ѵ�.
			tmp->word[0] = tolower(tmp->word[0]);
		} // ���� ù ���ڰ� �빮���̸� ù ���ڸ� �ҹ��ڷ� �����Ѵ�.

		int cnt = 0;
		for (int i = 0; i < k; i++) {
			tmp = tmp->rlink;
			cnt++;
			if (tmp == head) {
				exit(1);
			} // ���������� k�� ���� ���� ��ġ�� head��� ������ ���ڿ��� ������ ���ڶ�� ������
			  // ������ ���ڿ����� ����� �� ����.
			  // print_surrounding_words("and", 5); �� Ȯ���ϸ� ������ ���忡���� �ʰ��ż� ��µ��� �ʴ´�.
		}

		for (int i = 0; i < cnt; i++) {
				tmp = tmp->llink;
		} // Ȯ���ߴ� node�� �ٽ� ������� ������

		if (strstr(tmp->word, word)!=NULL) {
			// tmpw->word�ȿ� word�� �����Ѵٸ� �ּҸ� ��ȯ�ϴ� ����
			// data, �� ���� ���Ե� ����̱� ������ ã�����ϴ� ���ڿ��� ���Խ�Ų��.

			char* check = malloc(sizeof(char)*(strlen(tmp->word)));
			// Ư������(��ȣ, ��ǥ, ����) ���� ������ ���ڸ� ������ ���ڿ�
			strcpy(check, tmp->word);
			int size = strlen(check);
			for (int i = 0; i<size; i++) {
				if (isalpha(tmp->word[i]) == 0) {
					for (int j = i; j < size - 1; j++) {
						check[j] = check[j + 1];
					}
					check[size-1] = '\0';
					size--;
				}
			}

			if (strcmp(check, word)) {
				tmp = tmp->rlink;
				continue;
			}
			// Ư�����ڸ� ������ ���ڿ��� ã�� ���ڿ��� ���� ������
			// define, inó�� ���ڿ��ȿ� ã�� ���ڿ��� ���Ե� ����̹Ƿ� �����Ѵ�
			// print_surrounding_words("in", 2)�� Ȯ���ϸ� define, index ���� �������� �ʴ� ���� Ȯ���� �� �ִ�.

			if (is_capitalize == 1) { // ������ 1�� ����Ǿ������� �빮�ڷ� �����ϴ� ���ڿ��̴�.
				tmp->word[0] = toupper(tmp->word[0]); // ���۹��ڸ� �ٽ� �빮�ڷ� �����Ѵ�.
			}

			for (int i = 0; i < k; i++) {
				tmp = tmp->llink;
			}
			for (int i = 0; i < (2*k)+1; i++) {
				printf("%s ", tmp->word);
				tmp = tmp->rlink;
			}
			printf("\n");
			for (int i = 0; i < k+1; i++) {
				tmp = tmp->llink;
			}
		}
		tmp = tmp->rlink;
	} while (tmp != head);
}