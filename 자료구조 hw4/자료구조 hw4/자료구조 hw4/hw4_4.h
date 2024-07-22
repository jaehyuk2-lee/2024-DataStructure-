#include <stdlib.h>
#define TABLE_SIZE 1001

typedef struct {
	int key;
	int value;
} element;

element ht[TABLE_SIZE];

int is_made[10000] = { 0 }; // 정수를 겹치지 않게 생성하기 위한 배열

void linear_probing_insert(element item);
void linear_probing_search(element item);

double average_search(); // 평균 key 비교회수 리턴 함수
int worst_search(); // 최악의 경우 key 비교회수 리턴 함수
int search_count; // 비교횟수를 세는 변수

void show_table();