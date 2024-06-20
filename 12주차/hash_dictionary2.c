#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash_dictionary2.h"

int main() {
    char c, fname[20];
    char key[100], *data;
    printf("*********** Command *********\n");
    printf("R: Read data, S: Search data\n");
    printf("P: Print hash table, Q: Quit\n");
    printf("*****************************\n");
    while(1) {
        printf("\nCommand> ");
        c = getchar();
        c = toupper(c);

        switch(c) {
            case 'R':
                printf("\nDictionary file name: ");
                scanf("%s", fname);
                build_dictionary(fname);
                printf("Total number of words: %d \n", wcount);
                break;
            case 'S':
                printf("\nWord: ");
                scanf("%s", key);
                num_comparison = 1;
                Element item;
                strcpy(item.key, key);
                chain_search(item);
                printf("Total number of comparison = %d\n",num_comparison);
                break;
            case 'P':
                printf("\n");
                hash_show();
                break;
            case 'Q':
                printf("\n");
                exit(1);
            default:
                break;
        }while(getchar()!='\n');
    }
}

void build_dictionary(char* fname) {
    char key[100], data[200];
    FILE *ifp;

    for(int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = (ListNode*)malloc(sizeof(ListNode));
    }

    if((ifp = fopen(fname,"r")) == NULL) {
        printf("No such file!\n");
        exit(1);
    }

    wcount = 0;
    while(fscanf(ifp, "%s %s", key, data) == 2) {
        Element tmp;
        strcpy(tmp.key, key);
        strcpy(tmp.data, data);
        chain_insert(tmp);
    }
    fclose(ifp);
}
void chain_insert(Element item) {
    ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));
    strcpy(tmp->item.key, item.key);
    strcpy(tmp->item.data, item.data);
    tmp->link = NULL;

    ListNode* p = hash_table[hash(item.key)];
    while(p->link) {
        p = p->link;
    }
    p->link = tmp;
    wcount++;
}
void chain_search(Element item) {
    int h = hash(item.key);
    
    ListNode*p = hash_table[h]->link;
    while(p) {
        if(strcmp(p->item.key,item.key) == 0) {
            printf("Meaning: %s\n", p->item.data);
            break;
        }
        p = p->link;
        num_comparison++;
    }
    if(p==NULL) {
        printf("No such word!\n");
    }
}
void hash_show() {
    ListNode* p;
    for(int i = 0; i < TABLE_SIZE; i++) {
        p = hash_table[i]->link;
        printf("hash_table[%d]: ", i);
        while(p) {
            printf("<%s, %s> -> ", p->item.key, p->item.data);
            p = p->link;
        }
        printf("NULL\n");
    }
}

int hash(char* key) {
    return transfrom(key)%TABLE_SIZE;
}
int transfrom(char* key) {
    int ret = 0;
    for(int i = 0; key[i]; i++) {
        ret += (int)key[i];
    }
    return ret;
}