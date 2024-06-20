#define MAX_SIMUL_TIME 20
#define MAX_PRINTING_TIME 5
#define JOB_ARRIVAL_PROB 0.5
#define boolean unsigned char
#define true 1
#define false 0

int current_time = 0;
int new_job_id = 0;

int current_job_id;
int remaining_time;

int total_wait_time = 0;
int num_printed_jobs = 0;

typedef struct {
    int id;
    int arrival_time;
    int duration;
} Job;

typedef struct QueueNode {
    Job item;
    struct QueueNode* link;
} QueueNode;

QueueNode* front, * rear;

void insert_job_into_queue(int id, int arrival_time, int duration);
void process_next_job();

boolean is_job_arrived();
boolean is_printer_idle();

double Random();
int get_random_duration();

void addq(Job e);
Job deleteq();
boolean is_queue_empty();
void queue_show();