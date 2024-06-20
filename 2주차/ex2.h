#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct
{
    char name[10];
    int id;
    char grade[4];
} StudentRecord;

StudentRecord r[MAX];
int num_record = 0;
const char *fname = "grade.txt";

void read_record(const char *fname);
void print_record();
void search_record();
void change_record();
void write_record(const char *fname);
void selecton_sort(StudentRecord arr[], int n);
void swap(StudentRecord* a, StudentRecord* b);