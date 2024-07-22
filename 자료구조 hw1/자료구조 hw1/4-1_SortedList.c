// slist_deletemax�� �ּ�ȭ�ϱ����� ����
// �Է¹޴� ������ p�� �������� ������������ �Է��� �޴´ٸ� p�� ū�� �켱, �ֱٿ� �Է¹��� ���� �켱���� �����
// slist_deletemax�� TimeComplexity�� O(1)�� ����� �� �ִ�.
#include <stdio.h>
#define MAX_SIZE 100 // SortedList�� �ִ� ���� ���� ����
typedef struct
{
    int p;
    int id; // �켱����(p)�� ��(id)�� �����ϴ� ����ü
} Element;
typedef struct {
    Element arr[MAX_SIZE]; // Element �ڷ����� �����ϴ� �迭
    int size;
} SortedList;
void init_slist(SortedList*);
int is_empty(SortedList*);
int is_full(SortedList*);
void slist_insert(SortedList*, Element);
Element slist_deletemax(SortedList*);
void printElement(Element); // Element�� p�� id�� ����ϱ� ���� �Լ�
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
    a->size = 0; // ���� ����� �� 0���� ����
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
// �켱������ n�� ���Ұ� � �Էµƴ��� ������ �迭
// �켱������ n���� ���� ���� ������ �� �������� ���� ��簪 �������� ��ġ�Ѵ�.
void slist_insert(SortedList* a, Element e) {
    int insert = 0; // ���ԵǾ�� �ϴ���ġ
    if (is_empty(a) == 1) {
        pos[e.p - 1] += 1;
        a->arr[a->size] = e;
        a->size++;
    } // List�� ����ִٸ� �����Ѵ�.
    else if (a->arr[a->size - 1].p > e.p) {
        // �Է¹��� �켱������ �� ������ ������ �켱�������� �۴ٸ� �߰����� �����ؾ���
        insert = 0;
        for (int i = 0; i <= e.p - 1; i++) {
            insert += pos[i]; // �켱���� p ������ Element���� ���� -> ���Ե� index
        } // ���� �켱���� ���ҵ��� ���� ������ ��ġ�� �Էµȴ�.
        // �켱������ 10���� �ִٰ� �ڵ带 �ۼ� ������ �Է¹޴� ���� n���϶� n���� �켱������ ���� �� �����Ƿ� �ִ� n���� �۾�
        pos[e.p - 1] += 1; // �켱������ p�� Element 1�� ������Ų��.
        a->size++; // �Է��� ���� �� �̹Ƿ� ũ�⸦ 1 Ű���.
        for (int i = a->size; i >= insert; i--) {
            a->arr[i].p = a->arr[i - 1].p;
            a->arr[i].id = a->arr[i - 1].id;
        } // �Է��� ���� ���� �ִ� ���ҵ���� �ڷ� ��ĭ�� �δ�. n���� ���Ҹ� �Է¹޾��� ��, �ִ� n���� �۾�
        a->arr[insert] = e; // ���Ҹ� �Է��Ѵ�.
    }
    else {
        pos[e.p - 1] += 1;
        a->arr[a->size] = e;
        a->size++;
    }
    for (int i = 0; i < a->size; i++) {
        printElement(a->arr[i]);
    }
    printf("\n"); //������ �� �Ǵ��� Ȯ���ϱ����� ����ϴ� �ڵ�
}
Element slist_deletemax(SortedList* a) {
    if (is_empty(a) == 1) {
        printf("List is Empty\n");
        return a->arr[a->size];
    }
    else {
        a->size--; // ������ ���� ����Ŵ
        return a->arr[a->size]; // ������ ���� ���
    }
}
// �켱������ �������� ������ �Ǿ��ֱ� ������ �� ������ ������ ���� ������ �ȴ�.
// ���� �ð����⵵�� O(1)�̴�.
void printElement(Element e) {
    printf("{%d, %d} ", e.p, e.id);
}