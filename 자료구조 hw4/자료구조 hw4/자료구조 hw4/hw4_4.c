#include <stdio.h>
#include <time.h>
#include "hw4_4.h"

int main() {
	srand(time(NULL));

	for (int i = 0; i < TABLE_SIZE; i++) {
		ht[i].key = -1;
	} // 해쉬 테이블의 key를 -1로 설정해 비어있는 테이블임을 표시한다.

	int select = 0;
	while (select != 1 && select != 2) {
		printf("Input loading density : [1 | 500keys] [2 | 900keys] : ");
		scanf_s("%d", &select);
		if (select != 1 && select != 2) {
			printf("Wrong input\n");
		}
	} // 사용자로부터 1, 2 둘 중 하나를 입력받을 동안 반복한다.
	// 1을 입력 시 500개의 key, 2를 입력 시 900개의 key를 생성한다.

	element item;
	if (select == 1) {
		for (int i = 0; i < 500; i++) {
			item.key = rand() % 10000;
			while (is_made[item.key] != 0) {
				item.key = rand() % 10000;
			}
			is_made[item.key] = 1;
			// key가 겹치지 않도록 난수 생성
			item.value = item.key + 10000;
			linear_probing_insert(item);
			// 500개의 item을 생성해 insert 한다.
		}
	}
	else {
		for (int i = 0; i < 900; i++) {
			item.key = rand() % 10000;
			item.value = item.key + 10000;
			linear_probing_insert(item);
			// 900개의 item을 생성해 insert 한다.
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
	// 주어진 해쉬 함수에 맞게 값을 입력할 index를 설정한다.
	while (ht[index].key != -1) {
		// 해쉬 테이블이 -1일 때 까지(비어있을 때 까지) 아래를 반복한다.
		printf("collision\n"); // -1이 아니라면 이미 값 존재 -> 오버 플로우 발생
		index = (index + 1) % TABLE_SIZE; // 가장 가까운 다음 값 (테이블의 끝이면 맨 위로) 이동

		count++; // 충돌 개수 +1
		if (count == TABLE_SIZE) {
			// 모든 테이블과 충돌이 일어났다면, 테이블이 꽉찬 상태이므로 삽입이 불가능하다.
			printf("hash table full\n");
			return;
		}
	}

	ht[index] = item; // 테이블에 item 삽입
	printf("key: %d, index: %d\n", item.key, index);
}

void linear_probing_search(element item) {
	search_count = 0; // 비교횟수 초기화
	int index = item.key % 1001; // 주어진 해쉬 함수 부터 탐색 시작
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
		// 조건 확인 -> key 비교 따라서 search_count++

		if (search_count == TABLE_SIZE) {
			printf("No such key\n");
			break;
		}
		// TABLE_SIZE 만큼 확인 했다면, 모든 테이블을 확인해도 값이 없기 때문에, 존재하지 않는 값
	}
}

void show_table() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		printf("[index: %d, key:%d, value:%d]\n", i, ht[i].key, ht[i].value);
	}
}

double average_search() {
	double sum = 0;
	int count = 0; //linear_probing_search()가 실행 된 횟수

	for (int i = 0; i < TABLE_SIZE; i++) {
		if (ht[i].key != -1) { // key값이 존재하면 linear_probing_search() 실행
			linear_probing_search(ht[i]);
			sum += search_count;
			count++;
		}
	}
	// 테이블에 존재하는 key에 대해서 linear_probing_search()를 실행, 실행 후 비교 횟수를 sum에 저장
	// search 실행 회수 + 1

	return sum / count; // 실행 횟수에 대한 비교횟수 평균 리턴
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
	// linear_probing_search() 실행 후, 비교 횟수 중 큰 값을 계속 최신화

	return max; // 최대 비교 회수 리턴
}
