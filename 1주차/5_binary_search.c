#include <stdio.h>

int bs(int*, int, int, int);

int main() {
    int a[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int search_num;
    int search_index;

    printf("  i :\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
    printf("a[i]: ");
    for (int i = 0; i < 10; i++) {
        printf("\t%d", a[i]);
    }
    printf("\n");

    printf("Search number: ");
    scanf("%d" ,&search_num);

    search_index = bs(a, search_num, 0, 9);
    printf("%d is in a[%d]\n", search_num, search_index);

    return 0;
}

int bs(int *arr, int num, int left, int right) {
    printf("Call to binary_search with inex[%d, %d]\n", left, right);
    int middle = (left+right)/2;

    if (arr[middle] == num) {
        return middle;
    }
    else if(arr[middle] > num) {
        return bs(arr, num, left, middle-1);
    }
    else {
        return bs(arr, num, middle+1, right);
    }
}