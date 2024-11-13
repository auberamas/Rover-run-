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
    t_node* root = createNode(map.costs[getX(locaMarc)][getY(locaMarc)],nbDrawnMove,0,NULL,locaMarc, ROOT);
    node_queue q = createNodeQueue(factorialDivision(nbDrawnMove,nbDrawnMove-nbMove)); // the maximum number of nodes in the queue will be the number of parents of leaves since we will process depth by depth and when a floor is putted in it means that a floor is dequeue
    t_localisation newLoc;
    printf("Root initialized.  ");
    int idx = 0;
    for(int i = 0; i<nbDrawnMove; i++) {
        newLoc = updateLocalisationMap(list_of_move[i], locaMarc, map);
        printf(" x,y : %d,%d", getX(newLoc), getY(newLoc));
        if (isValidLocalisation(newLoc.pos,map.x_max,map.y_max)){
            root->sons[idx] = createNode(map.costs[getX(newLoc)][getY(newLoc)], nbDrawnMove - 1, 1, root, newLoc, list_of_move[i]);
            enqueueNode(&q, *(root->sons[idx]));
            idx++;
        }else{
            printf("Invalid pos or Crevasse.");
            root->nbSons--;
        }
    }
    printf("\nSons of root added.\n");

    int layer = 0;
    t_node node;
    while (!isNodeQueueEmpty(q)){
        node = dequeueNode(&q);
        if(node.depth!=layer){
            layer = node.depth;
            printf("\nFrom layer %d :", layer);
        }
        printf("\n\tAdding sons : ");
        if(node.depth!=nbMove && node.value != 0){ //there won't have crevasses in the queue because we don't even create them
            int find = 0;
            idx = 0;
            for(int i = 0; i<node.parent->nbSons; i++) {
                if(!find && node.parent->sons[i]->movement == node.movement) {
                    find == 1;
                }else{
                    printf("Son %d ", idx);
                    t_move itsmove = node.parent->sons[i]->movement;
                    newLoc = updateLocalisationMap(itsmove, node.localisation, map);
                    printf("coor (%d,%d) ", getX(newLoc),getY(newLoc));
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
            printf("Sons not created: the node is at the base or at the leaves level");
            node.nbSons = 0;
        }
    }
    printf("\nTree successfully generated.\n");
    return root;
}

t_node minLeaf(t_node node){
    if(node.nbSons == 0){
        return node;
    }
    t_node minSons[node.nbSons];
    for(int i=0; i<node.nbSons;i++){
        minSons[i]= minLeaf(*(node.sons[i]));
    }
    // find the smallest node in the list of leaf
    t_node minNode = minSons[0];
    for(int i=1; i<node.nbSons; i++){
        if(minSons[i].value < minNode.value){
            minNode = minSons[i];
        }else{
            if(minSons[i].value == minNode.value && minSons[i].depth < minNode.depth){
                minNode = minSons[i];
            }
        }
    }
    return minNode;
}

t_node* wayToLeafFromLeaf(t_node leaf){
    t_node* tab = (t_node*) malloc((leaf.depth +1)*sizeof(t_node));
    for(int i =leaf.depth; i>=0 ; i--){
        tab[i]=leaf;
        leaf = *(leaf.parent);
    }
    return tab;
}



