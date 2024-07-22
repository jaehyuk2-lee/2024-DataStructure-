# define MAX_VERTICES 22470

typedef struct gNode {
    int vertex; // vertex�� id
    int distance; // Ư�� vertex�� ���� �Ÿ�, get_close_vertiecies�� ���� ����
    struct gNode* link; // ����� vertex �ּ�
}gNode;

gNode* adjList[MAX_VERTICES]; // ��������Ʈ 
int visited[MAX_VERTICES] = { 0 }; // �湮����Ȯ��

void build_graph(char* fname); // ���Ϸ� ���� graph �����
void show_graph(); // 10���� �׷��� ���� ����Ʈ ���
void get_close_vertices(int v, int k); // vertex v�� ���� k �ܰ� �ȿ� �����ϴ� vertex BFS�� Ž��


int arrV[MAX_VERTICES]; // k �ܰ� �ȿ� �����ϴ� vertex ���� �迭
void sort(); // arrV���� (��������)
int top = -1; // arrV�� ������ index

typedef struct QueueNode {
    int item;
    struct QueueNode* link;
} QueueNode;
QueueNode* front, * rear;

void addq(int e);
int deleteq();
void queue_show();
int is_queue_empty();

// queue vertex�� id�� ����