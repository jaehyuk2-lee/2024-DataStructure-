# define MAX_VERTICES 22470

typedef struct gNode {
    int vertex; // vertex의 id
    int distance; // 특정 vertex로 부터 거리, get_close_vertiecies를 위해 포함
    struct gNode* link; // 연결된 vertex 주소
}gNode;

gNode* adjList[MAX_VERTICES]; // 인접리스트 
int visited[MAX_VERTICES] = { 0 }; // 방문여부확인

void build_graph(char* fname); // 파일로 부터 graph 만들기
void show_graph(); // 10개의 그래프 인접 리스트 출력
void get_close_vertices(int v, int k); // vertex v로 부터 k 단계 안에 존재하는 vertex BFS로 탐색


int arrV[MAX_VERTICES]; // k 단계 안에 존재하는 vertex 저장 배열
void sort(); // arrV정렬 (선택정렬)
int top = -1; // arrV의 마지막 index

typedef struct QueueNode {
    int item;
    struct QueueNode* link;
} QueueNode;
QueueNode* front, * rear;

void addq(int e);
int deleteq();
void queue_show();
int is_queue_empty();

// queue vertex의 id를 포함