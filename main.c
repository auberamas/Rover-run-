#include <stdio.h>
#include "map.h"
#include "moves.h"
#include "tree.h"

int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);
    printf("\n\n\n");

    int nbDrawnedmoves = 9;
    int nbOfMoves = 6;
    t_move* moves = drawNbMoves(nbDrawnedmoves);
    for(int i=0; i<nbDrawnedmoves; i++){
        printf("move %d : %s   ", i, getMoveAsString(moves[i]));
    }

    t_orientation ori = SOUTH;
    t_localisation loca = loc_init(5,6,ori);//x,y

    t_node* root = createTree(moves, nbDrawnedmoves, nbOfMoves, map, loca);

    t_node* bestLeaf = minLeaf(root);
    int x= getX(bestLeaf->localisation), y =getY(bestLeaf->localisation);
    printf("\t soil: %d cost: %d coor: (%d,%d) %s\n", getSoil(map, x, y), map.costs[y][x],x,y,getMoveAsString(bestLeaf->movement));
    t_node** path = wayToLeafFromLeaf(bestLeaf);
    for(int i=0;i<bestLeaf->depth+1;i++)printf(" move %d: %s\n",i, getMoveAsString(path[i]->movement));
    printf("value : %d", path[bestLeaf->depth]->value);



    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);
    printf("\n\n\n");

    /**
    int x= getX(root->localisation), y =getY(root->localisation);
    printf("Root: soil: %d cost: %d coor: (%d,%d)\n", getSoil(map, x, y), map.costs[y][x],x,y);
    printf("First layer :\n ");
    for(int i =0;i<root->nbSons;i++){
        x= getX(root->sons[i]->localisation), y =getY(root->sons[i]->localisation);
        printf("\t soil: %d cost: %d coor: (%d,%d) %s\n", getSoil(map, x, y), map.costs[y][x],x,y,getMoveAsString(root->sons[i]->movement));
    }
    printf("Second layer from son 1:\n ");
    for(int i =0; i < root->sons[0]->nbSons; i++){
        x= getX(root->sons[1]->sons[i]->localisation), y =getY(root->sons[1]->sons[i]->localisation);
        printf("\t soil: %d cost: %d coor: (%d,%d) move : %s \n", getSoil(map, x, y), map.costs[y][x],x,y, getMoveAsString(root->sons[1]->sons[i]->movement));
    }
    **/
    return 0;
}
