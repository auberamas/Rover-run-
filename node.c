//
// Created by pierr on 11/9/2024.
//

#include "node.h"
#include <stdio.h>

t_node* createNode(int value, int nb_sons, int depth, t_node* parent, t_localisation localisation, t_move movement){
    t_node *new_node;
    new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = value;
    new_node->nbSons = nb_sons;
    new_node->sons = (t_node **)malloc(nb_sons*sizeof(t_node *));

    for (int i=0; i <nb_sons; i++)
    {
        new_node->sons[i]=NULL;
    }
    new_node->depth = depth;
    new_node->parent = parent;
    new_node->localisation = localisation;
    new_node->movement = movement;
    return new_node;
}


/**
 * @brief Function to create a queue
 * @param size : the size of the queue
 * @return the queue
 */
node_queue createNodeQueue(int size)
{
    // the size of the queue must be positive
    assert(size > 0);
    node_queue queue;
    queue.size = size;
    queue.first = 0;
    queue.last = 0;
    queue.nodes = (t_node **)malloc(size * sizeof(t_node*));
    return queue;
}

void enqueueNode(node_queue *p_queue, t_node* node)
{
    // the queue must not be full
    assert((p_queue->last - p_queue->first) < p_queue->size);
    p_queue->nodes[(p_queue->last) % p_queue->size] = node;
    p_queue->last++;
    return;
}

t_node* dequeueNode(node_queue* p_queue)
{
    // the queue must not be empty
    assert(p_queue->last != p_queue->first);
    p_queue->first++;
    return p_queue->nodes[(p_queue->first - 1) % p_queue->size];
}

int isNodeQueueEmpty(node_queue q){
    return (q.first == q.last);
}