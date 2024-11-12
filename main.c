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

    int nbmoves = 5;
    t_move* moves = drawNbMoves(nbmoves);
    for(int i=0; i<nbmoves; i++){
        printf("move %d : %s   ", i, getMoveAsString(moves[i]));
    }

    t_orientation ori = NORTH;
    t_localisation loca = loc_init(3,3,ori);

    t_node* root = createTree(moves, nbmoves, 2, map, loca);


    int x= getX(root->localisation), y =getY(root->localisation);
    printf("Root: soil: %d cost: %d coor: (%d,%d)\n", getSoil(map, x, y), map.costs[x][y],x,y);
    printf("First layer :\n ");
    for(int i =0;i<5;i++){
        x= getX(root->sons[i]->localisation), y =getY(root->sons[i]->localisation);
        printf("\t soil: %d cost: %d coor: (%d,%d) %s\n", getSoil(map, x, y), map.costs[x][y],x,y,getMoveAsString(root->sons[i]->movement));
    }
    printf("Second layer from son 1:\n ");
    for(int i =0;i<4;i++){
        x= getX(root->sons[1]->sons[i]->localisation), y =getY(root->sons[1]->sons[i]->localisation);
        printf("\t soil: %d cost: %d coor: (%d,%d) move : %s \n", getSoil(map, x, y), map.costs[x][y],x,y, getMoveAsString(root->sons[1]->sons[i]->movement));
    }
    return 0;
}
