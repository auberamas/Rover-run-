//
// Created by pierr on 11/9/2024.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H

#include "moves.h"
#include <stdlib.h>

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


#endif //UNTITLED1_NODE_H
