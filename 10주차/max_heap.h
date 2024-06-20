#define MAX_SIZE 100
#define boolean unsigned char
#define true 1
#define false 0

typedef struct Element {
	int key;
	char data;
} Element;

Element heap[MAX_SIZE];
int heap_size = 0;
 
void insert_max_heap(Element item);
Element delete_max_heap();
void max_heap_show();
boolean is_heap_empty();
