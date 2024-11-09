//
// Created by pierr on 10/21/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "moves.h"
#include "map.h"

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
