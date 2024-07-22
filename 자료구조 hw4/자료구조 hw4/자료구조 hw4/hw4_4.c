#include <stdio.h>
#include <time.h>
#include "hw4_4.h"

int main() {
	srand(time(NULL));

	for (int i = 0; i < TABLE_SIZE; i++) {
		ht[i].key = -1;
	} // �ؽ� ���̺��� key�� -1�� ������ ����ִ� ���̺����� ǥ���Ѵ�.

	int select = 0;
	while (select != 1 && select != 2) {
		printf("Input loading density : [1 | 500keys] [2 | 900keys] : ");
		scanf_s("%d", &select);
		if (select != 1 && select != 2) {
			printf("Wrong input\n");
		}
	} // ����ڷκ��� 1, 2 �� �� �ϳ��� �Է¹��� ���� �ݺ��Ѵ�.
	// 1�� �Է� �� 500���� key, 2�� �Է� �� 900���� key�� �����Ѵ�.

	element item;
	if (select == 1) {
		for (int i = 0; i < 500; i++) {
			item.key = rand() % 10000;
			while (is_made[item.key] != 0) {
				item.key = rand() % 10000;
			}
			is_made[item.key] = 1;
			// key�� ��ġ�� �ʵ��� ���� ����
			item.value = item.key + 10000;
			linear_probing_insert(item);
			// 500���� item�� ������ insert �Ѵ�.
		}
	}
	else {
		for (int i = 0; i < 900; i++) {
			item.key = rand() % 10000;
			item.value = item.key + 10000;
			linear_probing_insert(item);
			// 900���� item�� ������ insert �Ѵ�.
		}
	}

	show_table();

	/*element test;
	test.key = 500;
	linear_probing_search(test);*/

	printf("\nAverage Search Count : %lf\n", average_search());
	printf("Worst Search Count : %d\n", worst_search());
}

void linear_probing_insert(element item) {
	int count = 0;
	int index = item.key % 1001;
	// �־��� �ؽ� �Լ��� �°� ���� �Է��� index�� �����Ѵ�.
	while (ht[index].key != -1) {
		// �ؽ� ���̺��� -1�� �� ����(������� �� ����) �Ʒ��� �ݺ��Ѵ�.
		printf("collision\n"); // -1�� �ƴ϶�� �̹� �� ���� -> ���� �÷ο� �߻�
		index = (index + 1) % TABLE_SIZE; // ���� ����� ���� �� (���̺��� ���̸� �� ����) �̵�

		count++; // �浹 ���� +1
		if (count == TABLE_SIZE) {
			// ��� ���̺�� �浹�� �Ͼ�ٸ�, ���̺��� ���� �����̹Ƿ� ������ �Ұ����ϴ�.
			printf("hash table full\n");
			return;
		}
	}

	ht[index] = item; // ���̺� item ����
	printf("key: %d, index: %d\n", item.key, index);
}

void linear_probing_search(element item) {
	search_count = 0; // ��Ƚ�� �ʱ�ȭ
	int index = item.key % 1001; // �־��� �ؽ� �Լ� ���� Ž�� ����
	while (1) {
		if (ht[index].key == item.key) {
			search_count++;
			// printf("Postion of key : %d\n", index);
			// printf("Search Count   : %d\n", search_count);
			break;
		}
		else if (ht[index].key != item.key) {
			search_count++;
			index = (index + 1) % TABLE_SIZE;
		}
		else if (ht[index].key == -1) {
			search_count++;
			printf("No such key\n");
			break;
		}
		// ���� Ȯ�� -> key �� ���� search_count++

		if (search_count == TABLE_SIZE) {
			printf("No such key\n");
			break;
		}
		// TABLE_SIZE ��ŭ Ȯ�� �ߴٸ�, ��� ���̺��� Ȯ���ص� ���� ���� ������, �������� �ʴ� ��
	}
}

void show_table() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		printf("[index: %d, key:%d, value:%d]\n", i, ht[i].key, ht[i].value);
	}
}

double average_search() {
	double sum = 0;
	int count = 0; //linear_probing_search()�� ���� �� Ƚ��

	for (int i = 0; i < TABLE_SIZE; i++) {
		if (ht[i].key != -1) { // key���� �����ϸ� linear_probing_search() ����
			linear_probing_search(ht[i]);
			sum += search_count;
			count++;
		}
	}
	// ���̺� �����ϴ� key�� ���ؼ� linear_probing_search()�� ����, ���� �� �� Ƚ���� sum�� ����
	// search ���� ȸ�� + 1

	return sum / count; // ���� Ƚ���� ���� ��Ƚ�� ��� ����
}
int worst_search() {
	int max = -1;

	for (int i = 0; i < TABLE_SIZE; i++) {
		if (ht[i].key != -1) {
			linear_probing_search(ht[i]);
			if (max < search_count) {
				max = search_count;
			}
		}
	}
	// linear_probing_search() ���� ��, �� Ƚ�� �� ū ���� ��� �ֽ�ȭ

	return max; // �ִ� �� ȸ�� ����
}
