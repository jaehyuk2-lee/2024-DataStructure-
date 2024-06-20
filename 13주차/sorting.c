#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

int main() {
    int list[SIZE], n = SIZE;
    int exp_list[EXP_SIZE];

    printf("\n----- insertion sort -----\n");
    copy_list(original, list, n);
    print_list(list, 0, n-1);
    num_compare = 0;
    insertion_sort(list, n, 1);
    printf("\n");
    print_list(list,0,n-1);
    printf("\nTotal number of comparison = %d\n", num_compare);

    printf("\n----- quick sort -----\n");
    copy_list(original, list, n);
    print_list(list, 0, n-1);
    num_compare = 0;
    quick_sort(list, 0, n-1, 1);
    printf("\n");
    print_list(list,0,n-1);
    printf("\nTotal number of comparison = %d\n", num_compare);


    printf("\n----- merge sort -----\n");
    copy_list(original, list, n);
    print_list(list, 0, n-1);
    num_compare = 0;
    merge_sort(list, 0, n-1, 1);
    printf("\n");
    print_list(list,0,n-1);
    printf("\nTotal number of comparison = %d\n", num_compare);

    for(int i = 1; i <= 10; i++) {
        n = i * 1000;
        experiment = (int*)malloc(sizeof(int)*n);

        printf("\n----- n = %d ----- \n", n);
        random_initialize(experiment, n);

        copy_list(experiment, exp_list, n);
        num_compare = 0;
        insertion_sort(exp_list, n, 0);
        printf("\n No. of comparison (insertion sort) = %d\n", num_compare);

        copy_list(experiment, exp_list, n);
        num_compare = 0;
        quick_sort(exp_list, 0, n-1, 0);
        printf("\n No. of comparison (quick sort) = %d\n", num_compare);

        copy_list(experiment, exp_list, n);
        num_compare = 0;
        merge_sort(exp_list, 0, n-1, 0);
        printf("\n No. of comparison (merge sort) = %d\n", num_compare);
        free(experiment);
    }
}

void insertion_sort(int list[], int n, int show) {
    for(int i = 1; i < n; i++) {
        int next = list[i];
        int j;
        for(j = i-1; j >= 0 && next < list[j]; j--) {
           list[j+1] = list[j];
           num_compare++;
        }
        list[j+1] = next;
        if(show == 1) {
            print_list(list, 0, n-1);
        }
    }
}

void quick_sort(int list[], int left, int right, int show) {
    if(left < right) {
        int mid = partition(list, left, right);
        if(show == 1) {
            print_list(list, left, right);
        }

        quick_sort(list, left, mid-1, show);
        quick_sort(list, mid+1, right, show);
    }
}
int partition(int list[], int left, int right) {
    int i = left;
    int j = right+1;

    int pivot = list[left];

    while(i < j) {
        while(++i <= right && list[i] < pivot);
        while(--j >= left && list[j] > pivot);

        if(i < j) {
            int tmp = list[i];
            list[i] = list[j];
            list[j] = tmp;
        }
        num_compare++;
    }
    
    int tmp = list[left];
    list[left] = list[j];
    list[j] = tmp;
    num_compare++;

    return j;
}

void merge_sort(int list[], int left, int right, int show){
    if(left < right) {
        int mid = (left+right)/2;
        
        merge_sort(list, left, mid, show);
        merge_sort(list, mid+1, right, show);
        merge(list, left, mid, right);
        if(show == 1) {
            print_list(list, left, right);
        }
    }
}
void merge(int list[], int left, int mid, int right) {
    int sorted[EXP_SIZE];
    copy_list(list, sorted, right);

    int i = left;
    int j = mid+1;
    int k = left;

    while(i <= mid && j <= right) {
        if(list[i] < list[j]) sorted[k++] = list[i++];
        else sorted[k++] = list[j++];
        num_compare++;
    }
    if(i > mid) for(int n = j; n <= right; n++) sorted[k++] = list[n];
    else for(int n = i; n <= mid; n++) sorted[k++] = list[n];

    for(int n = left; n <= right; n++) {
        list[n] = sorted[n];
    }
}

void copy_list(int original[], int list[], int n) {
    for(int i = 0; i < n; i++) {
        list[i] = original[i];
    }
}
void print_list(int list[], int left, int right) {
    for(int i = 0; i < left; i++) {
        printf("    ");
    }
    for(int i = left; i <= right; i++) {
        printf("%4d", list[i]);
    }
    printf("\n");
}

void random_initialize(int list[], int n) {
    for(int i = 0; i < n; i++) {
        list[i] = rand();
    }
}