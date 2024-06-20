#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash_dictionary1.h"

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
                linear_probing_search(item);
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
        strcpy(hash_table[i].key, "");
        strcpy(hash_table[i].data, "");
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
        linear_probing_insert(tmp);
    }
    fclose(ifp);
}
void linear_probing_insert(Element item) {
    int h = hash(item.key);
    while(1) {
        if(strcmp(hash_table[h].key, "") != 0) {
            int i = 0;
            while(strcmp(hash_table[(h+i)%TABLE_SIZE].key, "") != 0) {
                i++;
                if(i == TABLE_SIZE){
                    break;
                }
            }
            if(i == TABLE_SIZE) {
                printf("Hash Table is full\n");
                break;
            }
            else h = (h+i)%TABLE_SIZE;
        }
        else {
            strcpy(hash_table[h].key, item.key);
            strcpy(hash_table[h].data, item.data);
            wcount++;
            break;
        }
    }
}
void linear_probing_search(Element item) {
    int h = hash(item.key);
    printf("start_hash_value = %d\n", h);

    while(1) {
        if(strcmp(hash_table[h].key, "") == 0) {
            printf("No such word !\n");
            break;
        }

        if(strcmp(hash_table[h].key, item.key) != 0) {
            int i = 0;
            while(strcmp(hash_table[(h+i)%TABLE_SIZE].key, item.key) != 0) {
                i++;
                if(i == TABLE_SIZE){
                    break;
                }
                num_comparison++;
                if(strcmp(hash_table[(h+i)%TABLE_SIZE].key, "") == 0){
                    break;
                }
            }
            if(i == TABLE_SIZE) {
                printf("No such Word !\n");
                break;
            }
            else h = (h+i)%TABLE_SIZE;
        }
        else {
            printf("Meaning: %s\n", hash_table[h].data);
            break;
        }
    }
}

void hash_show() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("hash_table[%d] = <%s , %s>\n", i, hash_table[i].key, hash_table[i].data);
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