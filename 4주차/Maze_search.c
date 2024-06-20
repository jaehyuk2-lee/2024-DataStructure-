#include "Maze_search.h"
#define _CRT_SECURE_NO_WARNINGS

int main(void) {
    int r, c;
    Stack s;
    Element here, entry = { 1,0 };
    here = entry;
    int dr[4] = { -1, 1, 0, 0 };
    int dc[4] = { 0, 0, -1, 1 };

    init_stack(&s);
    while (maze[here.r][here.c] != 'x') {
        r = here.r;
        c = here.c;
        maze[r][c] = '.';
        maze_print(maze);

        for (int i = 0; i < 4; i++) {
            push_loc(&s, r + dr[i], c + dc[i]);
        }
        stack_print(&s);
        printf("\n\n");
        if (is_empty(&s)) {
            printf("실패\n");
            return 0;
        }
        else here = pop(&s);
    }
    printf("성공\n");
    return 0;
}

void init_stack(Stack* s) {
    s->top = -1;
}
int is_empty(Stack* s) {
    if (s->top == -1) return 1;
    else return 0;
}
void push(Stack* s, Element item) {
    s->data[++s->top] = item;
}
Element pop(Stack* s) {
    return s->data[s->top--];
}

void push_loc(Stack* s, int r, int c) {
    if (maze[r][c] == '0' || maze[r][c] == 'x') {
        Element e;
        e.r = r; e.c = c;
        push(s, e);
    }
}
void maze_print(char maze[][MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}
void stack_print(Stack* s) {
    printf("Current Stack : ");
    for (int i = 0; i <= s->top; i++) {
        printf("(%d, %d) ", s->data[i].r, s->data[i].c);
    }
    printf("\n");
}