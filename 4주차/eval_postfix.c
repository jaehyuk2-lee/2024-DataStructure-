#include <stdio.h>
#include <string.h>
#include "eval_postfix.h"

int main() {
    char exp[100];
    int result;

    while(1) {
        err_check = false;
        printf("\nInput postfix expression: ");
        scanf("%s", exp);

        result = eval_postfix(exp);
        if(err_check == false){
            printf("Result = %d\n", result);
        }
    }
    return 0;
}
void push(int e) {
    stack[++top] = e;
}
int pop() {
    return stack[top--];
}

int eval_postfix(char* exp) {
    int size = strlen(exp);
    int num1, num2;
    for(int i = 0; i < size; i++) {
        if(is_number(exp[i]) == true) {
            push(exp[i]-'0');
        }
        else if(is_op(exp[i]) == true) {
            switch (exp[i]) {
            case '+':
                num2 = pop();
                num1 = pop();
                push(num1+num2);
                break;
            case '-':
                num2 = pop();
                num1 = pop();
                push(num1-num2);
                break;
            case '*':
                num2 = pop();
                num1 = pop();
                push(num1*num2);
                break;
            case '/':
                num2 = pop();
                if(num2 == 0) {
                    printf("divide by 0 error \n");
                    err_check = true;
                    break;
                }
                num1 = pop();
                push(num1/num2);
                break;
            
            default:
                break;
            }
        }
    }
    return pop();
}

boolean is_number(char c) {
    if(('0')<=c&&(c<='9')) return true;
    else return false;
}

boolean is_op(char c) {
    if(is_number(c) == false) return true;
    else return false;
}