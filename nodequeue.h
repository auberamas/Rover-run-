//
// Created by pierr on 11/9/2024.
//

#ifndef UNTITLED1_NODEQUEUE_H
#define UNTITLED1_NODEQUEUE_H

#include "tree.h"

/**
 * @brief Structure for the queue of integers
 */
typedef struct s_queue
{
    t_node* nodes;
    int size;
    int last;
    int first;
} t_queue;

/**
 * @brief Function to create a queue
 * @param size : the size of the queue
 * @return the queue
 */
t_queue createNodeQueue(int);

/**
 * @brief Function to enqueue a value in the queue
 * @param p_queue : pointer to the queue
 * @param value : the position to enqueue
 * @return none
 */
void enqueueNode(t_queue *,t_node);

/**
 * @brief Function to dequeue a value from the queue
 * @param p_queue : pointer to the queue
 * @return the value dequeued
 */
t_node dequeueNode(t_queue *);
/**
 * @brief Function to check if the queue is empty
 * @return integer 1 if empty 0 else
 */
int isNodeQueueEmpty(t_queue);

#endif //UNTITLED1_NODEQUEUE_H
