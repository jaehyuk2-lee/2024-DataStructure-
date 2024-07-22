#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode* link;
} ListNode;

void remove_duplicate(ListNode* head);

ListNode* set_list(); // 문제에 주어진 배열을 만들고 그 head를 리턴하는 함수
void show_list(ListNode* head); // 연결된 ListNode들의 data, adress, next adress를 출력하는 함수

int main() {
    ListNode* head;
    head = set_list();
    show_list(head); // 생성한 문자열을 확인
    printf("\n");

    remove_duplicate(head); // data가 중복되는 노드를 삭제
    printf("\n");
    show_list(head); // 삭제후 문자열 확인
}

ListNode* set_list() {
    ListNode* n1 = (ListNode*)malloc(sizeof(ListNode));
    ListNode* n2 = (ListNode*)malloc(sizeof(ListNode));
    ListNode* n3 = (ListNode*)malloc(sizeof(ListNode));
    ListNode* n4 = (ListNode*)malloc(sizeof(ListNode));
    ListNode* n5 = (ListNode*)malloc(sizeof(ListNode));
    ListNode* n6 = (ListNode*)malloc(sizeof(ListNode));
    ListNode* n7 = (ListNode*)malloc(sizeof(ListNode));

    n1->data = 2;
    n1->link = n2;

    n2->data = 3;
    n2->link = n3;

    n3->data = 3;
    n3->link = n4;

    n4->data = 4;
    n4->link = n5;

    n5->data = 7;
    n5->link = n6;

    n6->data = 7;
    n6->link = n7;

    n7->data = 7;
    n7->link = NULL;

    return n1;
}

void remove_duplicate(ListNode* head) {
    ListNode* tmp;
    tmp = head->link;

    printf("Remove Duplicate\n");
    while (head->link) {
        if (head->data == tmp->data) {
            head->link = tmp->link;
            printf("free data : [%d], adress : [%p], next adress : [%p]\n", tmp->data, tmp, tmp->link);
            free(tmp);
            tmp = head->link;
        }
        else {
            head = head->link;
            tmp = head->link;
        }
    }

}

void show_list(ListNode* head) {
    while (head) {
        printf("data : [%d], adress : [%p], next adress : [%p]\n", head->data, head, head->link);
        head = head->link;
    }
}
