#define TABLE_SIZE 10000

int total_word = 0;

typedef struct WordData {
	char* word;
	char* file_name;
	int freq;
	struct WordData* link;
}WordData;

WordData* ht[TABLE_SIZE];

////////////////// 색인과정 ///////////////////
// 파일에서 인덱스 생성
void make_index(char* fname);
// 단어 노드 생성
WordData* new_node(char* word, char* file_name);
// 단어 노드 해싱
void insert_word(WordData* p);
// hash 함수
int hash(char* word);


///////////////// 검색과정 ///////////////////
// 찾는 단어의 index 반환
int search_word(char* word);
// 단어가 있는 파일명과 빈도수, 첫 문장을 출력
void print_result(int index);
// 파일의 첫 줄을 출력
void print_first_sentence(char* file_name);