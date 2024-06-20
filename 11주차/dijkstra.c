#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main() {
    found[0] = true;

    for(int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = cost[0][i];
    }
    dijkstra();
}

void show_status() {
    printf("\n");
    printf("vertex:\t\t0\t1\t2\t3\t4\t5\n");
    printf("distance:");
    for(int i = 0; i < MAX_VERTICES; i++) {
        printf("\t%d", distance[i]);
    }
    printf("\n");
    printf("found:\t");
    for(int i = 0; i < MAX_VERTICES; i++) {
        printf("\t%d", found[i]);
    }
    printf("\n");
}

int min_distance() {
    int min_index;
    for(int i = 0; i < MAX_VERTICES; i++) {
        if(!found[i]) {
            min_index = i;
            break;
        }
    }

    for(int i = 0; i < MAX_VERTICES; i++) {
        if((distance[min_index] > distance[i]) && !found[i]) {
            min_index = i;
        }
    }

    return min_index;
}

void dijkstra() {
    show_status();
    for(int i = 0; i < MAX_VERTICES; i++) {
        int u = min_distance();
        found[u] = true;

        for(int w = 0; w < MAX_VERTICES; w++) {
            if(!found[w]) {
                distance[w] = (distance[w] > distance[u]+cost[u][w]) ? distance[u]+cost[u][w] : distance[w];
            }
        }
        // u를 찾았을 때 u에 인접한 모든 w의 거리 최신화
        show_status();
    }
}