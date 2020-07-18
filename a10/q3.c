#include <stdlib.h>
#include <stdio.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define NUM_THREADS 3
uthread_t threads[NUM_THREADS];
uthread_mutex_t stack_lock;
uthread_cond_t stack_acond;
int aPrinted;

void randomStall() {
    int i, r = random() >> 16;
    while (i++<r);
}

void waitForAllOtherThreads() {
    uthread_mutex_lock(stack_lock);
    aPrinted = aPrinted + 1;
    while(aPrinted!=NUM_THREADS) {
        uthread_cond_wait(stack_acond);
    }
    uthread_cond_signal(stack_acond);
    uthread_mutex_unlock(stack_lock);
}

void* p(void* v) {
    randomStall();
    printf("a\n");
    waitForAllOtherThreads();
    printf("b\n");
    return NULL;
}

int main(int arg, char** arv) {
    stack_lock = uthread_mutex_create();
    stack_acond = uthread_cond_create(stack_lock);
    uthread_init(3);
    aPrinted = 0;
    for (int i=0; i<NUM_THREADS; i++)
        threads[i] = uthread_create(p, NULL);
    for (int i=0; i<NUM_THREADS; i++)
        uthread_join (threads[i], NULL);
    printf("------\n");
    uthread_mutex_destroy(stack_lock);
}