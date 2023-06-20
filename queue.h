//
// Created by Rani Wishahy on 6/14/23.
//
#ifndef IMAGEENCRYPTION_QUEUE_H
#define IMAGEENCRYPTION_QUEUE_H

#include <pthread.h>
#include <stdbool.h>

typedef void* Data;

pthread_mutex_t queue_lock;

typedef struct q_node* QueueNode;

QueueNode queueNodeCreate(int, char*, Data, size_t);
void queueNodeDestroy(QueueNode);
QueueNode queueNodeCopy(QueueNode);


typedef struct queue_t* Queue;

Queue queueCreate(size_t);
void queueDestroy(Queue);
bool queuePush(Queue, QueueNode);
QueueNode queuePop(Queue);
QueueNode queueFront(Queue);
size_t queueSize(Queue);
bool queueIsEmpty(Queue);
QueueNode queueGetNodeByID(Queue, int);

#endif //IMAGEENCRYPTION_QUEUE_H
