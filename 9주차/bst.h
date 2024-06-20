
typedef struct TreeNode {
    int key;
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode* root;
void bst_insert(int key, char data);
char bst_search(int key);
void bst_show_inorder(TreeNode* root);