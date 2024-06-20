#define MAX_SIZE 6
#include <stdio.h>

typedef struct
{
    int r;
    int c;
} Element;

typedef struct
{
    Element data[MAX_SIZE];
    int top;
} Stack;

char maze[MAX_SIZE][MAX_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'0', '0', '0', '0', '0', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '1', '1', '0', '0', 'x'},
    {'1', '1', '1', '0', '1', '1'},
    {'1', '1', '1', '1', '1', '1'}
};

void init_stack(Stack* s);
int is_empty(Stack* s);
void push(Stack* s, Element item);
Element pop(Stack* s);

void push_loc(Stack* s, int r, int c);
void maze_print(char maze[][MAX_SIZE]);
void stack_print(Stack* s);