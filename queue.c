//
// Created by Rani Wishahy on 6/14/23.
//
#include "queue.h"
#include <malloc.h>
#include <string.h>

#define SUCCESS (true)
#define FAILURE (false)


pthread_mutex_t global_lock;
pthread_cond_t readers_allowed;
pthread_cond_t writers_allowed;
int writers_inside = 0;
int readers_inside = 0;
int writers_waiting = 0;

//***************************************************** Locks ********************************************************//

void readerLock() {
    pthread_mutex_lock(&global_lock);
    while (writers_inside + writers_waiting > 0) {
        pthread_cond_wait(&readers_allowed, &global_lock);
    }
    readers_inside++;
    pthread_mutex_unlock(&global_lock);
}

void readerUnlock() {
    pthread_mutex_lock(&global_lock);
    readers_inside--;
    if (readers_inside == 0) {
        pthread_cond_signal(&writers_allowed);
    }
    pthread_mutex_unlock(&global_lock);
}

void writerLock() {
    pthread_mutex_lock(&global_lock);
    writers_waiting++;
    while (writers_inside + readers_inside > 0) {
        pthread_cond_wait(&writers_allowed, &global_lock);
    }
    writers_waiting--;
    writers_inside++;
    pthread_mutex_unlock(&global_lock);
}

void writerUnlock() {
    pthread_mutex_lock(&global_lock);
    writers_inside--;
    pthread_cond_signal(&writers_allowed);
    pthread_cond_broadcast(&readers_allowed);
    pthread_mutex_unlock(&global_lock);
}

//*************************************************** QueueNode ******************************************************//

struct q_node {
    int id;
    char* name;
    Data data;
    size_t data_size;
    QueueNode next;
};


QueueNode queueNodeCreate(int id, char* name, Data data, size_t size) {
    QueueNode new_node = malloc(sizeof (*new_node));
    new_node->id = id;
    new_node->name = name;
    memcpy(new_node->data, data, size); // no overlap, one is on the stack the other is on the heap.
    new_node->data_size = size;
    new_node->next = NULL;
    return new_node;
}

void destroyQueueNode(QueueNode q_node) {
    if (!q_node) return;
    free(q_node->data);
    free(q_node);
}

QueueNode queueNodeCopy(QueueNode to_copy) {
    if (!to_copy) return NULL;
    QueueNode copy = malloc(sizeof (*copy));
    memcpy(copy, to_copy, sizeof (*to_copy));
    return copy;
}


//***************************************************** Queue ********************************************************//

struct queue_t {
    QueueNode head;
    QueueNode tail;
    size_t size;
    size_t max_size;
};


Queue queueCreate(size_t max_size) {
    Queue new_q = malloc(sizeof (*new_q));
    new_q->head = new_q->tail = NULL;
    new_q->size = 0;
    new_q->max_size = max_size;
    return new_q;
}


void queueDestroy(Queue q) {
    writerLock();
    QueueNode ptr = q->head;
    while (ptr) {
        QueueNode to_delete = ptr;
        ptr = ptr->next;
        free(to_delete);
    }
    writerUnlock();
}


bool queuePush(Queue q, QueueNode new_node) {
    writerLock();
    if (!q || !new_node || q->size == q->max_size) {
        writerUnlock();
        return FAILURE;
    }
    q->tail->next = new_node;
    q->tail = new_node;
    q->size++;
    writerUnlock();
    return SUCCESS;
}


QueueNode queuePop(Queue q) {
    writerLock();
    if (!q || q->size == 0) {
        writerUnlock();
        return NULL;
    }
    QueueNode popped_node = q->head;
    q->head = q->head->next;
    q->size--;
    writerLock();
    return popped_node;
}


QueueNode queueFront(Queue q) {
    readerLock();
    if (!q || q->size == 0) {
        readerUnlock();
        return NULL;
    }
    QueueNode copy = queueNodeCopy(q->head);
    readerUnlock();
    return copy;
}


size_t queueSize(Queue q) {
    return q->size;
}


bool queueIsEmpty(Queue q) {
    return q->size == 0;
}


QueueNode queueGetNodeByID(Queue q, int id) {
    readerLock();
    if (!q) return NULL;
    QueueNode ptr = q->head;

    while(ptr) {
        if (ptr->id == id) {
            QueueNode copy = queueNodeCopy(ptr);
            readerUnlock();
            return copy;
        }
        ptr = ptr->next;
    }

    readerUnlock();
    return NULL;
}

//********************************************************************************************************************//

