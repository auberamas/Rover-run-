//
// Created by flasque on 19/10/2024.
//

#include "moves.h"
#include <stdlib.h>

/* prototypes of local functions */
/* local functions are used only in this file, as helper functions */

/**
 * @brief Function to rotate the robot according to a move and its actual orientation
 * @param ori : the actual orientation of the robot
 * @param move : the move to do
 * @return the new orientation of the robot
 */
t_orientation rotate(t_orientation, t_move );

/**
 * @brief function to translate the robot according to a move and its actual position
 * @param loc : the actual localisation of the robot
 * @param move : the move to do
 * @return the new localisation of the robot
 */
t_localisation translate(t_localisation , t_move);

/* definition of local functions */

t_orientation rotate(t_orientation ori, t_move move)
{
    int rst;
    switch (move)
    {
        case T_LEFT:
            rst=3;
            break;
        case T_RIGHT:
            rst=1;
            break;
        case U_TURN:
            rst=2;
            break;
        default:
            break;
    }
    return (ori+rst)%4;
}

t_localisation translate(t_localisation loc, t_move move)
{
    /** rules for coordinates:
     *  - x grows to the right with step of +1
     *  - y grows to the bottom with step of +1
     *  - the origin (x=0, y=0) is at the top left corner
     */
    t_position res = loc.pos;
    switch (move) {
        case F_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 1;
                    break;
                case EAST:
                    res.x = loc.pos.x + 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 1;
                    break;
                case WEST:
                    res.x = loc.pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 2;
                    break;
                case EAST:
                    res.x = loc.pos.x + 2;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 2;
                    break;
                case WEST:
                    res.x = loc.pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        case F_30:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 3;
                    break;
                case EAST:
                    res.x = loc.pos.x + 3;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 3;
                    break;
                case WEST:
                    res.x = loc.pos.x - 3;
                    break;
                default:
                    break;
            }
            break;
        case B_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y + 1;
                    break;
                case EAST:
                    res.x = loc.pos.x - 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y - 1;
                    break;
                case WEST:
                    res.x = loc.pos.x + 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
        return loc_init(res.x, res.y, loc.ori);

}

/* definitions of exported functions */

char *getMoveAsString(t_move move)
{
    return _moves[move];
}

t_localisation move(t_localisation loc, t_move move)
{
    t_localisation new_loc;
    new_loc.ori = rotate(loc.ori, move);
    new_loc = translate(loc, move);
    return new_loc;
}

void updateLocalisation(t_localisation *p_loc, t_move m)
{
    *p_loc = move(*p_loc, m);
    return;
}

t_move drawMove(){
    int rand_move = rand()%100+1;
    int move =0;
    // finding the drawn value
    while(rand_move > probabilities[move]){
        move++;
    }
    int temp = move;
    // updating the probabilities table
    while(temp<7) {
        probabilities[temp] = probabilities[temp] - 1;
        temp ++;
    }
    return move;
}


t_move* drawNbMoves(int nb){
    t_move* SetOfMove = malloc(nb * sizeof(t_move));
    for(int i = 0; i<nb; i++){
        SetOfMove[i]=drawMove();
    }
    return SetOfMove;
}

t_localisation updateLocalisationMap(t_move movement, t_localisation localisation, t_map map){
    int rand_turn = rand()%2;
    t_localisation new_loc;
    switch (getSoil(map, getX(localisation), getY(localisation))) {
        case PLAIN:
            break;
        case REG:
            break; // Need to find a way to do less move in the next phase
        case CREVASSE:
            new_loc.ori = NORTH;
            new_loc.pos.x=-1;
            new_loc.pos.y=-1;
            return new_loc;
        case ERG :
            switch (movement) {
                case F_10:
                    break;
                case B_10:
                    break;
                case T_LEFT:
                    break;
                case T_RIGHT:
                    break;
                case F_20:
                    movement = F_10;
                    break;
                case F_30 :
                    movement = F_20;
                    break;
                case U_TURN:
                    if(rand_turn)
                        movement = T_RIGHT;
                    else
                        movement = T_LEFT;
                    break;
            }
            break;
    }
    return move(localisation, movement);
}
