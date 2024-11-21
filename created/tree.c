//
// Created by pierr on 10/21/2024.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

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
        for(int i=a; i>b; i--)
            mult *= i;
        return mult;
    }else{
        printf("Factorial division ERROR");
        return -1;
    }

}


t_node* createTree(t_move* list_of_move, int nbDrawnMove, int nbMove, t_map map, t_localisation locaMarc, double* timeCplx){ // need to add when crevasse and when outside the map
    clock_t timeFinal, timeStart;
    if(COMPLEXITY){
        timeStart = clock();
    }
    if(DEBUG)printf("\nStarting to create the tree.\n");

    // Initialisation of the root
    t_node* root = createNode(getCost(map, locaMarc),nbDrawnMove,0,NULL,locaMarc, ROOT);
    node_queue q = createNodeQueue(factorialDivision(nbDrawnMove,nbDrawnMove-nbMove-1)); // the maximum number of nodes in the queue will be the number of parents of leaves since we will process depth by depth and when a floor is putted in it means that a floor is dequeue
    if(DEBUG)printf("Root initialized.  ");

    for(int i = 0; i<nbDrawnMove; i++) {
        t_localisation newLoc = updateLocalisationMap(list_of_move[i], locaMarc, map);
        if(DEBUG)printf(" x,y : %d,%d", getX(newLoc), getY(newLoc));
        if (isValidLocalisation(newLoc.pos,map.x_max,map.y_max) && getCost(map, newLoc)!=0 && nbMove!=1){
            root->sons[i] = createNode(getCost(map, newLoc), nbDrawnMove - 1, 1, root, newLoc, list_of_move[i]);
            enqueueNode(&q, root->sons[i]);
        }else{
            if(DEBUG)printf("with No Son");
            if(isValidLocalisation(newLoc.pos,map.x_max,map.y_max)){
                if(DEBUG)printf("Base found or leaf.");
                root->sons[i] = createNode(0, 0, 1, root, newLoc, list_of_move[i]);
            }else {
                if(DEBUG)printf("Invalid pos or Crevasse.");
                root->sons[i] = createNode(10000, 0, 1, root, newLoc, list_of_move[i]);
            }
        }
    }
    if(DEBUG)printf("\nSons of root added.\n");

    // Making all sons
    int layer = 0;//for layers display
    t_node* node;
    int idx;
    while (!isNodeQueueEmpty(q)){
        node = dequeueNode(&q);

        if(DEBUG)if(node->depth!=layer){layer = node->depth;printf("\nFrom layer %d :", layer);}//just display layers
        if(DEBUG)printf("\n\tAdding sons (%d) for (%d,%d): ",node->parent->nbSons-1, getX(node->localisation), getY(node->localisation));

        idx = 0;
        int foundMyself = 0;
        for(int i = 0; i< node->parent->nbSons; i++) {
            if(!foundMyself && node->parent->sons[i]->movement == node->movement) {
                if(DEBUG)printf("\tSON %d found we I am really. ", i);
                foundMyself = 1;//to not create a son with the same move
            }else{
                if(DEBUG)printf("\tSON %d (%d in list)", i,idx);
                t_move itsMove = node->parent->sons[i]->movement;
                t_localisation newLoc = updateLocalisationMap(itsMove, node->localisation, map);// the localisation if the move is correct, (-1,-1) else
                if(DEBUG)printf(" coor (%d,%d) ", getX(newLoc),getY(newLoc));
                if (isValidLocalisation(newLoc.pos,map.x_max,map.y_max) && getCost(map, newLoc)!=0 && node->depth+1!=nbMove){
                    if(DEBUG)printf(" NotLeaf ");
                    node->sons[idx] = createNode(getCost(map, newLoc), node->nbSons -1, node->depth+1, node, newLoc, itsMove);
                    enqueueNode(&q,node->sons[idx]);
                } else{
                    if(isValidLocalisation(newLoc.pos,map.x_max,map.y_max)){
                        if(DEBUG){if(getCost(map, newLoc)==0)printf("\n\nBase found.\n\n");else printf("Arrived to a leaf.");}
                        node->sons[idx] = createNode(getCost(map, newLoc), 0, node->depth+1, node, newLoc, itsMove);
                    }else {
                        if(DEBUG)printf("Invalid pos or Crevasse.");
                        node->sons[idx] = createNode(10000, 0, node->depth+1, node, newLoc, itsMove);
                    }
                }
                idx++;
            }
        }
    }
    if(DEBUG)printf("Tree successfully generated.\n\n\n");
    free(q.nodes);
    if(COMPLEXITY){
        timeFinal = clock();
        timeCplx[0] = timeCplx[0] + ((double)(timeFinal-timeStart))/CLOCKS_PER_SEC;
    }
    return root;
}


