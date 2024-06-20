#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "arraylist.h"

int main() {
    char c;
    printf("******************* Command ********************\n");
    printf("+<c>: Insert c, -<c>: Delete c \n");
    printf("E: ListEmpty, F: ListFull, S: ListShow, Q: Quit \n");
    printf("************************************************\n");

    while(1) {
        printf("\nCommand> ");
        c = getchar();
        c = toupper(c);

        switch(c) {
            case '+':
                c = getchar();
                list_insert(c);
                break;
            case '-':
                c = getchar();
                list_delete(c);
                break;
            case 'E':
                if(list_empty()) printf("TRUE\n");
                else printf("FALSE\n");
                break;
            case 'F' :
                if(list_full()) printf("TRUE\n");
                else printf("FALSE\n");
                break;
            case 'S':
                list_show();
                break;
            case 'Q':
                printf("\n");
                exit(1);
            default:
                break;
        } while(getchar() != '\n');
    }
    return 0;
}

void list_insert(Element e) {
    if (list_full()) {
        printf("List is full\n");
    }
    else {
        List[size] = e;
        size++;
    }
}
void list_delete(Element e) {
    int i = 0;
    if (list_empty()) {
        printf("List is empty\n");
    }
    else {
        while(true) {
            if (i == size){
                printf("Data does not exist\n");
                break;
            }
            else if(List[i] == e) {
                for(int j = i; j < size; j++) {
                    List[j] = List[j+1];
                }
                size--;
                break;
            }
            i++;
        }
    }
}
boolean list_empty() {
    if (size == 0) return true;
    else return false;
}

boolean list_full() {
    if (size == MaxSize) return true;
    else return false;
}

void list_show() {
    if (list_empty()) {
        printf("List is empty");
    }
    else {
        for(int i = 0; i < size; i++) {
        printf("%c ", List[i]);
        }
    }
    
    printf("\n");
}