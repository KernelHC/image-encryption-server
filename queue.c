//
// Created by Rani Wishahy on 6/14/23.
//
#include "queue.h"
#include <malloc.h>
#include <string.h>

#define SUCCESS (true)
#define FAILURE (false)

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


bool queuePush(Queue q, QueueNode new_node) {
    if (!q || !new_node || q->size == q->max_size) return FAILURE;
    q->tail->next = new_node;
    q->tail = new_node;
    q->size++;
    return SUCCESS;
}


QueueNode queuePop(Queue q) {
    if (!q || q->size == 0) return NULL;
    QueueNode popped_node = q->head;
    q->head = q->head->next;
    q->size--;
    return popped_node;
}


QueueNode queueFront(Queue q) {
    if (!q || q->size == 0) return NULL;
    return queueNodeCopy(q->head);
}


size_t queueSize(Queue q) {
    return q->size;
}


bool queueIsEmpty(Queue q) {
    return q->size == 0;
}


QueueNode queueGetNodeByID(Queue q, int id) {
    if (!q) return NULL;
    QueueNode ptr = q->head;
    while(ptr) {
        if (ptr->id == id) return queueNodeCopy(ptr);
        ptr = ptr->next;
    }
    return NULL;
}



//********************************************************************************************************************//

