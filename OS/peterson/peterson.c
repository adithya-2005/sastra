
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
volatile bool flag[2] = {false, false};
volatile int turn = 0;
void critical_section(int process_id) {
    printf("Process %d is in the critical section.\n", process_id);
}
void peterson(int process_id) {
    int other = 1 - process_id;
    flag[process_id] = true;
    turn = other;
    while (flag[other] && turn == other) {
    }
    critical_section(process_id);
    flag[process_id] = false;
}
void* process(void* arg) {
    int process_id = *(int*)arg;
    printf("Process %d is doing non-critical work.\n", process_id);
    peterson(process_id);
    printf("Process %d is doing more non-critical work.\n", process_id);
    return NULL;
}

int main() {
    pthread_t threads[2];
    int process_ids[2] = {0, 1};
    for (int i = 0; i < 2; ++i) {
        pthread_create(&threads[i], NULL, process, (void*)&process_ids[i]);
    }
    for (int i = 0; i < 2; ++i) {
        pthread_join(threads[i], NULL);
    }
   
    return 0;
}


