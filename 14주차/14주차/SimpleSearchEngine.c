#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SimpleSearchEngine.h"

int main() {
	int word_index;

	printf("-----------------------------------------\n");
	printf("Start indexing.....");

	char* file_name;
	for (int i = 1; i <= 10; i++) {
		file_name = (char*)malloc(sizeof(char) * 20);
		sprintf(file_name, "doc%03d.txt", i);
		make_index(file_name);
	}
	printf("successfully indexed all \n");
	printf("The total number of 'indexed words' is '%d'.\n", total_word); //색인된 총 단어 수
	printf("------------------------------------------------------\n");
	// 검색
	while (1) {
		printf("\nSearch keyword: ");
		char keyword[100];
		scanf("%s", keyword);
		if (strcmp(keyword, ".") == 0) return; // quit command

		for (int i = 0; keyword[i] != '\0'; i++) {
			keyword[i] = toupper(keyword[i]);
		}

		printf("\n---------------------- Result ------------------------\n");
		word_index = search_word(keyword);
		if (word_index != -1)
			print_result(word_index);
		printf("\n------------------------------------------------------\n");
	}
}

void make_index(char* file_name) {
	FILE* ifp;
	if ((ifp = fopen(file_name, "r")) == NULL) { //파일명 없는 경우 종료
		printf("No such file!\n");
		exit(1);
	}
	while (!feof(ifp)) {
		char buffer[1000];
		while (fgets(buffer, sizeof(buffer), ifp)) {

			// 토큰을 하나씩 읽어 단어로 변환
			char* token = strtok(buffer, " ");
			while (token != NULL) {
				char* word = (char*)malloc(sizeof(char) * 100);
				int j = 0;
				for (int i = 0; token[i]; i++) {
					if (isalpha(token[i])) {
						word[j] = toupper(token[i]);
						j++;
					}
				}
				word[j] = '\0';
				// 단어 노드를 만들어 해싱 
				if (strcmp(word, "\0") != 0) {
					insert_word(new_node(word, file_name));
				}
				token = strtok(NULL, " "); // 다음 토큰으로 진행
			}
		}
	}
	fclose(ifp);
}

WordData* new_node(char* word, char* file_name) {
	WordData* temp;
	temp = (WordData*)malloc(sizeof(WordData));

	temp->word = word;
	temp->file_name = file_name;
	temp->freq = 1;
	temp->link = NULL;
	return temp;
}

void insert_word(WordData* p) {
	int index = hash(p->word);
	int cnt = 0;
	while (ht[index] != NULL) {
		// list의 빈 공간 까지 index 이동
		if(!strcmp(ht[index]->link->word, p->word)) { // 같은 단어를 찾았을 때
			WordData* tmp = ht[index]->link;
			while (strcmp(tmp->file_name, p->file_name) && tmp->link != NULL) {
				tmp = tmp->link;
			}
			if (!strcmp(tmp->file_name, p->file_name)) { // 같은 파일이라면 freq만 증가
				tmp->freq++;
			}
			else {
				// tmp->link가 NULL 이므로 다른 파일에 저장된 단어
				// list의 제일 앞에 노드 insert
				// 문제에서 file이 내림차순으로 출력되기 때문에 노드를 앞에 추가하는 방식으로 insert
				p->link = ht[index]->link;
				ht[index]->link = p; 
			}
			// 이미 저장된 단어이기 때문에, total_word는 유지
			return;
		}

		if (cnt == TABLE_SIZE) {
			// TABLE_SIZE만큼 확인을 했다면, ht에 공간 없음
			printf("Hash Table is full \n");
			return;
		}
		index = (index + (++cnt)) % TABLE_SIZE;
	}
	// 빈 노드에 p 연결
	ht[index] = (WordData*)malloc(sizeof(WordData)); // list 더미 노드 생성
	ht[index]->link = p; // link에 연결
	total_word++;
}

int hash(char* word) {
	int sum = 0;
	for (int i = 0; word[i]; i++) {
		sum += word[i];
	}
	return sum;
}

int search_word(char* word) {
	int index = hash(word);
	int cnt = 0;
	while (strcmp(ht[index]->link->word, word)) {
		// 같은 단어를 찾을 때 까지, index 이동
		// 같은 단어를 찾았다면, strcmp가 0의 값을 리턴해 반복종료

		if (cnt == TABLE_SIZE) {
			// TABLE_SIZE만큼 확인을 했다면, ht에 공간 없음
			printf("Hash Table is full \n");
			return -1;
		}

		if (ht[index] == NULL) { // 노드가 없다면, 존재하지 않은 단어
			printf("No Such Word \n");
			return -1;
		}

		index = (index + (++cnt)) % TABLE_SIZE;
	}
	
	return index;
}
void print_result(int index) {
	WordData* tmp = ht[index]->link;

	while (tmp) {
		printf("< file name : %s , frequency : %d >\n", tmp->file_name, tmp->freq);
		print_first_sentence(tmp->file_name);
		tmp = tmp->link;
	}
}
void print_first_sentence(char* file_name) {
	FILE* ifp;
	if ((ifp = fopen(file_name, "r")) == NULL) { // 파일명이 없는 경우 종료
		printf("No such file!\n");
		exit(1);
	}

	char buffer[1000];
	if (fgets(buffer, sizeof(buffer), ifp) != NULL)
		printf("%s\n", buffer);
	fclose(ifp);
}