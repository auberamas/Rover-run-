//
// Created by pierr on 11/19/2024.
//

#ifndef UNTITLED1_MENU_H
#define UNTITLED1_MENU_H

#include "modified\map.h"
#include "modified\loc.h"

static char* Maps[] = {"..\\maps\\expedition.map", "..\\maps\\intermediate.map", "..\\maps\\middle.map", "..\\maps\\tiny.map", "..\\maps\\wide.map"};
int isMission();
void messageEnd(int);
int userInput(int, int);
t_map chooseMap();
t_localisation chooseLocalisation();
t_orientation chooseOrientation();
void displayParameters(t_localisation, t_map);

_Noreturn void menu();

void wantShowMap();
void wantShowComplexity();


#endif //UNTITLED1_MENU_H
