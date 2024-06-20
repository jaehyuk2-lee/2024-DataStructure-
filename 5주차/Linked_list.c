#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Linked_list.h"

int main() {
    char c, e;
    ListNode *head, *p;
    head = (ListNode*)malloc(sizeof(ListNode));
    head->data = '\0';
    head->link = NULL;

    printf("***************Command***************\n");
    printf("+<c> : Insert c, -<c> : Delete c,\n");
    printf("?<c> : Search c, S : show, Q : Quit\n");
    printf("*************************************\n");
    
    while(1) {
        printf("Command>");
        c = getchar();
        c = toupper(c);

        switch (c) {
        case '+':
            e = getchar();
            list_insert(head, e);
            break;

        case '-':
            e = getchar();
            list_delete(head, e);
            break;

        case '?':
            e = getchar();
            p = list_search(head, e);

            if(p) {
                printf("\n%c is in the list. \n", e);
                printf("Node address = %p, data = %c. link = %p \n", p, p->data, p->link);
            }
            else printf("\n%c is not in the list \n", e);
            break;

        case 'S':
            list_show(head);
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


void list_insert(ListNode *head, Element e) {
    ListNode* insert;
    insert = (ListNode*)malloc(sizeof(ListNode));
    insert->data = e;
    insert->link = head->link;
    head->link = insert;
}

void list_delete(ListNode *head, Element e) {
    if (list_empty(head)) {
        printf("List is empty\n");
        return;
    }
    ListNode* pre;
    ListNode* tmp;
    pre = head->link;

    if(pre->data == e) {
        head->link = pre->link;
        free(pre);
    }
    else {
        tmp = pre->link;

        while(1) {
            if(tmp->data == e) {
                pre->link = tmp->link;
                free(tmp);
                break;
            }
            else if(tmp->link == NULL) {
                printf("\n%c is not in the list\n", e);
                break;
            }
            else {
                pre = tmp;
                tmp = tmp->link;
            }
        }
    }
}

ListNode* list_search(ListNode *head, Element e) {
    ListNode* tmp;
    tmp = head->link;
    while(1) {
        if(tmp->data == e) {
            return tmp;
        }
        else if(tmp->link == NULL) {
            return NULL;
        }
        else tmp = tmp->link;
    }
}

bool list_empty(ListNode *head) {
    if(head->link == NULL) return true;
    else return false;
}

void list_show(ListNode *head) {
    if (list_empty(head)) {
        printf("List is empty\n");
    }
    else {
        ListNode* tmp;
        tmp = head->link;
        while(tmp) {
            printf("%c ", tmp->data);
            tmp = tmp->link;
        }
        printf("\n");
    }
}