//
// Created by pierr on 10/21/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "node.h"
#include "map.h"
#include "nodequeue.h"





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


#endif //UNTITLED1_TREE_H
