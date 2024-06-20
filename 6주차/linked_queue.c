#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "linked_queue.h"

int main() {
    char c, e;
    front = rear = NULL;

    while (1) {
        printf("\nCommand> ");
        c = getchar();
        c = toupper(c);
        switch (c) {
        case '+':
            e = getchar();
            addq(e);
            break;

        case '-':
            if (is_queue_empty()) {
                printf("\nQueue is empty!!!\n");
            }
            else {
                e = deleteq();
                printf("\n%c", e);
            }
            break;

        case 'S':
            if (is_queue_empty()) {
                printf("\nQueue is empty!!!\n");
            }
            else {
                queue_show();
            }
            break;

        case 'Q':
            printf("\n");
            exit(1);
            break;

        default:
            break;
        }
        while (getchar() != '\n');
    }

    return 0;
}

void addq(Element e) {
    QueueNode* p;
    p = (QueueNode*)malloc(sizeof(QueueNode));
    p->item = e;
    p->link = NULL;
    if (is_queue_empty()) {
        front = rear = p;
    }
    else {
        rear->link = p;
        rear = p;
    }
}

Element deleteq() {
    Element ret;
    QueueNode* tmp;

    ret = front->item;

    tmp = front;
    front = front->link;
    free(tmp);

    return ret;
}

void queue_show() {
    QueueNode* p;
    p = front;
    while (p != NULL) {
        printf(" %c ", p->item);
        p = p->link;
    }
}
boolean is_queue_empty() {
    if (front == NULL) return true;
    else return false;
}