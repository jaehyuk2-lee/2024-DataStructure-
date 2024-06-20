#define	MAX_SIMUL_TIME 20		
#define	MAX_PRINTING_TIME 10	
#define	JOB_ARRIVAL_PROB 0.5	
#define	boolean	unsigned char
#define	true 1
#define	false 0
#define	MAX_PQ_SIZE 1000 

int current_time = 0;
int new_job_id = 0;
int current_job_id;
int remaining_time;

int total_wait_time;
int num_printed_jobs;

typedef struct {
	int key;
	int id;
	int arrival_time;
	int duration;
}Job;
typedef Job Element;

Element PQ[MAX_PQ_SIZE];
int PQ_size = 0;

void insert_job(int id, int arrival_time, int duration);
void process_next_job();
boolean is_job_arrived();
boolean is_printer_idle();

double random();
int get_random_duration();

void insert_PQ(Element item);
Element delete_PQ();
void PQ_show();
boolean is_PQ_empty();
