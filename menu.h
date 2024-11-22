//
// Created by pierr on 11/19/2024.
//

#ifndef UNTITLED1_MENU_H
#define UNTITLED1_MENU_H

#include "modified\map.h"
#include "modified\loc.h"

//save all map names
static char* Maps[] = {"..\\maps\\expedition.map", "..\\maps\\intermediate.map", "..\\maps\\middle.map", "..\\maps\\tiny.map", "..\\maps\\wide.map"};
/**
 * Ask the user if he wants to start a mission
 * @return 1 if mission, 0 else
 */
int isMission(int);

/**
 * indicates if you reached the base (and the number of phase) or not
 */
void messageEnd(int);

/**
 * @brief secure input, the user can choose between a range of integer
 * @param1 lower boundary
 * @param2 upper boundary
 * @return the user input
 */
int userInput(int, int);

/**
 * @brief the user can choose a map
 * @return the chosen map
 */
t_map chooseMap();

/**
 * @brief the user can choose (a valid) localisation on the map
 * @param1 maximum x of the map
 * @param2 maximum y of the map
 * @return the chosen localisation
 */
t_localisation chooseLocalisation(int, int);

/**
 * @brief display the parameters of MARC at the beginning
 */
void displayParameters(t_localisation, t_map);

/**
 * allow the user to choose between 4 scenarios
 */
void menu();

/**
 * @brief display complexity and initialize complexity
 * @param1 array of double to save complexity values of the main functions : tree, min leaf, path, phases until base
 * @param2 integer that indicates if we want to display the complexity (1 to display)
 */
void manageComplexity(double*, int);


#endif //UNTITLED1_MENU_H
