#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arraystack.h"

int main() {
    char c, e;

    while (1) {
        printf("Command>");
        c = getchar();
        c = toupper(c);
        switch (c) {
        case '+':
            e = getchar();
            push(e);
            break;
        case '-':
            e = pop();
            if(e != false) printf("%c \n", e);
            break;
        case 'S':
            stack_show();
            break;
        case 'Q':
            printf("\n");
            exit(1);
        default:
            break;
        }
        while(getchar()!='\n');
    }

    return 0;
}

void push(Element e) {
    stack[++top] = e;
}
Element pop() {
    if(top == -1) {
        printf("stack is empty\n");
        return false;
    }
    else return stack[top--];
}
void stack_show() {
    if(top == -1) {
        printf("stack is empty\n");
    }
    for(int i = 0; i <= top; i++) {
        printf(" %c ", stack[i]);
    }
    printf("\n");
}