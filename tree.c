//
// Created by pierr on 10/21/2024.
//

#include "tree.h"
#include <stdlib.h>

t_node* createNode(int value, int nb_sons, int depth, t_node* parent){
    t_node *new_node;
    new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = value;
    new_node->nbSons = nb_sons;
    new_node->sons = (t_node **)malloc(nb_sons*sizeof(t_node *));
    for (int i=0; i <nb_sons; i++)
    {
        new_node->sons[i]=NULL;
    }
    new_node->depth = depth;
    new_node->parent = parent;
    return new_node;
}

t_node *createTree(t_move* list_of_move, int nbMove){
    t_node* root = createNode(-1,9,5,NULL);

}

