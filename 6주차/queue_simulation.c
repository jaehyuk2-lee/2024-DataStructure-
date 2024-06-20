#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue_simulation.h"

int main() {
    int duration;
    srand(time(NULL));
    front = rear = NULL;

    while (current_time < MAX_SIMUL_TIME) {
        printf("----- time %d -----\n", current_time);

        if (is_job_arrived()) {
            ++new_job_id;
            duration = get_random_duration();
            insert_job_into_queue(new_job_id, current_time, duration);
        }
        if (is_printer_idle()) {
            if (!is_queue_empty()) process_next_job();
        }
        else {
            printf("아직 Job<%d>을 프린트하고 있습니다... 남은시간 : %d\n", current_job_id, remaining_time);
            --remaining_time;
        }
        queue_show();
        ++current_time;
    }
    printf("완료된 프린트 job = %d 개\n", num_printed_jobs);
    printf("평균 지연 시간 = %lf 단위시간", (double)total_wait_time / num_printed_jobs);
    return 0;
}

void insert_job_into_queue(int id, int arrival_time, int duration) {
    Job p;
    p.id = id;
    p.arrival_time = arrival_time;
    p.duration = duration;

    addq(p);
    printf("새 Job<%d>이 들어왔습니다. 프린트 시간은 = %d입니다.\n", id, duration);
}
void process_next_job() {
    Job p;
    p = deleteq();
    current_job_id = p.id;
    remaining_time = p.duration - 1;
    total_wait_time = total_wait_time + current_time - p.arrival_time;

    ++num_printed_jobs;
    printf("프린트를 시작합니다 - Job<%d>...\n", current_job_id);
}

boolean is_job_arrived() {
    if (Random() < JOB_ARRIVAL_PROB) return true;
    else return false;
}
boolean is_printer_idle() {
    if (remaining_time <= 0) return true;
    else return false;
}

double Random() {
    return rand() / (double)RAND_MAX;
}
int get_random_duration() {
    return (int)(MAX_PRINTING_TIME * Random()) + 1;
}

void addq(Job e) {
    QueueNode* p;
    p = (QueueNode*)malloc(sizeof(QueueNode));
    p->item = e;
    p->link = NULL;

    if (is_queue_empty()) {
        front = rear = p;
    }
    else {
        rear->link = p;
        rear = p;
    }
}
Job deleteq() {
    Job ret;
    QueueNode* tmp;
    tmp = front;
    ret = front->item;
    front = front->link;
    free(tmp);
    return ret;
}

boolean is_queue_empty() {
    if (front == NULL) return true;
    else return false;
}

void queue_show() {
    QueueNode* p;
    p = front;

    printf("[ ");
    while (p != NULL) {
        printf("%d(%d) ", p->item.id, p->item.duration);
        p = p->link;
    }
    printf("]\n");
}