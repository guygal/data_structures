#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

void clearQueue(Queue *queue)
{
    if (queue == NULL || queue->size == 0)
        return;

    QueueNode *q = queue->head;
    while (q != NULL) {
        queue->head = queue->head->next;
        free(q);
        q = queue->head;
    }
}

void freeQueue(Queue **queue)
{
    clearQueue(*queue);
    free(*queue);
    *queue = NULL;
}

void pushQueue(Queue *q, QUEUE_DATA_TYPE data)
{
    if (q == NULL)
        return;

    QueueNode *n = (QueueNode *)malloc(sizeof(QueueNode));
    if (n == NULL) {
        fprintf(stderr, "Failed to allocate memory for the queue\n");
        return;
    }
    n->data = data;
    n->next = NULL;

    if (q->tail == NULL) {
        q->tail = n;
        q->head = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }

    ++(q->size);
}

QUEUE_DATA_TYPE popQueue(Queue *q)
{
    if (q == NULL || q->head == NULL)
        return NULL;

    QUEUE_DATA_TYPE data = q->head->data;
    QueueNode *n = q->head->next;
    free(q->head);

    q->head = n;

    if (q->head == NULL)
        q->tail = NULL;

    --(q->size);

    return data;
}

void printQueue(Queue *q)
{
    if (q == NULL)
        return;

    QueueNode *n = q->head;
    while (n) {
        //printf("%d ", n->data);
        printf("%d ", n->data->data);
        n = n->next;
    }
    printf("\n");
}

int isEmptyQueue(Queue *q)
{
    //return q->head == q->tail == NULL;
    //return q->head == NULL;
    return q->size == 0;
}