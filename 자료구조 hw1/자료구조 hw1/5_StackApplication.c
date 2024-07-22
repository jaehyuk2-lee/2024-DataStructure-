#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>// ���ڿ� ���� �Լ� ����� ���� ����
#include <ctype.h>
#define MAX_SIZE 101 // �ִ�� Ȯ���� �� �ִ� ���ڿ��� ũ�� 100���� ����
typedef struct {
    char data[MAX_SIZE];
    int top;
} stack;
void push(stack*, char);
char pop(stack*);
void is_palindrome(char*);
int main() {
    char str[MAX_SIZE];
    printf("�ִ���� 100 ���ڿ� �Է�\n");
    scanf("%[^\n]s", str);
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        str[i] = tolower(str[i]);
    } // �Է¹��� ���ڿ��� �ҹ��ڷ� ����;
    for (int i = 0; i < length; i++) {
        if (str[i] < 97 || str[i]>122) {
            for (int j = i; j < length; j++) {
                str[j] = str[j + 1];
            }
            str[length] = '\0';
            length -= 1;
            i--;
        }
    }
    printf("%s\n", str); // �ҹ��ڷ� ������ ���ڿ� ���
    is_palindrome(str);
}
void push(stack* s, char c) {
    s->data[++s->top] = c;
}
char pop(stack* s) {
    return s->data[s->top--];
}
void is_palindrome(char* str) {
    stack compare;
    int size = strlen(str);
    strcpy(compare.data, str);
    compare.top = size - 1;
    int is_p = 1;
    for (int i = 0; i < size; i++) {
        if (pop(&compare) != str[i]) {
            is_p = 0;
        }
    }
    for (int i = size - 1; i >= 0; i--) {
        printf("%c", str[i]);
    }
    printf("\n");
    if (is_p == 1) {
        printf("yes\n");
    }
    else printf("no\n");
}