#pragma once
#define boolean unsigned char
#define true 1
#define false 0

typedef char Element;

typedef struct QueueNode {
    Element item;
    struct QueueNode* link;
} QueueNode;
QueueNode *front, *rear;

void addq(Element e);
Element deleteq();
void queue_show();
boolean is_queue_empty();