#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "hw3_5.h"

int main() {
    build_graph("facebook.txt");
    //show_graph();
    get_close_vertices(1234, 3);
}

void build_graph(char* fname) {
    FILE* ifp;
    int v, w;
    if ((ifp = fopen(fname, "r")) == NULL) {
        printf("No such file!\n");
        exit(1);
    }

    for (int i = 0; i < MAX_VERTICES; i++) {
        adjList[i] = (gNode*)malloc(sizeof(gNode));
        adjList[i]->vertex = i;
        adjList[i]->distance = 0;
        adjList[i]->link = NULL;
    } // 더미 노드 생성

    while (fscanf(ifp, "%d, %d", &v, &w) == 2) {
        gNode* p = (gNode*)malloc(sizeof(gNode));
        p->vertex = w;
        p->link = NULL;

        gNode* tmp = adjList[v];
        while (tmp->link) { // 리스트의 마지막 까지 포인터 이동
            tmp = tmp->link;
        }
        tmp->link = p;
        // NULL인 부분에 p연결
    }
}

void show_graph() {
    gNode* p;
    for (int i = 0; i < 11; i++) {
        printf("adj_list[%d]: ", i);
        if (adjList[i] == NULL) {
            printf("NULL\n");
            continue;
        }
        p = adjList[i]->link;
        while (p) {
            printf("<%d> -> ", p->vertex);
            p = p->link;
        }
        printf("NULL\n");
    }
    // 10개의 인접리스트의 연결 vertex 출력
}

void get_close_vertices(int v, int k) {
    gNode* p = adjList[v];
    visited[v] = 1; // 시작 vertex 방문

    addq(p->vertex); // queue에 추가하면서 반복 시작
    while (!is_queue_empty()) {
        v = deleteq();
        for (p = adjList[v]->link; p; p = p->link) {
            if(visited[p->vertex] != 1) adjList[p->vertex]->distance = (adjList[v]->distance + 1);
            // 인접 리스트들의 노드들이 방문을 하지 않았다면, 현재 노드로부터 거리 +1
        }
        for (p = adjList[v]; p; p = p->link) {
            if (visited[p->vertex] != 1 && adjList[p->vertex]->distance <= k) {
                // p의 vertex가 아직 방문을 하지 않았고, k번 안에 있는 노드일 경우
                addq(p->vertex);
                arrV[++top] = p->vertex;
                // vertex 추가
                visited[p->vertex] = 1;
            }
        }
    }

    sort(); // 저장한 vertex 오름차순으로 정렬
    printf("%d\n", top + 1);
    for (int i = 0; i <= top; i++) {
        printf("%d ", arrV[i]);
    }
    // arrV출력
}

void sort() {
    for (int i = 0; i < top; i++) {
        int min_index = i;
        for (int j = i + 1; j <= top; j++) {
            if (arrV[min_index] > arrV[j]) {
                min_index = j;
            }
        }
        int tmp = arrV[min_index];
        arrV[min_index] = arrV[i];
        arrV[i] = tmp;
    }
}

void addq(int e) {
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

int deleteq() {
    int ret;
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
        printf(" %d ", p->item);
        p = p->link;
    }
    printf("\n");
}
int is_queue_empty() {
    if (front == NULL) return 1;
    else return 0;
}