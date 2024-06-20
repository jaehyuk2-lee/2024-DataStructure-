#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priority_queue_simulation.h"

void main() {
	int duration;
	srand(time(NULL));

	while (current_time < MAX_SIMUL_TIME) {
		printf("\n----- time %d ----- \n", current_time);;

		if (is_job_arrived()) {
			++new_job_id;
			duration = get_random_duration();
			insert_job(new_job_id, current_time, duration);
		}

		if (is_printer_idle()) {
			if (!is_PQ_empty()) process_next_job();
		}
		else {
			printf(" 아직 Jop <%d>을 프린트하고 있습니다 ...남은 시간 : %d \n", current_job_id, remaining_time);
			--remaining_time;
		}
		PQ_show();
		++current_time;
	}
	printf("\n완료된 프린트 job = %d 개 \n", num_printed_jobs);
	printf("평균 지연 시간    = %f 단위시간 \n\n", (double)total_wait_time / num_printed_jobs);
}

void insert_job(int id, int arrival_time, int duration) {
	Job p;

	p.key = duration;
	p.id = id;
	p.arrival_time = arrival_time;
	p.duration = duration;

	insert_PQ(p);
	printf(" 새 jop <%d>이 들어 왔습니다. key(출력 시간) = %d 입니다. \n", id, duration);

}
void process_next_job() {
	Job p;
	p = delete_PQ();
	current_job_id = p.id;
	remaining_time = p.duration - 1;
	total_wait_time += current_time - p.arrival_time;
	++num_printed_jobs;

	printf(" 프린트를 시작합니다 - jop <%d>... \n", current_job_id);

}
boolean is_job_arrived() {
	if (random() < JOB_ARRIVAL_PROB)
		return true;
	else
		return false;

}
boolean is_printer_idle() {
	if (remaining_time <= 0)
		return true;
	else
		return false;
}

double random() {
	return rand() / (double)RAND_MAX;
}
int get_random_duration() {
	return (int)(MAX_PRINTING_TIME * random()) + 1;
}

void insert_PQ(Element item) {
	int i = ++PQ_size;
	while ((i != 1) && item.key < PQ[i / 2].key) {
		PQ[i] = PQ[i / 2];
		i /= 2;
	}
	PQ[i] = item;
}
Element delete_PQ() {
	Element min = PQ[1];
	Element temp = PQ[PQ_size--];
	int p = 1, c = 2;
	while (c <= PQ_size) {
		if ((c < PQ_size) && (PQ[c].key > PQ[c + 1].key)) c++;

		if (temp.key <= PQ[c].key)break;
		PQ[p] = PQ[c];
		p = c;
		c = c * 2;
	}
	PQ[p] = temp;
	return min;
}
void PQ_show() {
	printf("현재 프린트 큐<key, id> : [ ");
	for (int i = 1; i <= PQ_size; i++) {
		printf("<%d %d> ", PQ[i].key, PQ[i].id);
	}
	printf("]\n");
}
boolean is_PQ_empty() {
	if (PQ_size == 0) return true;
	else return false;
}
