#define Element char
#define bool unsigned char
#define true 1
#define false 0

typedef struct ListNode {
    Element data;
    struct ListNode *link;
} ListNode;

void list_insert(ListNode *head, Element e);
void list_delete(ListNode *head, Element e);
ListNode* list_search(ListNode *head, Element e);
bool list_empty(ListNode *head);
void list_show(ListNode *head);