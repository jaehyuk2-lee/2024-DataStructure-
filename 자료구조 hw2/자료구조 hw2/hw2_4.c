#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode* link;
} ListNode;

ListNode* makeNode(int);
// Linked list ���� �Լ�, ���� N�� 0�̸�, List�� �������� �����Ƿ� NULL�� ��ȯ�Ѵ�.
// 0�� �ƴϸ� 1���� ���� ������ head�� �����ϰ�, N-1���� �����ϸ� (1���� ���� �����߱� ����), data���� �����ϰ�, link�� head�� ������.
// ���� �ִ� ����Ʈ�� �� �������� ���Ӱ� ������ Node�� ����Ű�� �Ѵ�.
// �ݺ����� ����Ǹ� �� ������ Node�� head�� ����Ű�� Circular Linked List�� ���� �� �ִ�.

void show_list(ListNode* head);
// ���ȿ����� head�� �� ������ Node�� �ξ� head->link���� ����ϸ�, head�� �Ǳ������� (�������� �Ǳ�������) ����� ������
// head�� �� ������ �ΰ� �����߱� ������, head�� data�� ���� ����� �����ϰ� ���� Node�� head�� �ƴҶ����� ����Ѵ�.

void find_seq(ListNode*, int, int);
// head�� K�� Node�� link�� ���� �� K��°�� data�� ����ϰ� free�� �Ѵ�.
// head�� link�� head��� ������ ���� ����̱� ������ data ���, free�� �����Ѵ�.

int main() {
    int N, K;
    printf("N, K: ");
    scanf_s("%d %d", &N, &K);

    ListNode* head = NULL;

    head = makeNode(N);
    show_list(head);

    find_seq(head, N, K);
}

ListNode* makeNode(int N) {
    if (N == 0) {
        return NULL;
    }
    else {
        ListNode* head = NULL;
        ListNode* current = (ListNode*)malloc(sizeof(ListNode));
        head = current;
        current->data = 1;
        current->link = head;
        for (int i = 1; i < N; i++) {
            ListNode* next = (ListNode*)malloc(sizeof(ListNode));
            next->data = i + 1;
            next->link = head;
            current->link = next;
            current = current->link;
        }
        return head;
    }
}

void show_list(ListNode* head) {
    ListNode* p;
    p = head->link;
    printf("data : [%d], adress : [%p], next adress : [%p]\n", head->data, head, head->link);
    while (p != head) {
        printf("data : [%d], adress : [%p], next adress : [%p]\n", p->data, p, p->link);
        p = p->link;
    }
}

void find_seq(ListNode* head, int N, int K) {
    ListNode* p = head;
    ListNode* left = p;
    
    while (head->link != head) {
        p = head;
        for (int i = 0; i < K-1; i++) {
            left = p;
            p = p->link;
        }
        printf("%d ", p->data);
        left->link = p->link;
        head = left->link;
        free(p);
        
    } 
}