t_node* minLeaf(t_node* node, double* timeCplx){
    clock_t timeFinal, timeStart;
    if(COMPLEXITY){
        timeStart = clock();
    }
    if(DEBUG)printf("Processing node with value: %d, nbSons: %d\n", node->value, node->nbSons);

    if(node->nbSons == 0){
        return node;
    }
    t_node** minSons = malloc(node->nbSons * sizeof(t_node*));
    for(int i=0; i<node->nbSons;i++){
        if(DEBUG){if(node->sons[i] == NULL) printf("mange tes morts");}
        minSons[i]= minLeaf(node->sons[i], timeCplx);
    }
    // find the smallest node in the list of leaf
    t_node* minNode = minSons[0];
    for(int i=1; i<node->nbSons; i++){
        if(minSons[i]->value < minNode->value || (minSons[i]->value == minNode->value && minSons[i]->depth < minNode->depth)){
            minNode = minSons[i];
        }
    }
    free(minSons);
    if(COMPLEXITY){
        timeFinal = clock();
        timeCplx[1] = timeCplx[1]+((double)(timeFinal-timeStart))/CLOCKS_PER_SEC;
    }
    return minNode;
}


t_node** wayToLeafFromLeaf(t_node* node, double* timeCplx){
    clock_t timeFinal, timeStart;
    if(COMPLEXITY){
        timeStart = clock();
    }
    t_node** tab = (t_node**) malloc((node->depth +1)*sizeof(t_node*));
    for(int i =node->depth; i>=0 ; i--){
        if(DEBUG)printf("%d, %d, %d\n",i,node->depth,node->value);
        tab[i]=node;
        if(node->depth!=0) {node = node->parent;}
    }
    if(COMPLEXITY){
        timeFinal = clock();
        printf("************** %f **************** ", (double)(timeFinal-timeStart)/CLOCKS_PER_SEC);
        timeCplx[2]= timeCplx[2]+((double)(timeFinal-timeStart))/CLOCKS_PER_SEC;
    }
    return tab;
}

t_move* aPhase(t_localisation loca, int nbDrawnMoves, int nbOfMoves, t_map map, int* sizeMoves, double *timeCplx){
    resetProba();
    t_move* moves = drawNbMoves(nbDrawnMoves);
    printf("Drawn moves :\n");
    for(int i=0; i < nbDrawnMoves; i++){
        printf("move %d: %s, ", i, getMoveAsString(moves[i]));
    }
    printf("\n");
    t_node* root = createTree(moves, nbDrawnMoves, nbOfMoves, map, loca, timeCplx);

    t_node* bestLeaf = minLeaf(root, timeCplx);

    if(DEBUG){int x= getX(bestLeaf->localisation), y =getY(bestLeaf->localisation);printf("\t soil: %d cost: %d coor: (%d,%d) %s\n", getSoil(map, x, y), map.costs[y][x],x,y,getMoveAsString(bestLeaf->movement));}
    t_node** path = wayToLeafFromLeaf(bestLeaf, timeCplx);

    if(DEBUG)for(int i=0;i<bestLeaf->depth+1;i++)printf(" move %d: %s\n",i, getMoveAsString(path[i]->movement));
    if(DEBUG)printf("value : %d", path[bestLeaf->depth]->value);

    *sizeMoves = bestLeaf->depth+1;
    t_move* lMoves = malloc(*sizeMoves * sizeof(t_move));
    for(int i=0; i<*sizeMoves;i++)lMoves[i]=path[i]->movement;
    //HERE SHOULD FREE THE TREE
    freeTree(root);
    //HERE SHOULD FREE PATH
    free(path);
    return lMoves;
}

int phaseUntilBase(t_map map, t_localisation loc, int nbToDraw, int nbMoves,int showMap, double* timeCplx){
    int baseFound = 0, regMalus=0, nbMovesPhase,nbPhase = 0;
    while (!baseFound && nbPhase<=100){
        printf("--------------------------------\n\tPHASE NUMBER %d\n--------------------------------\n",nbPhase+1);
        if(!regMalus)nbMovesPhase = nbMoves;
        else nbMovesPhase = nbMoves-1;

        int pathSize;
        t_move* path = aPhase(loc, nbToDraw, nbMovesPhase, map,&pathSize, timeCplx);

        if(showMap)regMalus = updateAnimPhase(map, path, pathSize, &loc);
        else regMalus = updatePhase(map, path, pathSize, &loc);

        if(getCost(map,loc) == 0)baseFound=1;
        printf("\nPhase Ended at (%d,%d)\n", getX(loc), getY(loc));
        nbPhase++;
        if(showMap)sleep(2);
        free(path);
    }
    if(nbPhase ==100)return -1;
    return nbPhase;
}

void freeTree(t_node* node){
    // If I'm a root I free myself and return
    // recursively freeTree each sons
    // free myself
    for(int i = 0; i<node->nbSons; i++){
        freeTree(node->sons[i]);
    }
    free(node->sons);
    free(node);
}
