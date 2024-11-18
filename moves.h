//
// Created by flasque on 19/10/2024.
//

#ifndef UNTITLED1_MOVES_H
#define UNTITLED1_MOVES_H

#include "loc.h"
#include "map.h"

#define DEBUG 0

/**
 * @brief Array of strings for the possible moves of the robot
 */
static char _moves[8][8] = {"F 10m", "F 20m", "F 30m", "B 10m", "T left", "T right", "U-turn", "Root"};

/**
 *  @brief Array of the sum of probabilities to draw each moves
 */
static int init_probabilities[] = {22, 37, 44, 51, 72, 93, 100};//original probas
static int probabilities[] = {22, 37, 44, 51, 72, 93, 100};//proba which will be modify

/**
 * @brief Enum for the possible moves of the robot
 */

typedef enum e_move
{
    F_10, // Forward 10 m
    F_20, // Forward 20 m
    F_30, // Forward 30 m
    B_10, // Backward 10 m
    T_LEFT, // Turn left (+90°)
    T_RIGHT, // Turn right (-90°)
    U_TURN,
    ROOT
} t_move;

/**
 * @brief function to get a t_move as a string
 * @param move : the move to convert
 * @return the string corresponding to the move
 */
char *getMoveAsString(t_move move);

/**
 * @brief function to update the localisation of the robot according to a move
 * @param loc : the localisation of the robot
 * @param move : the move to do
 * @return the new localisation of the robot
 */
t_localisation move(t_localisation, t_move);

/**
 * @brief wrapper function to update a single location
 * @param p_loc : the pointer to the localisation of the robot
 * @param move : the move to do
 * @return none
 */
void updateLocalisation(t_localisation *, t_move);



/**
 *@brief draw a move
 * @return a movement
 **/
t_move drawMove();

/**
 * @brief draw nine movement
 * @return an array of nine movements
 */
 t_move* drawNbMoves(int);

void resetProba();

 /**
  * @brief update the localisation with respect to the map and the current localisation
  * @param move the movement to be done
  * @param localisation the actual localisation (position+orientation)
  * @param map the map
  * @return the updated localisation
  */
 t_localisation updateLocalisationMap(t_move move, t_localisation localisation, t_map map);


/**
 * @brief ckeck throughout the move if we pass by a crevasse
 * @param move the movement to be done
 * @param localisation the actual localisation (position+orientation)
 * @param map the map
 * @return 0 if the localisation is leads to a crevasse and 1 else
 */
 int checkMove(t_move move, t_localisation localisation, t_map map);

 /**
  * @brief create an invalid Loc
  * @return a position whith pos at -1 -1
  */
 t_localisation doInvalidLoc();

int updateAnimPhase(t_map map, t_move* moves, int size,t_localisation* loc);

int updatePhase(t_map map, t_move* moves, int size,t_localisation* loc);


#endif //UNTITLED1_MOVES_H
