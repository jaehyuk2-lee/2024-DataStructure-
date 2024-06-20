#include "o_list_merge.h"

int main() {
    ArrayList L1 = { {1,3,5,7,9}, 5 };
    ArrayList L2 = { {2,4,6,8}, 4 };

    printf("리스트 L1: ");
    for (int i = 0; i < L1.size; i++) {
        printf("%d ", L1.array[i]);
    }
    printf("\n");
    printf("리스트 L2: ");
    for (int i = 0; i < L2.size; i++) {
        printf("%d ", L2.array[i]);
    }
    printf("\n");

    ArrayList merged_list = list_merge(&L1, &L2);
    printf("병합된 리스트: ");
    for (int i = 0; i < merged_list.size; i++) {
        printf("%d ", merged_list.array[i]);
    }
    printf("\n");

    return 0;
}

ArrayList list_merge(ArrayList* L1, ArrayList* L2) {
    ArrayList merged_list = { NULL, 0 };
    for (int i = 0; i < L1->size; i++) {
        insert(&merged_list, get_element(*L1, i));
    }
    for (int i = 0; i < L2->size; i++) {
        insert(&merged_list, get_element(*L2, i));
    }

    return merged_list;
}

Element get_element(ArrayList L, int i) {
    return L.array[i];
}

void insert(ArrayList* L, Element e) {
    L->array[L->size] = e;
    L->size++;
}