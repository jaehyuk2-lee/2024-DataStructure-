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
	printf("The total number of 'indexed words' is '%d'.\n", total_word); //���ε� �� �ܾ� ��
	printf("------------------------------------------------------\n");
	// �˻�
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
	if ((ifp = fopen(file_name, "r")) == NULL) { //���ϸ� ���� ��� ����
		printf("No such file!\n");
		exit(1);
	}
	while (!feof(ifp)) {
		char buffer[1000];
		while (fgets(buffer, sizeof(buffer), ifp)) {

			// ��ū�� �ϳ��� �о� �ܾ�� ��ȯ
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
				// �ܾ� ��带 ����� �ؽ� 
				if (strcmp(word, "\0") != 0) {
					insert_word(new_node(word, file_name));
				}
				token = strtok(NULL, " "); // ���� ��ū���� ����
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
		// list�� �� ���� ���� index �̵�
		if(!strcmp(ht[index]->link->word, p->word)) { // ���� �ܾ ã���� ��
			WordData* tmp = ht[index]->link;
			while (strcmp(tmp->file_name, p->file_name) && tmp->link != NULL) {
				tmp = tmp->link;
			}
			if (!strcmp(tmp->file_name, p->file_name)) { // ���� �����̶�� freq�� ����
				tmp->freq++;
			}
			else {
				// tmp->link�� NULL �̹Ƿ� �ٸ� ���Ͽ� ����� �ܾ�
				// list�� ���� �տ� ��� insert
				// �������� file�� ������������ ��µǱ� ������ ��带 �տ� �߰��ϴ� ������� insert
				p->link = ht[index]->link;
				ht[index]->link = p; 
			}
			// �̹� ����� �ܾ��̱� ������, total_word�� ����
			return;
		}

		if (cnt == TABLE_SIZE) {
			// TABLE_SIZE��ŭ Ȯ���� �ߴٸ�, ht�� ���� ����
			printf("Hash Table is full \n");
			return;
		}
		index = (index + (++cnt)) % TABLE_SIZE;
	}
	// �� ��忡 p ����
	ht[index] = (WordData*)malloc(sizeof(WordData)); // list ���� ��� ����
	ht[index]->link = p; // link�� ����
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
		// ���� �ܾ ã�� �� ����, index �̵�
		// ���� �ܾ ã�Ҵٸ�, strcmp�� 0�� ���� ������ �ݺ�����

		if (cnt == TABLE_SIZE) {
			// TABLE_SIZE��ŭ Ȯ���� �ߴٸ�, ht�� ���� ����
			printf("Hash Table is full \n");
			return -1;
		}

		if (ht[index] == NULL) { // ��尡 ���ٸ�, �������� ���� �ܾ�
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
	if ((ifp = fopen(file_name, "r")) == NULL) { // ���ϸ��� ���� ��� ����
		printf("No such file!\n");
		exit(1);
	}

	char buffer[1000];
	if (fgets(buffer, sizeof(buffer), ifp) != NULL)
		printf("%s\n", buffer);
	fclose(ifp);
}