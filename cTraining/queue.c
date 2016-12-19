#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int argc, char const *argv[])
{
	Queue *my_queue=queue_new();
	printf("%d\n",queue_is_empty(my_queue));
	if(queue_push_head(my_queue,10)==0)
	{
		printf("push head success\n");
		
		queue_push_tail(my_queue,101);
		queue_push_head(my_queue,101);
		printf("%d\n",queue_pop_head(my_queue));
		printf("%d\n",queue_pop_tail(my_queue));
		printf("%d\n",queue_pop_tail(my_queue));
	}
	else
	{
		printf("push head failed\n");
	}

	return 0;
}

Queue *queue_new()
{
	Queue *queue;

	queue=malloc(sizeof(Queue));

	if (queue==NULL)
	{
		return NULL;
	}

	queue->head=NULL;
	queue->tail=NULL;

	return queue;
}

void queue_free(Queue *queue)
{
	while(!queue_is_empty(queue))
	{
		queue_pop_head(queue);
	}

	free(queue);
}

int queue_is_empty(Queue *queue)
{
	return queue->head==NULL;
}

int queue_push_head(Queue *queue,QueueValue data)
{
	QueueEntry *entry;

	entry = malloc(sizeof(QueueEntry));

	if (entry == NULL)
	{
		free(entry);
		return -1;
	}

	entry->data = data;
	entry->next = queue->head;
	entry->prev = NULL;

	if (queue->head == NULL)
	{
		queue->head=entry;
		queue->tail=entry;
	}
	else
	{
		queue->head->prev=entry;
		queue->head=entry;
	}

	return 0;
}

QueueValue queue_pop_head(Queue *queue)
{
	QueueEntry *entry;
	QueueValue value;

	entry = malloc(sizeof(QueueEntry));
	/*queue is empty*/
	if (queue->head==NULL)
	{
		return QUEUE_EMPTY;
	}
	else
	{
		/*queue is not empty*/
		entry = queue->head;
		value = entry->data;

		queue->head = entry->next;

		if (queue->head==NULL)
		{
			queue->tail=NULL;
		}
		else
		{
			queue->head->prev = NULL;
		}
		

		free(entry);

		return value;
	}
}

QueueValue queue_peek_head(Queue *queue)
{
	QueueEntry *entry;
	entry = malloc(sizeof(QueueEntry));

	if (queue==NULL)
	{
		return QUEUE_EMPTY;
	}
	else
	{
		entry = queue->head;

		return entry->data;
	}

}

int queue_push_tail(Queue *queue,QueueValue value)
{
	QueueEntry *entry;

	entry = malloc(sizeof(QueueEntry));

	if (entry== NULL)
	{
		free(entry);
		return -1;
	}

	entry->data=value;
	entry->next=NULL;
	entry->prev=queue->tail;

	/*queue is empty*/
	if (queue->head==NULL)
	{
		queue->tail=entry;
		queue->head=entry;	
	}
	else
	{
		queue->tail->next=entry;
		queue->tail=entry;
		return 0;
	}
}

QueueValue queue_pop_tail(Queue *queue)
{
	QueueEntry *entry;
	QueueValue value;


	if (queue->tail==NULL)
	{
		return QUEUE_EMPTY;
	}
	else
	{
		entry = queue->tail;

		value=entry->data;

		queue->tail=entry->prev;

		if (queue->tail==NULL)
		{
			queue->head=NULL;
		}
		else
		{
			queue->tail->next=NULL;
		}

		free(entry);

		return value;
	}
}

QueueValue queue_peek_tail(Queue *queue)
{
	QueueValue value;

	if (queue->tail==NULL)
	{
		return QUEUE_EMPTY;
	}
	else
	{
		value=queue->tail->data;

		return value;
	}
}
