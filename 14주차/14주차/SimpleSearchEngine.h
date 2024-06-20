#define TABLE_SIZE 10000

int total_word = 0;

typedef struct WordData {
	char* word;
	char* file_name;
	int freq;
	struct WordData* link;
}WordData;

WordData* ht[TABLE_SIZE];

////////////////// ���ΰ��� ///////////////////
// ���Ͽ��� �ε��� ����
void make_index(char* fname);
// �ܾ� ��� ����
WordData* new_node(char* word, char* file_name);
// �ܾ� ��� �ؽ�
void insert_word(WordData* p);
// hash �Լ�
int hash(char* word);


///////////////// �˻����� ///////////////////
// ã�� �ܾ��� index ��ȯ
int search_word(char* word);
// �ܾ �ִ� ���ϸ�� �󵵼�, ù ������ ���
void print_result(int index);
// ������ ù ���� ���
void print_first_sentence(char* file_name);