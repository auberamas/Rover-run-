#include <stdio.h>
#include "modified\map.h"
#include "created\tree.h"
#include "menu.h"

int main() {

    // a supprimer *************************************
    /*
    t_map map = createMapFromFile("..\\maps\\training_5.map");
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
    */

    menu();
    // *************************************************************

    /*
    int nbDrawnedmoves = 9;
    int nbOfMoves = 5;

    t_orientation ori = EAST;
    t_localisation loca = loc_init(3,3,ori);//x,y

    int nbPhase = phaseUntilBase(map, loca, nbDrawnedmoves, nbOfMoves,1);
    printf("Base found in %d phases",nbPhase);
    */
    return 0;
}
