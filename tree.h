//
// Created by pierr on 10/21/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "moves.h"

/**
 * structure for a node
 */
typedef struct s_node
{
    int value;
    int depth;
    struct s_node **sons;
    int nbSons; // physical size of the array
    struct s_node *parent;
} t_node;


/**
 * @brief initialize a node
 * @param value the value to be stored in the node
 * @param nb_sons the number of sons: physical size of the array
 * @param depth int, depth of the node
 * @param parent node (t_node), parent of the node
 * @return
 */
t_node *createNode(int value, int nb_sons, int depth, t_node* parent);

/**
 * @brief generate the tree
 * @param list_of_move the list of 9 move to draw
 * @param nbMove number of move
 * @return the root of the tree
 */
t_node *createTree(t_move* list_of_move, int nbMove);


#endif //UNTITLED1_TREE_H
