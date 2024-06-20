#define TABLE_SIZE 13
#define boolean unsigned char
#define true 1
#define false 0

typedef struct {
    char key[100];
    char data[100];
} Element;
Element hash_table[TABLE_SIZE];

int num_comparison;
int wcount;

void build_dictionary(char* fname);
void linear_probing_insert(Element item);
void linear_probing_search(Element item);
void hash_show();

int hash(char* key);
int transfrom(char* key);