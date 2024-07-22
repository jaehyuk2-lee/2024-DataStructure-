#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode* build_tree() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* p1 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* p2 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* p3 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* p4 = (TreeNode*)malloc(sizeof(TreeNode));

    root->data = 'A';
    root->left = p1;
    root->right = p2;

    p1->data = 'B';
    p1->left = p3;
    p1->right = p4;

    p2->data = 'C';
    p2->left = NULL;
    p2->right = NULL;

    p3->data = 'D';
    p3->left = NULL;
    p3->right = NULL;

    p4->data = 'E';
    p4->left = NULL;
    p4->right = NULL;

    return root;
}

void show_inorder(TreeNode* root) {
    if (root != NULL) {
        show_inorder(root->left);
        printf("%c ", root->data);
        show_inorder(root->right);
    }
} // Ʈ���� �ۼ��Ǿ����� ������ȸ�� Ȯ��

TreeNode stack[5]; // TreeNode�� �����ϴ� stack, TreeNode�� 5���̹Ƿ� �ִ� 5�������� ����
int top = -1;// stack�� �� �� ���� index

void push(TreeNode t) {
    stack[++top] = t;
} // ��尡 �߰� �Ǹ� ���� ���� index�� �ø��� ���� �߰�

void pop() {
    top--;
}
// ���� ��带 �ٽ� ������� �ʱ� ������ void�� �ۼ�
// ���� ���� index�� 1�� �ٿ� stack ���ο� ���� ����������, �������� ���� �Ұ���
// push�ϸ� ��尡 �������

void print_paths(TreeNode* root) {
    if (root == NULL) return;
    push(*root); // ���� ��带 stack�� ����
    if (root->left == NULL && root->right == NULL) {
        for (int i = 0; i <= top; i++) {
            printf("%c ", stack[i].data); // stack�� ����Ǿ��ִ� ��� ���� ����Ѵ�
        }
        printf("\n");
        pop();
        // ����, ������ ��尡 ���ٸ� �ܸ� ���
        // ������� stack�� ����� Ʈ������ data�� ����ϰ� ���������� ������ ���� �����Ѵ�.
    }
    else {
        print_paths(root->left);
        print_paths(root->right);
        pop();
        // Ʈ���� ���� �������� ��� ����ߴٸ�, stack���� ����
        // �ܸ���常 ����ϸ� �Ǳ� ������, �ܸ��� ��� ����ߴٸ�, �߰� �κг�带 ����
    }
}

int main() {
    TreeNode* root = build_tree();
    show_inorder(root);
    printf("\n");

    print_paths(root);
}