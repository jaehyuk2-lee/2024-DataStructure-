#define MAX_VERTICES 6
#define boolean unsigned char
#define true 1
#define false 0
#define INT_MAX 999

int cost[MAX_VERTICES][MAX_VERTICES] = 
{
    {0, 50, 10, INT_MAX, 65, INT_MAX},
    {INT_MAX, 0, 15, INT_MAX, 10, INT_MAX},
    {20, INT_MAX, 0, 15, INT_MAX, INT_MAX},
    {INT_MAX, 20, INT_MAX, 0, 35, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, 30, 0, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, 3, INT_MAX, 0}
};

int distance[MAX_VERTICES];
boolean found[MAX_VERTICES];

void show_status();
int min_distance();
void dijkstra();