#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode* link;
} ListNode;

ListNode* makeNode(int);
// Linked list 생성 함수, 만약 N이 0이면, List를 생성하지 않으므로 NULL을 반환한다.
// 0이 아니면 1개를 먼저 생성해 head로 생성하고, N-1개를 생성하며 (1개를 먼저 생성했기 때문), data값을 설정하고, link를 head로 보낸다.
// 원래 있던 리스트의 맨 마지막을 새롭게 생성된 Node를 가리키게 한다.
// 반복문이 종료되면 맨 마지막 Node가 head를 가리키는 Circular Linked List를 얻을 수 있다.

void show_list(ListNode* head);
// 교안에서는 head를 맨 마지막 Node에 두어 head->link부터 출력하며, head가 되기전까지 (마지막이 되기전까지) 출력을 하지만
// head를 맨 앞으로 두고 생성했기 때문에, head의 data를 먼저 출력해 시작하고 현재 Node가 head가 아닐때까지 출력한다.

void find_seq(ListNode*, int, int);
// head를 K번 Node의 link로 변경 후 K번째에 data를 출력하고 free를 한다.
// head의 link가 head경우 마지막 남은 노드이기 때문에 data 출력, free후 종료한다.

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