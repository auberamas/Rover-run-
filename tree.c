//
// Created by pierr on 10/21/2024.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>


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



t_node* createTree(t_move* list_of_move, int nbDrawnMove, int nbMove, t_map map, t_localisation locaMarc){ // need to add when crevasse and when outside of the map
    // initialisation of the root
    t_node* root = createNode(map.costs[locaMarc.pos.x][locaMarc.pos.y],nbDrawnMove,0,NULL,locaMarc, ROOT);
    node_queue q = createNodeQueue(factorialDivision(nbDrawnMove,nbDrawnMove-nbMove)); // the maximum number of nodes in the queue will be the number of parents of leaves since we will process depth by depth and when a floor is putted in it means that a floor is dequeue
    t_localisation newLoc;
    for(int i = 0; i<nbDrawnMove; i++) {
        newLoc = updateLocalisationMap(list_of_move[i], locaMarc, map);
        root->sons[i] = createNode(map.costs[newLoc.pos.x][newLoc.pos.y], nbDrawnMove - 1, 1, root, newLoc, list_of_move[i]);
        enqueueNode(&q, *(root->sons[i]));
        root->sons[i];
    }

    t_node node;
    while (!isNodeQueueEmpty(q)){
        node = dequeueNode(&q);
        if(node.depth!=nbMove){
            int find = 0;
            int idx = 0;
            for(int i = 0; i<node.parent->nbSons; i++) {
                if(!find && node.parent->sons[i]->movement == node.movement) {
                    find == 1;
                }else{
                    t_move itsmove = node.parent->sons[i]->movement;
                    newLoc = updateLocalisationMap(itsmove, node.localisation, map);
                    node.sons[idx] = createNode(map.costs[newLoc.pos.x][newLoc.pos.y], node.nbSons -1, node.depth+1, &node, newLoc, itsmove);
                    enqueueNode(&q,*(node.sons[idx]));
                    idx ++;
                }
            }
        }
    }
}
