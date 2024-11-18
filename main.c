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
    int nbOfMoves = 5;
    t_orientation ori = NORTH;
    t_localisation loca = loc_init(5,6,ori);//x,y

    displayMapWithMARC(map,loca);

    int sizeMoves = 0;
    t_move* path = aPhase(loca,nbDrawnedmoves,nbOfMoves,map,&sizeMoves);
    for(int i=0;i<sizeMoves;i++)printf(" move %d: %s\n",i, getMoveAsString(path[i]));

    updateAnimPhase(map, path, sizeMoves, &loca);

    printf("(%d,%d)", getX(loca), getY(loca));

    return 0;
}
