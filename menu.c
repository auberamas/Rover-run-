//
// Created by pierr on 11/19/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "modified/map.h"
#include "created/tree.h"

#define NBMAP 5


int userInput(int first, int last){
    int type, choice = 0;
    do{
        printf("\nChoose a value between %d and %d:",first, last);
        type = scanf("%d",&choice);
        if (type != 1 || choice < first || choice > last) {
            printf("Invalid input.");
            while (getchar() != '\n');
        }
    }while (type!=1||(choice < first) || (choice > last));
    return choice;
}

void messageEnd(int res){
    if (res != -1){
        printf("Base found in %d phases", res);
    }
    else{
        printf("I'm lost [>.<] \n");
    }
}

int mission(){
    int mission;
    printf("Do you want to start a mission ? Enter 1 for YES or 0 for NO : \n");
    scanf("%d",&mission);
    return mission;
}

t_map chooseMap(){
    printf(" ajouter des phrases");// a modifier
    int choice;
    do{
        printf("Choose a map in the list:");
        scanf("%d",&choice);
        if (choice >NBMAP || choice <= 0){
            printf("Your choice is not in the list!\n");
        }
    }while(choice >NBMAP || choice <= 0);
    t_map map = createMapFromFile(Maps[choice]);
    return map;
}

t_localisation chooseLocalisation(){
    t_localisation chosenLoc;
    // choice of orientation
    char *orientations[] = {"NORTH", "EAST", "SOUTH", "WEST"};
    printf("In which direction do you want MARC to start ? Choose from :\n");
    for(int i =1; i<5; i++){
        printf("%d - %s", i, orientations[i]);
    }
    chosenLoc.ori = userInput(1,5) -1;

    // choice of position


    return chosenLoc;
}

void menu(){
    int nbDrawnedmoves = 9;
    int nbOfMoves = 5;
    do{
        // proposition de scenario
        printf("Which scenario do you want to chose? (Enter your number of choice)  \n 1. Pre-defined scenario 1 \n 2. Pre-defined scenario 2 \n 3. Pre-defined scenario 3 \n 4. User-defined scenario");
        int scenario = userInput(1,5);

        switch(scenario){
            // hard filled
            case 0:{
                // ajouter une fonction qui donne les parametres de departs et ceux d'arrivée
                t_map map = createMapFromFile(Maps[4]);
                t_orientation ori = EAST;
                t_localisation loca = loc_init(3,3,ori);//x,y
                int nbPhase = phaseUntilBase(map, loca, nbDrawnedmoves, nbOfMoves,1);
                messageEnd(nbPhase);
            }

            case 1:{
                t_map map = createMapFromFile(Maps[1]);
                t_orientation ori = NORTH;
                t_localisation loca = loc_init(2,26, ori); //x,y
                int nbPhase = phaseUntilBase(map, loca, nbDrawnedmoves, nbOfMoves,0);
                messageEnd(nbPhase);
            }
            case 2:{
                t_map map = createMapFromFile(Maps[0]);
                t_orientation ori = SOUTH;
                t_localisation loca = loc_init(3,7, ori); //x,y
                int nbPhase = phaseUntilBase(map, loca, nbDrawnedmoves, nbOfMoves,0);
                messageEnd(nbPhase);

            }
            case 3:{
                t_map map = chooseMap();
                t_orientation  ori =


            }
        }
    }while(mission);
}



