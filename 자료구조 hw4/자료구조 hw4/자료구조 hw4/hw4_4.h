#include <stdlib.h>
#define TABLE_SIZE 1001

typedef struct {
	int key;
	int value;
} element;

element ht[TABLE_SIZE];

int is_made[10000] = { 0 }; // ������ ��ġ�� �ʰ� �����ϱ� ���� �迭

void linear_probing_insert(element item);
void linear_probing_search(element item);

double average_search(); // ��� key ��ȸ�� ���� �Լ�
int worst_search(); // �־��� ��� key ��ȸ�� ���� �Լ�
int search_count; // ��Ƚ���� ���� ����

void show_table();