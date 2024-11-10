//
// Created by pierr on 11/9/2024.
//

#include "node.h"
#include <stdio.h>

t_node* createNode(int value, int nb_sons, int depth, t_node* parent, t_localisation localisation, t_move movement){
    t_node *new_node;
    new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = value;
    new_node->nbSons = nb_sons;
    new_node->sons = (t_node **)malloc(nb_sons*sizeof(t_node *));

    if(new_node->sons == NULL) printf("fail");
    else printf("created. ");

    for (int i=0; i <nb_sons; i++)
    {
        new_node->sons[i]=NULL;
    }
    new_node->depth = depth;
    new_node->parent = parent;
    new_node->localisation = localisation;
    new_node->movement = movement;
    return new_node;
}