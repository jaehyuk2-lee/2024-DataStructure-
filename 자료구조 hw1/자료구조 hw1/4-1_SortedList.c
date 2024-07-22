// slist_deletemax를 최소화하기위한 전략
// 입력받는 값들을 p를 기준으로 오름차순으로 입력을 받는다면 p가 큰것 우선, 최근에 입력받은 것을 우선으로 출력해
// slist_deletemax의 TimeComplexity를 O(1)로 기대할 수 있다.
#include <stdio.h>
#define MAX_SIZE 100 // SortedList의 최대 저장 가능 개수
typedef struct
{
    int p;
    int id; // 우선순위(p)와 값(id)를 저장하는 구조체
} Element;
typedef struct {
    Element arr[MAX_SIZE]; // Element 자료형을 저장하는 배열
    int size;
} SortedList;
void init_slist(SortedList*);
int is_empty(SortedList*);
int is_full(SortedList*);
void slist_insert(SortedList*, Element);
Element slist_deletemax(SortedList*);
void printElement(Element); // Element의 p와 id를 출력하기 위한 함수
int main() {
    Element e, next;
    SortedList a;
    init_slist(&a);
    e.p = 2; e.id = 100; slist_insert(&a, e);
    e.p = 1; e.id = 101; slist_insert(&a, e);
    e.p = 3; e.id = 102; slist_insert(&a, e);
    e.p = 1; e.id = 103; slist_insert(&a, e);
    printf("\n");
    next = slist_deletemax(&a);
    printElement(next);
    printf("\n");
    next = slist_deletemax(&a);
    printElement(next);
    printf("\n");
    return 0;
}
void init_slist(SortedList* a) {
    a->size = 0; // 현재 저장된 값 0개로 설정
}
int is_empty(SortedList* a) {
    if (a->size <= 0) return 1;
    else return 0;
}
int is_full(SortedList* a) {
    if (a->size == MAX_SIZE) return 1;
    else return 0;
}
int pos[10] = { 0 };
// 우선순위가 n인 원소가 몇개 입력됐는지 저장할 배열
// 우선순위가 n보다 작은 값이 들어오면 그 이전까지 들어온 모든값 다음으로 위치한다.
void slist_insert(SortedList* a, Element e) {
    int insert = 0; // 삽입되어야 하는위치
    if (is_empty(a) == 1) {
        pos[e.p - 1] += 1;
        a->arr[a->size] = e;
        a->size++;
    } // List가 비어있다면 삽입한다.
    else if (a->arr[a->size - 1].p > e.p) {
        // 입력받은 우선순위가 맨 마지막 원소의 우선순위보다 작다면 중간으로 삽입해야함
        insert = 0;
        for (int i = 0; i <= e.p - 1; i++) {
            insert += pos[i]; // 우선순위 p 이하인 Element들의 개수 -> 삽입될 index
        } // 같은 우선순위 원소들의 제일 오른쪽 위치에 입력된다.
        // 우선순위가 10까지 있다고 코드를 작성 했지만 입력받는 수가 n개일때 n개의 우선순위가 생길 수 있으므로 최대 n번의 작업
        pos[e.p - 1] += 1; // 우선순위가 p인 Element 1개 증가시킨다.
        a->size++; // 입력을 받을 것 이므로 크기를 1 키운다.
        for (int i = a->size; i >= insert; i--) {
            a->arr[i].p = a->arr[i - 1].p;
            a->arr[i].id = a->arr[i - 1].id;
        } // 입력을 넣을 곳에 있는 원소들부터 뒤로 한칸씩 민다. n개의 원소를 입력받았을 때, 최대 n번의 작업
        a->arr[insert] = e; // 원소를 입력한다.
    }
    else {
        pos[e.p - 1] += 1;
        a->arr[a->size] = e;
        a->size++;
    }
    for (int i = 0; i < a->size; i++) {
        printElement(a->arr[i]);
    }
    printf("\n"); //정렬이 잘 되는지 확인하기위해 출력하는 코드
}
Element slist_deletemax(SortedList* a) {
    if (is_empty(a) == 1) {
        printf("List is Empty\n");
        return a->arr[a->size];
    }
    else {
        a->size--; // 마지막 원소 가르킴
        return a->arr[a->size]; // 마지막 원소 출력
    }
}
// 우선순위를 기준으로 정렬이 되어있기 때문에 맨 마지막 원소의 값을 꺼내면 된다.
// 따라서 시간복잡도는 O(1)이다.
void printElement(Element e) {
    printf("{%d, %d} ", e.p, e.id);
}