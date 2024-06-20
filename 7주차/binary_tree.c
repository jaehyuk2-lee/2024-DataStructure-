#include "binary_tree.h"

int main() {
    char c;
    int n;
    TreeNode* t;
    t = build_simple_tree();

    printf("*************** Command *************\n");
    printf("C: Count tree, A: Sum tree data\n");
    printf("H: Height of tree, S: Show preorder\n");
    printf("L: Level order, F: Free tree, Q: Quit \n");
    printf("*************************************\n");

    while(1) {
        printf("\nCommand> ");
        c = getchar();
        c = toupper(c);

        switch (c) {
        case 'C':
            n = bt_count(t);
            printf("\n Total number of node = %d\n", n);
            break;

        case 'A':
            n = bt_sum(t);
            printf("\n Total number of node = %d\n", n);
            break;

        case 'H':
            n = bt_height(t);
            printf("\n Total number of node = %d\n", n);
            break;

        case 'S':
            printf("\n");
            bt_show_preorder(t);
            printf("\n");
            break;

        case 'L':
            bt_level_order(t);
            break;

        case 'F':
            printf("\n");
            bt_free(t);
            break;

        case 'Q':
            printf("\n");
            exit(1);
        
        default:
            break;
        }
        while(getchar() != '\n');
    }
}


// TreeNode* build_simple_tree() {
//     TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
//     TreeNode* n2 = (TreeNode*)malloc(sizeof(TreeNode));
//     TreeNode* n3 = (TreeNode*)malloc(sizeof(TreeNode));
//     TreeNode* n4 = (TreeNode*)malloc(sizeof(TreeNode));
//     TreeNode* n5 = (TreeNode*)malloc(sizeof(TreeNode));
//     TreeNode* n6 = (TreeNode*)malloc(sizeof(TreeNode));
//     TreeNode* n7 = (TreeNode*)malloc(sizeof(TreeNode));
//     TreeNode* n8 = (TreeNode*)malloc(sizeof(TreeNode));
//     TreeNode* n9 = (TreeNode*)malloc(sizeof(TreeNode));

//     root->data = 10;
//     root->left = n2;
//     root->right = n3;

//     n2->data = 20;
//     n2->left = n4;
//     n2->right = n5;

//     n3->data = 30;
//     n3->left = n6;
//     n3->right = n7;

//     n4->data = 40;
//     n4->left = n8;
//     n4->right = n9;

//     n5->data = 50;
//     n5->left = NULL;
//     n5->right = NULL;

//     n6->data = 60;
//     n6->left = NULL;
//     n6->right = NULL;

//     n7->data = 70;
//     n7->left = NULL;
//     n7->right = NULL;

//     n8->data = 80;
//     n8->left = NULL;
//     n8->right = NULL;

//     n9->data = 90;
//     n9->left = NULL;
//     n9->right = NULL;

//     return root;
// }

TreeNode* build_simple_tree() {
    TreeNode* tree_array[9];

    for(int i = 0; i < 9; i++) {
        tree_array[i] = (TreeNode*)malloc(sizeof(TreeNode));
        tree_array[i]->data = (i+1)*10;
        tree_array[i]->left = NULL;
        tree_array[i]->right = NULL;
    }


    for(int i = 0; i < 4; i++) {
        tree_array[i]->left = tree_array[2*i+1];
        tree_array[i]->right = tree_array[2*i+2];
    }

    return tree_array[0];
}

int bt_count(TreeNode* root) {
    if(root == NULL) {
        return 0;
    }
    else return(1+bt_count(root->left)+bt_count(root->right));
}
int bt_sum(TreeNode* root) {
    if(root == NULL) {
        return 0;
    }
    else return(root->data+bt_sum(root->left)+bt_sum(root->right));
}
int bt_height(TreeNode* root) {
    if(root == NULL) {
        return 0;
    }
    else return(max(1+bt_height(root->left), 1+bt_height(root->right)));
}
void bt_show_preorder(TreeNode* root) {
    if(root) {
        printf("%d ", root->data);
        bt_show_preorder(root->left);
        bt_show_preorder(root->right);
    }
}
void bt_free(TreeNode* root) {
    if(root) {
        bt_free(root->left);
        bt_free(root->right);
        printf("free node with item %d\n", root->data);
        free(root);
    }
}
void bt_level_order(TreeNode* root) {
    printf("******* Level Order Traversal ******\n");
    while(root) {
        printf("%d\n", root->data);
        addq(root->left);
        addq(root->right);
        root = deleteq();
    }
}