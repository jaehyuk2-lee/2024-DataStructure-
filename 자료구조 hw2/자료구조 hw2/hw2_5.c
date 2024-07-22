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
	// test case, 프로세스 양이 많아서 한번만 실행
}

void text2dlist(const char* fname) {
	FILE* fp;
	fp = fopen(fname, "r+");

	char paragraph[1500]; // 1500자 까지 글자를 저장할 수 있는 문자열, 파일의 내용을 복사해서 가져온다.
	fscanf(fp, "%[^\t]s", paragraph);
	// 단어는 space나 newline으로 구분되기 때문에 \t이 입력되지 않는한 모두 받아들인다.

	int size = strlen(paragraph);
	for (int i = 0; i<size; i++) {
		if (paragraph[i] == '\n') {
			paragraph[i] = ' ';
		}
	}
	printf("%s\n", paragraph);
	// 문자열에 포함된 줄바꿈을 공백으로 바꿔 strtok 함수가 공백으로 문자를 자를 수 있도록 수정한다.

	char* ptr = strtok(paragraph, " "); // 공백을 기준으로 문자열을 잘라서 단어로 저장한다
	DListNode* new = (DListNode*)malloc(sizeof(DListNode));
	head = new;
	new->word = ptr;
	new->llink = head;
	new->rlink = head;
	ptr = strtok(NULL, " ");
	// 단어 한개당 Node를 만들어 할당한다.
	while (ptr != NULL) { // 더이상 문자열이 나오지 않을 때 까지 반복한다.
		new = (DListNode*)malloc(sizeof(DListNode));
		new->word = malloc(sizeof(char) * strlen(ptr));
		strcpy(new->word, ptr);
		// 복사할 문자열의 크기만큼 word의 크기를 설정하고 복사를 시행한다.
		// 동적할당을 하지않고 new->word = ptr로 수행했을 시 ptr에 의해 복사한 값이 변경될 위험이 있다.
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
	} // 앞 뒤로 k개의 단어를 출력해야 되기 때문에 k번째 Node전 까지는 문자열을 출력할 수 없다.

	do {
		int is_capitalize = 0; // 첫문자가 대문자 이었는지 확인하는 변수
		if (isalpha(tmp->word[0]) == 1) {
			is_capitalize = 1; // 첫문자가 대문자였다면 1을 입력한다.
			tmp->word[0] = tolower(tmp->word[0]);
		} // 제일 첫 문자가 대문자이면 첫 문자를 소문자로 변경한다.

		int cnt = 0;
		for (int i = 0; i < k; i++) {
			tmp = tmp->rlink;
			cnt++;
			if (tmp == head) {
				exit(1);
			} // 오른쪽으로 k번 갔을 때의 위치가 head라면 오른쪽 문자열의 개수가 모자라기 때문에
			  // 이후의 문자열들은 출력할 수 없다.
			  // print_surrounding_words("and", 5); 로 확인하면 마지막 문장에서는 초과돼서 출력되지 않는다.
		}

		for (int i = 0; i < cnt; i++) {
				tmp = tmp->llink;
		} // 확인했던 node를 다시 원래대로 돌린다

		if (strstr(tmp->word, word)!=NULL) {
			// tmpw->word안에 word가 존재한다면 주소를 반환하는 조건
			// data, 과 같이 포함된 경우이기 때문에 찾고자하는 문자열에 포함시킨다.

			char* check = malloc(sizeof(char)*(strlen(tmp->word)));
			// 특수문자(괄호, 쉼표, 온점) 등을 제거한 문자를 저장할 문자열
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
			// 특수문자를 제거한 문자열이 찾는 문자열과 같지 않으면
			// define, in처럼 문자열안에 찾는 문자열이 포함된 경우이므로 생략한다
			// print_surrounding_words("in", 2)로 확인하면 define, index 등은 포함하지 않는 것을 확인할 수 있다.

			if (is_capitalize == 1) { // 변수에 1이 저장되어있으면 대문자로 시작하는 문자열이다.
				tmp->word[0] = toupper(tmp->word[0]); // 시작문자를 다시 대문자로 수정한다.
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