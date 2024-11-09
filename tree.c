//
// Created by pierr on 10/21/2024.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

#include "nodequeue.h"

/* prototypes of local functions */
/* local functions are used only in this file, as helper functions */

/**
 * @brief Function to compute the factorial of a number over the factorial of an other number
 * @param a : numerator
 * @param b : Denominator
 * @return the new orientation of the robot
 */
int factorialDivision(int a, int b);

int factorialDivision(int a, int b){
    int mult = 1;
    if (b<a){
        for(int i=a; i>=b; i--)
            mult *= i;
        return mult;
    }else{
        printf("Factorial division ERROR");
        return -1;
    }

}



t_node* createNode(int value, int nb_sons, int depth, t_node* parent){
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
    return new_node;
}



t_node* createTree(t_move* list_of_move, int nbDrawMove, int nbMove){ // need to add when crevasse and when outside of the map
    t_node* root = createNode(-1,nbDrawMove,0,NULL);
    for(int i = 0; i<nbDrawMove;i++)
        root->sons[i]= createNode(list_of_move[i],nbDrawMove-1,1,root);
    t_node node = *root;
    t_queue q = createNodeQueue(factorialDivision(nbDrawMove,nbDrawMove-nbMove)); // the maximum number of nodes in the queue will be the number of parents of leaves since we will process depth by depth and when a floor is putted in it means that a floor is dequeued
    enqueueNode(&q, node);

    int notLast =1;

    while (!isNodeQueueEmpty(q)){
        node = dequeueNode(&q);
        if(node.depth!=nbMove){

        }
    }
}

