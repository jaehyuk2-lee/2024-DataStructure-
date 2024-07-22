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
} // 트리가 작성되었는지 중위순회로 확인

TreeNode stack[5]; // TreeNode를 저장하는 stack, TreeNode는 5개이므로 최대 5개까지만 저장
int top = -1;// stack의 맨 위 값의 index

void push(TreeNode t) {
    stack[++top] = t;
} // 노드가 추가 되면 가장 높은 index를 늘리고 값을 추가

void pop() {
    top--;
}
// 꺼낸 노드를 다시 사용하지 않기 때문에 void로 작성
// 가장 높은 index를 1개 줄여 stack 내부에 값은 존재하지만, 논리적으로 접근 불가능
// push하면 노드가 덮어씌워짐

void print_paths(TreeNode* root) {
    if (root == NULL) return;
    push(*root); // 현재 노드를 stack에 저장
    if (root->left == NULL && root->right == NULL) {
        for (int i = 0; i <= top; i++) {
            printf("%c ", stack[i].data); // stack에 저장되어있는 모든 값을 출력한다
        }
        printf("\n");
        pop();
        // 왼쪽, 오른쪽 노드가 없다면 단말 노드
        // 현재까지 stack에 저장된 트리들의 data를 출력하고 마지막으로 저장한 노드는 제거한다.
    }
    else {
        print_paths(root->left);
        print_paths(root->right);
        pop();
        // 트리의 왼쪽 오른쪽을 모두 출력했다면, stack에서 제거
        // 단말노드만 출력하면 되기 때문에, 단말을 모두 출력했다면, 중간 부분노드를 제거
    }
}

int main() {
    TreeNode* root = build_tree();
    show_inorder(root);
    printf("\n");

    print_paths(root);
}