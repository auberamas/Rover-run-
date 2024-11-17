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
    t_node* root = createNode(getCost(map, locaMarc),nbDrawnMove,0,NULL,locaMarc, ROOT);
    node_queue q = createNodeQueue(factorialDivision(nbDrawnMove,nbDrawnMove-nbMove)); // the maximum number of nodes in the queue will be the number of parents of leaves since we will process depth by depth and when a floor is putted in it means that a floor is dequeue
    t_localisation newLoc;
    printf("Root initialized.  ");
    for(int i = 0; i<nbDrawnMove; i++) {
        newLoc = updateLocalisationMap(list_of_move[i], locaMarc, map);
        printf(" x,y : %d,%d", getX(newLoc), getY(newLoc));
        if (isValidLocalisation(newLoc.pos,map.x_max,map.y_max) && getCost(map, newLoc)!=0 && nbMove!=1){
            root->sons[i] = createNode(getCost(map, newLoc), nbDrawnMove - 1, 1, root, newLoc, list_of_move[i]);
            enqueueNode(&q, *(root->sons[i]));
        }else{
            printf("with No Son");
            if(isValidLocalisation(newLoc.pos,map.x_max,map.y_max)){
                printf("Base found or leaf.");
                root->sons[i] = createNode(0, 0, 1, root, newLoc, list_of_move[i]);
            }else {
                printf("Invalid pos or Crevasse.");
                root->sons[i] = createNode(10000, 0, 1, root, newLoc, list_of_move[i]);
            }
        }
    }
    printf("\nSons of root added.\n");
    // Making all sons
    int layer = 0;//for layers display
    t_node node;
    while (!isNodeQueueEmpty(q)){
        node = dequeueNode(&q);

        if(node.depth!=layer){layer = node.depth;printf("\nFrom layer %d :", layer);}//just display layers
        printf("\n\tAdding sons (%d): ",node.parent->nbSons-1);

        int foundMyself = 0;
        for(int i = 0; i<node.parent->nbSons; i++) {
            if(!foundMyself && node.parent->sons[i]->movement == node.movement) {
                printf("\tSON %d found we I am really. ", i);
                foundMyself == 1;//to not create a son with the same move
            }else{
                printf("\tSON %d ", i);
                t_move itsMove = node.parent->sons[i]->movement;
                newLoc = updateLocalisationMap(itsMove, node.localisation, map);// the localisation if the move is correct, (-1,-1) else
                printf(" coor (%d,%d) ", getX(newLoc),getY(newLoc));
                if (isValidLocalisation(newLoc.pos,map.x_max,map.y_max) && getCost(map, newLoc)!=0 && node.depth+1!=nbMove){
                    printf(" NotLeaf ");
                    node.sons[i] = createNode(getCost(map, newLoc), node.nbSons -1, node.depth+1, &node, newLoc, itsMove);
                    enqueueNode(&q,*(node.sons[i]));
                } else{
                    if(isValidLocalisation(newLoc.pos,map.x_max,map.y_max)){
                        printf("Base found or leaf.");
                        node.sons[i] = createNode(getCost(map, newLoc), 0, node.depth+1, &node, newLoc, itsMove);
                    }else {
                        printf("Invalid pos or Crevasse.");
                        node.sons[i] = createNode(10000, 0, node.depth+1, &node, newLoc, itsMove);
                    }
                }
            }
        }
    }
    printf("\n\nTree successfully generated.\n\n\n");
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



