//
// Created by flasque on 19/10/2024.
//

#ifndef UNTITLED1_MAP_H
#define UNTITLED1_MAP_H

#include "loc.h"

#define COST_UNDEF 65535
/**
 * @brief Enum for the possible soils of the map
 */
typedef enum e_soil
{
    BASE_STATION,
    PLAIN,
    ERG,
    REG,
    CREVASSE
} t_soil;

static int COMPLEXITY = 1;

/**
 * @brief Array of costs for the soils
 */
static const int _soil_cost[5] = {0, 1, 2, 4, 10000};

/**
 * @brief Structure for the map

 */
typedef struct s_map
{
    t_soil  **soils;
    int     **costs;
    int     x_max;
    int     y_max;
    char* name;
} t_map;

/**
 * @brief Function to initialise the map from a file
 * @param filename : the name of the file
 * @return the map
 */
t_map createMapFromFile(char *);

/**
 * @brief free the memory allocated for a map
 * @param map
 */
void freeMap(t_map map);

/**
 * @brief Function to create a standard training map (11x11 with only plains and base station in the middle)
 * @param none
 * @return a standard map
 */
 t_map createTrainingMap();

/**
 * @brief display the map with characters
 * @param map : the map to display
 */
void displayMap(t_map);

/**
 * @brief getter for the soil at a given x and y
 * @param map
 * @param x
 * @param y
 * @return
 */
t_soil getSoil(t_map map, int x, int y);

/**
 * @brief getter for the Cost at a given localisation
 * @param map
 * @param loc
 * @return the cost value on the map
 */
int getCost(t_map map, t_localisation loc);

/**
 * @copybrief I took some already done function by Sir Flasque and mixed them
 * @brief Display the map with M at the given position and It's orientation
 * @param map
 * @param loca_marc
 */
void displayMapWithMARC(t_map map, t_localisation loca_marc);

#endif //UNTITLED1_MAP_H
