#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000

void insertion_sort(int list[], int n);
void quick_sort(int list[], int left, int right);
void print(int list);
int compare_count = 0;

int main() {
	srand(time(NULL));

	int TIME = 0;
	

	int list1[SIZE]; // insertion sort 실행 배열
	int list2[SIZE]; // qucik sort 실행 배열

	for (int i = 0; i < SIZE; i++) {
		list1[i] = rand();
		list2[i] = list1[i];
	}

	//print(list1);
	/* Timer on */
	clock_t start = clock(); // 타이머 시작
	insertion_sort(list1, SIZE);
	printf("Insertion Sort : %d\n", compare_count);
	//print(list1);

	TIME += ((int)clock() - start) / (CLOCKS_PER_SEC / 1000);

	printf("TIME : %d ms\n", TIME); /* ms 단위로 출력 */

	TIME = 0;

	compare_count = 0;
	//print(list2);
	start = clock(); // 타이머 시작
	quick_sort(list2, 0, SIZE);
	printf("Quick Sort : %d\n", compare_count);
	//print(list2);

	/* Timer off */
	TIME += ((int)clock() - start) / (CLOCKS_PER_SEC / 1000);
	printf("TIME : %d ms\n", TIME); /* ms 단위로 출력 */

	

}

void insertion_sort(int list[], int n) {
	compare_count = 0;
	for (int i = 1; i < n; i++) {
		int next = list[i];
		for (int j = i; j >= 0; j--) {
			if (list[j-1] < next) {
				list[j] = next;
				break;
			}
			compare_count++;
			list[j] = list[j - 1];
		}
	}
}

void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int pivot = list[left];
		int i = left;
		int j = right;

		while (i < j) {
			while (list[++i] < pivot && i < right)compare_count++;
			while (list[--j] > pivot && j > left)compare_count++;

			if (i < j) {
				compare_count++;
				int tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
		}

		compare_count++;
		int tmp = list[left];
		list[left] = list[j];
		list[j] = tmp;

		quick_sort(list, left, j);
		quick_sort(list, j+1, right);
	}
}

void print(int list[]) {
	for (int i = 0; i < SIZE; i++) {
		printf("%d ", list[i]);
	}
	printf("\n");
}