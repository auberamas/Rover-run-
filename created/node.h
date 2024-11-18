//
// Created by pierr on 11/9/2024.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H

#include "../modified/moves.h"
#include <stdlib.h>
#include <assert.h>

/*file creating a node structure (for tree) and a queue structure for node

/*STRUCTURE FOR NODE : */
/**
 * structure for a node
 */
typedef struct s_node
{
    int value; // value of the square reached
    int depth;
    struct s_node **sons;
    int nbSons; // physical size of the array
    t_move movement;
    t_localisation localisation;
    struct s_node *parent;
} t_node;


/*STUCTURE FOR QUEUE OF NODE : */

/**
 * @brief Structure for the queue of integers
 */
typedef struct sn_queue
{
    t_node** nodes;
    int size;
    int last;
    int first;
} node_queue;


/*FUNCTION FOR NODE : */
/**
 * @brief initialize a node
 * @param value the value to be stored in the node
 * @param nb_sons the number of sons: physical size of the array
 * @param depth int, depth of the node
 * @param parent node (t_node), parent of the node
 *
 * @return
 */
t_node *createNode(int value, int nb_sons, int depth, t_node* parent, t_localisation localisation, t_move movement);




/*QUEUE FOR NODE : */

/**
 * @brief Function to create a queue
 * @param size : the size of the queue
 * @return the queue
 */
node_queue createNodeQueue(int);

/**
 * @brief Function to enqueue a value in the queue
 * @param p_queue : pointer to the queue
 * @param value : the position to enqueue
 * @return none
 */
void enqueueNode(node_queue* , t_node*);

/**
 * @brief Function to dequeue a value from the queue
 * @param p_queue : pointer to the queue
 * @return the value dequeued
 */
t_node* dequeueNode(node_queue *);

/**
 * @brief Function to check if the queue is empty
 * @return integer 1 if empty 0 else
 */
int isNodeQueueEmpty(node_queue);

#endif //UNTITLED1_NODE_H
