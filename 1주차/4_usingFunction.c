#include <stdio.h>

int find_max(int *, int);

int main()
{
    int score[10] = {55, 20, 33, 85, 13, 22, 45, 98, 67, 77};
    int max_index;

    for (int i = 0; i < 10; i++)
    {
        printf("%d번 : %d점\n", i, score[i]);
    }

    max_index = find_max(score, 10);
    printf("1등은 %d번, 점수는 %d 입니다.\n", max_index, score[max_index]);
}

int find_max(int *arr, int size) {
    int index;
    int max = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            index = i;
            max = arr[i];
        }
    }

    return index;
}