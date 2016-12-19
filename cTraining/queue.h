#ifndef QUEUE_H
#define QUEUE_H 

typedef struct _QueueEntry QueueEntry;

typedef struct _Queue Queue;

#define QUEUE_EMPTY -1

typedef int QueueValue;

struct _QueueEntry {
	QueueValue data;
	QueueEntry *prev;
	QueueEntry *next;
};

struct _Queue {
	QueueEntry *head;
	QueueEntry *tail;
};

Queue *queue_new();

int queue_push_head(Queue *queue,QueueValue data);

QueueValue queue_pop_head(Queue *queue);

QueueValue queue_peek_head(Queue *queue);

void queue_free(Queue *queue);

int queue_is_empty(Queue *queue);

int queue_push_tail(Queue *queue,QueueValue value);

QueueValue queue_pop_tail(Queue *queue);

QueueValue queue_peek_tail(Queue *queue);



#endif


