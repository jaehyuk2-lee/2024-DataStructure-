#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bst.h"

int main() {
    char c, grade;
    int id;

    printf("*************** Command **************\n");
    printf("I: Insert data, S: Search data\n");
    printf("P: Print inorder, Q: Quit \n");
    printf("**************************************\n");

    while(1) {
        printf("\nCommand> ");
        c = getchar();
        c = toupper(c);

        switch (c) {
        case 'I':
            printf("\n id and grade: ");
            scanf("%d %c", &id, &grade);
            bst_insert(id, grade);
            break;

        case 'S':
            printf("\n id: ");
            scanf("%d", &id);
            grade = bst_search(id);
            if(grade!='\0')printf("Grade of %d: %c \n", id, grade);
            else printf("No such id\n");
            break;

        case 'P':
            printf("\n");
            bst_show_inorder(root);
            break;

        case 'Q':
            printf("\n");
            exit(1);
            break;
        
        default:
            break;
        } while(getchar() != '\n');
    }
}

void bst_insert(int key, char data) {
    TreeNode* insert = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* tmp;
    insert->key = key;
    insert->data = data;
    insert->left = NULL;
    insert->right = NULL;

    if (root == NULL) {
        root = insert;
    }
    else {
        tmp = root;
        while(1) {
            if(tmp->key < insert->key) {
                if(tmp->right == NULL) {
                    tmp->right = insert;
                    break;
                }
                else tmp = tmp->right;
            }
            else {
                if(tmp->left == NULL) {
                    tmp->left = insert;
                    break;
                }
                else tmp = tmp->left;
            }
        }
    }
    
}

char bst_search(int key) {
    TreeNode* tmp = root;
    while(1) {
        if(tmp == NULL) return '\0';
        if(tmp->key == key) {
            return tmp->data;
        }
        else if(tmp->key > key) {
            tmp = tmp->left;
        }
        else if(tmp->key < key) {
            tmp = tmp->right;
        }
    }
}

void bst_show_inorder(TreeNode* root) {
    if(root != NULL) {
        bst_show_inorder(root->left);
        printf("%d %c\n", root->key, root->data);
        bst_show_inorder(root->right);
    }
}