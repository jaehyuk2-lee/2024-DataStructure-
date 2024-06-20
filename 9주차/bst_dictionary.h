typedef struct TreeNode {
    char w1[100];
    char w2[100];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;
TreeNode* root;

int build_dictionary(char *fname);
void bst_insert(char* w1, char* w2);
char* bst_search(char* w1);
void bst_show_inorder(TreeNode* root);