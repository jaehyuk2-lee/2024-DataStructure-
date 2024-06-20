#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "bst_dictionary.h"

int main() {
    char c;
    char fname[20];
	char w1[100]; 
    char *w2 = NULL;
	int	wcount;

	printf("************* Command ************\n");
	printf("R: Read data, S: Search data    \n");
	printf("P: Print inorder, Q: Quit         \n");
	printf("**********************************\n");

	while (1) {
		printf("\nCommand> ");
        c = getchar();
		c = toupper(c);
        switch (c) {
			case 'R': 
				printf("\n Dictionary file name: ");
				scanf("%s", fname);
				wcount = build_dictionary(fname);
				printf(" Total number of words: %d \n", wcount);
				break;
			case 'S': 
				printf("\n Word: ");
				scanf("%s", w1);
				w2 = bst_search(w1);
				if (w2) printf (" Meaning: %s \n", w2);
				else printf(" No such word ! \n");
				break;
			case 'P': 
				printf ("\n");
				bst_show_inorder(root); 
				break;
			case 'Q': 
				printf("\n");
				exit(1);
			default :
                break;
        } while(getchar() != '\n');
    }
}

int build_dictionary(char *fname) {
    FILE *ifp;
    char w1[100];
    char w2[100];
    int cnt = 0;

    ifp = fopen(fname, "r");
    while(fscanf(ifp, "%s %s", w1, w2) == 2) {
        printf("%s %s\n", w1, w2);
        bst_insert(w1, w2);
        cnt++;
    }

    fclose(ifp);
    return cnt;
}
void bst_insert(char* w1, char* w2) {
    TreeNode* insert = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* tmp = root;
    strcpy(insert->w1, w1);
    strcpy(insert->w2, w2);
    insert->left = NULL;
    insert->right = NULL;

    if(root == NULL) {
        root = insert;
    }
    else {
        while(1) {
            if(strcmp(tmp->w1, insert->w1) < 0) {
                if(tmp->right == NULL) {
                   tmp->right = insert;
                   break;
                }
                else tmp = tmp->right;
            }
            else if (strcmp(tmp->w1, insert->w1) > 0) {
                if(tmp->left == NULL) {
                    tmp->left = insert;
                    break;
                }
                else tmp = tmp->left;
            }
        }
    }
}

char* bst_search(char* w1) {
    TreeNode* tmp = root;
    while(1) {
        if(tmp == NULL) {
            return NULL;
        }
        if(strcmp(tmp->w1, w1) == 0) {
            return tmp->w2;
        }
        else if(strcmp(tmp->w1, w1) > 0) {
            tmp = tmp->left;
        }
        else tmp = tmp->right;
    }
}
void bst_show_inorder(TreeNode* root) {
    if(root != NULL) {
        bst_show_inorder(root->left);
        printf("%s %s\n", root->w1, root->w2);
        bst_show_inorder(root->right);
    }
}