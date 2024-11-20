//
// Created by pierr on 11/19/2024.
//

#ifndef UNTITLED1_MENU_H
#define UNTITLED1_MENU_H

#include "\modified\map.h"
#include "\modified\loc.h"

static char* Maps[] = {"..\\maps\\exemple1.map", "..\\maps\\training_2.map", "..\\maps\\training_3.map", "..\\maps\\training_4.map", "..\\maps\\training_5.map"};
int mission();
void messageEnd(int);
int userInput(int, int);
t_map chooseMap();
t_localisation chooseLocalisation();
t_orientation chooseOrientation();
void wantShowMap();
void wantShowComplexity();

#endif //UNTITLED1_MENU_H
