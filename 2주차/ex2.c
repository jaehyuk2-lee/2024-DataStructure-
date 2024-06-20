#include "ex2.h"

int main() {
    char c;
    printf("Reading record from %s\n", fname);
    read_record(fname);
    printf("%d records have read\n", num_record);

    printf("********** 명령어 **********\n");
    printf("P: Print all records\n");
    printf("S: Search record\n");
    printf("C: Change record\n");
    printf("W: Write record\n");
    printf("T: Sort all records\n");
    printf("Q: Save and quit\n");
    printf("****************************\n");

    while(1) {
        printf("\nCommand>");
        c = getchar();
        c = toupper(c);
        printf("\n");

        switch (c)
        {
        case 'P':
            print_record();
            break;
        case 'S':
            search_record();
            break;
        case 'C':
            change_record();
            break;
        case 'W':
            write_record(fname);
            break;
        case 'T':
            selecton_sort(r, 10);
            break;
        case 'Q':
            printf("\n");
            exit(1);
            break;
        default:
            break;
        }
        while(getchar() != '\n');
    }

    return 0;
}

void print_record() {
    printf("----------------------------------\n");
    for(int i = 0; r[i].id != 0; i++) {
        printf("%10s %d           %s\n", r[i].name, r[i].id, r[i].grade);
    }
    printf("----------------------------------\n");
}

void search_record() {
    char name[10];
    printf("Search name: ");
    scanf("%s", name);
    for(int i = 0; i < MAX; i++) {
        if(!strcmp(r[i].name, name)){
            printf("  Name:  %s\n", r[i].name);
            printf("  ID:    %d\n", r[i].id);
            printf("  Grade: %s\n", r[i].grade);
            break;
        }

        if (r[i].id == 0) {
            printf("  Unfounded\n");
            break;
        }
    }    
}

void change_record() {
    char name[10];
    char grade[4];
    printf(" Name: ");
    scanf("%s", name);
    for(int i = 0; i < MAX; i++) {
        if(!strcmp(r[i].name, name)) {
            printf(" grade: ");
            scanf("%s", grade);
            strcpy(r[i].grade, grade);
            break;
        }

        if(r[i].id == 0) {
            printf("  Unfounded\n");
            break;
        }
    }
}

void read_record(const char *fname) {
    int i = 0;
    FILE *ifp;

    ifp = fopen(fname, "r");
    while(fscanf(ifp, "%s %d %s", r[i].name, &r[i].id, r[i].grade) == 3) {
        ++i;
    }
    num_record = i;
    fclose(ifp);
}

void write_record(const char* fname) {
    int i = 0;
    FILE *ofp;

    ofp = fopen(fname, "w");
    for(i = 0; r[i].id != 0; i++) {
        fprintf(ofp, "%s %d %s\n", r[i].name, r[i].id, r[i].grade);
    }

    printf("%d records have written to %s", i, fname);
    fclose(ofp);
}

void selecton_sort(StudentRecord arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[j].id < arr[i].id) {
                swap(&arr[j], &arr[i]);
            }
        }
    }
}

void swap(StudentRecord* a, StudentRecord* b) {
    StudentRecord tmp;
    strcpy(tmp.name, a->name);
    tmp.id = a->id;
    strcpy(tmp.grade, a->grade);

    strcpy(a->name, b->name);
    a->id = b->id;
    strcpy(a->grade, b->grade);

    strcpy(b->name, tmp.name);
    b->id = tmp.id;
    strcpy(b->grade, tmp.grade);
}