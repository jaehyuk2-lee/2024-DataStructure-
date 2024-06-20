#include <stdio.h>

int main()
{
    int score[10] = {55, 20, 33, 85, 13, 22, 45, 98, 67, 77};
    int max = 0;
    int max_index;

    for (int i = 0; i < 10; i++)
    {
        printf("%d번 : %d점\n", i, score[i]);
        if (score[i] >= max)
        {
            max_index = i;
            max = score[i];
        }
    }
    printf("1등은 %d번, 점수는 %d 입니다.\n", max_index, score[max_index]);
}