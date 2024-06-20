#define MAX_VERTICES 100
#define boolean unsigned char
#define true 1
#define false 0

int adj[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];

void build_simple_graph();
void insert_edge(int, int);
void dfs(int);
void bfs(int);

typedef int Element;

typedef struct QueueNode {
    Element item;
    struct QueueNode* link;
}QueueNode;

QueueNode* front;
QueueNode* rear;

void addq(Element e);
Element deleteq();
boolean is_queue_empty();