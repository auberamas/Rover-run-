//
// Created by pierr on 10/21/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "node.h"
#include "../modified/map.h"

#define DEBUG 0



/**
 * @brief generate the tree
 * @param list_of_move the list of drawed moves
 * @param nbDrawMove the number of drawed moves breadth of the first stage
 * @param nbMove number of move to do (depth)
 * @param map the map
 * @param locaMarc is the localisation of Marc
 * @return the root of the tree
 */
t_node *createTree(t_move* list_of_move, int nbDrawMove, int nbMove, t_map map, t_localisation locaMarc);

/**
 * @brief find the smallest leaf in the tree
 * @param node
 * @return the smallest leaf of the tree
 */
t_node* minLeaf(t_node* node);

/**
 * @brief gives the list of node from the root to the leaf
 * @param leaf the leaf
 * @return a table of node wich is the way to the root
 */
t_node** wayToLeafFromLeaf(t_node* leaf);

t_move* aPhase(t_localisation loca, int nbDrawnMove, int nbOfMoves, t_map map, int *sizeMoves);

int phaseUntilBase(t_map map, t_localisation loc, int nbToDraw, int nbMoves, int showMap);

void freeTree(t_node* root);

#endif //UNTITLED1_TREE_H
