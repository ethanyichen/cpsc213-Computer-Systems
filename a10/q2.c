#include <stdlib.h>
#include <stdio.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

const int N = 100000;
int cnt = 0;

uthread_t t0, t1, t2;
uthread_mutex_t stack_lock;

void countUp() {
    uthread_mutex_lock(stack_lock);
    for (int i = 0; i < N; i++) {
        cnt += 1;
    }
    uthread_mutex_unlock(stack_lock);
}

void countDown() {
    uthread_mutex_lock(stack_lock);
    for (int i = 0; i < N; i++) {
        cnt -= 1;
    }
    uthread_mutex_unlock(stack_lock);
}

void *count(void *v) {
    countUp();
    countDown();
    return NULL;
}

int main(int arg, char **arv) {
    stack_lock = uthread_mutex_create();
    uthread_init(4);
    t0 = uthread_create(count, NULL);
    t1 = uthread_create(count, NULL);
    t2 = uthread_create(count, NULL);
    uthread_join(t0, NULL);
    uthread_join(t1, NULL);
    uthread_join(t2, NULL);
    uthread_mutex_destroy(stack_lock);
    printf("cnt = %d %s\n", cnt, cnt == 0 ? "" : "XXX");
}