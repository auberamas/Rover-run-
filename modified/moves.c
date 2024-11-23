//
// Created by flasque on 19/10/2024.
//

#include "moves.h"
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <time.h>

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
            rst = 0;
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
    t_localisation new_loc=loc;
    if ((move >=T_LEFT) && (move <= U_TURN))
    {
        new_loc.ori = rotate(loc.ori, move);
    }
    else
    {
        if(move==ROOT)new_loc=loc;
        else new_loc = translate(loc, move);
    }

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

void resetProba(){
    for (int i = 0; i < 7; i++) {
        probabilities[i]=init_probabilities[i];
    }
    return;
}

t_localisation doInvalidLoc(){
    t_localisation new_loc;
    if(DEBUG)printf("crevasse on the way");
    new_loc.ori = NORTH;
    new_loc.pos.x=-1;
    new_loc.pos.y=-1;
    return new_loc;
}

int checkMove(t_move move,t_localisation loc, t_map map){
    int validLoc = 1;
    int steps = 1;
    t_localisation new_loc = loc;
    t_move new_move= F_10;
    switch (move) {
        case F_30:
            steps = 3;
            break;
        case F_20:
            steps = 2;
            break;
        case B_10:
            new_move = B_10;
            break;
        default:
            break;
    }

    for(int i = 0; i<steps; i++){
        updateLocalisation(&new_loc,new_move);
        if(!isValidLocalisation(new_loc.pos, map.x_max, map.y_max) || getSoil(map, getX(new_loc), getY(new_loc)) == CREVASSE){
            validLoc = 0;
            return validLoc;
        }
    }
    return validLoc;
}

t_localisation updateLocalisationMap(t_move movement, t_localisation localisation, t_map map){
    if(DEBUG)printf(" move %s ", getMoveAsString(movement));
    switch (getSoil(map, getX(localisation), getY(localisation))) {
        case BASE_STATION:
            if(DEBUG)printf("base");
            break;
        case PLAIN:
            if(DEBUG)printf("plain");
            break;
        case REG:
            if(DEBUG)printf("reg");
            break; // Need to find a way to do less move in the next phase
        case CREVASSE:
            return doInvalidLoc(); // Shouldn't append, if we arrived in a crevasse (because we don't enqueue them)
        case ERG:
            if(DEBUG)printf("erg");
            switch (movement) {
                case F_10:
                    movement = ROOT; //root will do nothing in the fct move(
                    break;
                case B_10:
                    movement = ROOT;
                    break;
                case T_LEFT:
                    movement = ROOT;
                    break;
                case T_RIGHT:
                    movement = ROOT;
                    break;
                case F_20:
                    movement = F_10;
                    break;
                case F_30 :
                    movement = F_20;
                    break;
                case U_TURN:
                    srand(time(0));
                    int rand_turn = rand()%2;
                    if(rand_turn)
                        movement = T_RIGHT;
                    else
                        movement = T_LEFT;
                    break;
            }
            break;
    }

    if(movement == F_10 || movement == F_20 || movement == F_30 || movement == B_10){
        if (checkMove(movement, localisation, map)==0){
            if(DEBUG)printf(" found a crevasse on my way");
            return doInvalidLoc();
        }
    }
    t_localisation new_loc = move(localisation, movement);
    return new_loc;
}

void displayLine(t_map map){
    for(int i =0; i<map.x_max; i++){
        printf("===");
    }
    printf("\n");
}


int updateAnimPhase(t_map map, t_move* moves, int size,t_localisation* loc){
    int foundReg = 0;
    //printf("Initial position: %s\n", getMoveAsString(moves[0]));
    printf("\n");
    displayMapWithMARC(map, *loc);
    displayLine(map);
    for (int i = 1; i < size; ++i) {
        updateLocalisation(loc, moves[i]);
        if(getSoil(map, getX(*loc), getY(*loc))==REG)foundReg=1;
        sleep(1);
        //printf("Move number %d: %s\n", i, getMoveAsString(moves[i]));
        displayMapWithMARC(map, *loc);
        displayLine(map);
    }
    return foundReg;
}

int updatePhase(t_map map, t_move* moves, int size,t_localisation* loc){
    int foundReg = 0;
    for (int i = 1; i < size; i++) {
        updateLocalisation(loc, moves[i]);
        if(getSoil(map, getX(*loc), getY(*loc))==REG)foundReg=1;
    }
    return foundReg;
}
