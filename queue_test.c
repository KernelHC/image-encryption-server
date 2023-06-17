//
// Created by Rani Wishahy on 6/15/23.
//
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <syscall.h>
#include "queue.h"
#include "pthread.h"

#define NUM_TESTS (14)

void sanityTest();
void queuePushTest();
void queuePopTest();
void queueFrontTest();
void queueSizeTest();
void queueMaxSizeTest();
void queueStressTest();

void concurrentSanityTest();
void concurrentPushTest();
void concurrentPopTest();
void concurrentFrontTest();
void concurrentSizeTest();
void concurrentMaxSizeTest();
void concurrentStressTest();

void* tests[] = {
        sanityTest,
        queuePushTest,
        queuePopTest,
        queueFrontTest,
        queueSizeTest,
        queueMaxSizeTest,
        queueStressTest,
        concurrentSanityTest,
        concurrentPushTest,
        concurrentPopTest,
        concurrentFrontTest,
        concurrentSizeTest,
        concurrentMaxSizeTest,
        concurrentStressTest,
        0
};

void sanityTest() {
    Queue q = queueCreate();
    assert(q);
    assert(queueIsEmpty(q));
    assert(queueSize(q) == 0);
    queueDestroy(q);
}

void queuePushTest() {

}

int main () {
    pthread_t* workers[NUM_TESTS];
    for (int i = 0; tests[i] != NULL; i++) {
        pthread_create(workers[i], NULL, tests[i], NULL);
    }
}