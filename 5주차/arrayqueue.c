#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "arrayqueue.h"

int main() {
    char c, e;
    printf("***************Command***************\n");
    printf("+<c> : Add Q c, - : DeleteQ,\n");
    printf("S : show, Q : Quit\n");
    printf("*************************************\n");

    while(1) {
        printf("Command>");
        c = getchar();
        c = toupper(c);
        printf("\n");

        switch (c) {
        case '+':
            e = getchar();
            addq(e);
            break;

        case '-':
            e = deleteq();
            if(e != '\0') printf("%c\n", e);
            break;

        case 'S':
            queue_show();
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
}

void addq(Element e) {
    if(rear == front) {
        is_empty = false;
    }

    if((rear+1) % MAX_SIZE == front) {
        printf("queue is full \n");
    }

    else {
        queue[rear++] = e;
    }
}

Element deleteq() {
    if(is_empty == true) {
        printf("queue is empty\n");
        return '\0';
    }
    else {
        if(rear-1 == front) {
            is_empty = true;
        }
        return queue[front++];
    }
}
void queue_show() {
    for(int i = front; i != rear; i++) {
        if(i > MAX_SIZE) {
            i %= MAX_SIZE;
        }
        printf("%c ", queue[i]);
    }
    printf("\n");
}