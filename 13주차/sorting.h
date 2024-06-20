#define SIZE 10
#define EXP_SIZE 10000

#define boolean unsigned char
#define true 1
#define false 0

int original[] = {46, 9, 35, 78, 24, 65, 53, 81, 22, 18};
int* experiment;

int num_compare;

void insertion_sort(int list[], int n, int show);

void quick_sort(int list[], int left, int right, int show);
int partition(int list[], int left, int right);

void merge_sort(int list[], int left, int right, int show);
void merge(int list[], int left, int mid, int right);

void copy_list(int original[], int list[], int n);
void print_list(int list[], int left, int right);

void random_initialize(int list[], int n);