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
t_node *createTree(t_move* list_of_move, int nbDrawMove, int nbMove, t_map map, t_localisation locaMarc, double* timeCplx);

/**
 * @brief find the smallest leaf in the tree
 * @param node
 * @param timeCplx
 * @return the smallest leaf of the tree
 */
t_node* minLeaf(t_node* node, double* timeCplx);

/**
 * @brief gives the list of node from the root to the leaf
 * @param leaf the leaf
 * @param timeCplx
 * @return a table of node wich is the way to the root
 */
t_node** wayToLeafFromLeaf(t_node* leaf, double* timeCplx);

/**
 * @brief a full phase of MARC navigation
 * @param loca
 * @param nbDrawnMove
 * @param nbOfMoves
 * @param map
 * @param sizeMoves
 * @param timeCplx
 * @return
 */
t_move* aPhase(t_localisation loca, int nbDrawnMove, int nbOfMoves, t_map map, int *sizeMoves, double* timeCplx);

/**
 * @brief phases of Marc navigation until he reached the base
 * @param map
 * @param loc
 * @param nbToDraw
 * @param nbMoves
 * @param showMap
 * @param timeCplx
 * @return
 */
int phaseUntilBase(t_map map, t_localisation loc, int nbToDraw, int nbMoves, int showMap, double* timeCplx);

/**
 * @brief free the whole tree from the root
 * @param root
 */
void freeTree(t_node* root);

#endif //UNTITLED1_TREE_H
