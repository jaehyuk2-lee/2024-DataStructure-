#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "adj_list2.h"

int main() {
    char c;
    int v;
    front = rear = NULL;

    build_simple_graph();

    printf("******** Command ********\n");
    printf("D: DFS, B: BFS, Q: Quit \n");
    printf("*************************\n");

    while(true) {
        printf("\nCommand> ");
        c = getchar();
        c = toupper(c);

        switch (c) {
        case 'D':
            printf("\nStart vertex: ");
            scanf("%d", &v);
            for(int i = 0; i<MAX_VERTICES; i++) visited[i] = false;
            dfs(v);
            printf("\n");
            break;
        case 'B':
            printf("\nStart vertex: ");
            scanf("%d", &v);
            for(int i = 0; i<MAX_VERTICES; i++) visited[i] = false;
            bfs(v);
            printf("\n");
            break;

        case 'Q':
            printf("\n");
            exit(true);
        default:
            break;
        } while(getchar() != '\n');
    }
}

void build_simple_graph() {
    insert_edge(1, 4);
    insert_edge(1, 3);
    insert_edge(1, 2);

    insert_edge(2, 5);
    insert_edge(2, 1);

    insert_edge(3, 5);
    insert_edge(3, 1);

    insert_edge(4, 5);
    insert_edge(4, 1);

    insert_edge(5, 4);
    insert_edge(5, 3);
    insert_edge(5, 2);

    printf("Graph is built. V = 5, E = 6.\n");
}

void insert_edge(int v, int w) {
    adj[v][w] = 1;
    adj[w][v] = 1;
}

void dfs(int v) {
    printf("%d ", v);
    visited[v] = true;

    for(int i = 1; i < MAX_VERTICES; i++) {
        if(adj[v][i] && !visited[i]) {
            dfs(i);
        }
    }
}

void bfs(int v) {
    printf("%d ", v);
    visited[v] = true;

    addq(v);
    while(!is_queue_empty()) {
        v = deleteq();
        for(int i = 1; i < MAX_VERTICES; i++) {
            if(adj[v][i] && !visited[i]){
                printf("%d ", i);
                visited[i] = true;

                addq(i);
            }
        }
    }
}

void addq(Element e) {
    QueueNode* p = (QueueNode*)malloc(sizeof(QueueNode));
    p->item = e;
    p->link = NULL;

    if(is_queue_empty()) {
        front = rear = p;
    }
    else {
        rear->link = p;
        rear = p;
    }
}

Element deleteq() {
    Element ret = front->item;
    QueueNode* tmp  = front;
    front = front->link;
    free(tmp);

    return ret;
}

boolean is_queue_empty() {
    if(front == NULL) {
        return true;
    }
    else return false;
}