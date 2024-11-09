//
// Created by pierr on 11/9/2024.
//

#include "nodequeue.h"

#include <assert.h>
#include <stdlib.h>

/**
 * @brief Function to create a queue
 * @param size : the size of the queue
 * @return the queue
 */
t_queue createNodeQueue(int size)
{
    // the size of the queue must be positive
    assert(size > 0);
    t_queue queue;
    queue.size = size;
    queue.first = 0;
    queue.last = 0;
    queue.nodes = (t_node *)malloc(size * sizeof(t_node));
    return queue;
}

void enqueueNode(t_queue *p_queue, t_node node)
{
    // the queue must not be full
    assert((p_queue->last - p_queue->first) < p_queue->size);
    p_queue->nodes[(p_queue->last) % p_queue->size] = node;
    p_queue->last++;
    return;
}

t_node dequeueNode(t_queue* p_queue)
{
    // the queue must not be empty
    assert(p_queue->last != p_queue->first);
    p_queue->first++;
    return p_queue->nodes[(p_queue->first - 1) % p_queue->size];
}

int isNodeQueueEmpty(t_queue q){
    return (q.first == q.last);
}
