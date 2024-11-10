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


t_node* createTree(t_move* list_of_move, int nbDrawnMove, int nbMove, t_map map, t_localisation locaMarc){ // need to add when crevasse and when outside of the map
    printf("\nStarting to create the tree.\n");
    // initialisation of the root
    t_node* root = createNode(map.costs[locaMarc.pos.x][locaMarc.pos.y],nbDrawnMove,0,NULL,locaMarc, ROOT);
    node_queue q = createNodeQueue(factorialDivision(nbDrawnMove,nbDrawnMove-nbMove)); // the maximum number of nodes in the queue will be the number of parents of leaves since we will process depth by depth and when a floor is putted in it means that a floor is dequeue
    t_localisation newLoc;
    printf("Root initialized. ");
    for(int i = 0; i<nbDrawnMove; i++) {
        newLoc = updateLocalisationMap(list_of_move[i], locaMarc, map);
        root->sons[i] = createNode(map.costs[newLoc.pos.x][newLoc.pos.y], nbDrawnMove - 1, 1, root, newLoc, list_of_move[i]);
        enqueueNode(&q, *(root->sons[i]));
        root->sons[i];
    }
    printf("Sons of root added.\n");

    int layer = 0;
    t_node node;
    while (!isNodeQueueEmpty(q)){
        node = dequeueNode(&q);
        if(node.depth!=layer){
            layer = node.depth;
            printf("\nFrom layer %d :", layer);
        }
        printf("\n\tAdding sons : ");
        if(node.depth!=nbMove){
            int find = 0;
            int idx = 0;
            for(int i = 0; i<node.parent->nbSons; i++) {
                if(!find && node.parent->sons[i]->movement == node.movement) {
                    find == 1;
                }else{
                    printf("Son %d ", idx);
                    t_move itsmove = node.parent->sons[i]->movement;
                    newLoc = updateLocalisationMap(itsmove, node.localisation, map);
                    printf("coo (%d,%d) ", getX(newLoc),getY(newLoc));
                    if (isValidLocalisation(newLoc.pos,map.x_max,map.y_max)){
                        node.sons[idx] = createNode(map.costs[getX(newLoc)][getY(newLoc)], node.nbSons -1, node.depth+1, &node, newLoc, itsmove);
                        enqueueNode(&q,*(node.sons[idx]));
                        idx ++;
                    } else{
                        printf("Invalid pos or Crevasse.");
                        node.nbSons--;
                    }
                }
            }
        } else{
            break;
        }
    }
    printf("\nTree successfuly generated.\n");
    return root;
}
