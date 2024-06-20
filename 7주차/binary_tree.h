#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define boolean unsigned char
#define true 1
#define false 0
#define max(x,y) x>y?x:y

typedef int Element;

typedef struct TreeNode {
    Element data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

TreeNode* build_simple_tree();
int bt_count(TreeNode* root);
int bt_sum(TreeNode* root);
int bt_height(TreeNode* root);
void bt_show_preorder(TreeNode* root);
void bt_free(TreeNode* root);

TreeNode* tree_queue[9];
int first = 0;
int last = 0;
void addq(TreeNode* root) {
    if(root) {
        if((last+1)%9 == first) {
            printf("Queue is full\n");
        }
        else {
            tree_queue[last] = root;
            last = (last+1)%9;
        }
    }
    
}
TreeNode* deleteq() {
    if(first == last) {
        return NULL;
    }
    else {
        TreeNode* ret = tree_queue[first];
        first = (first+1)%9;
        return ret;
    }
}

void bt_level_order(TreeNode* root);