//
// Created by pierr on 11/19/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "created\tree.h"

#define NBMAP 5


int userInput(int first, int last ){
    int type, choice = 0;
    do{
        printf("\n\nChoose a value between %d and %d:\t",first, last);
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
        printf("Base found in %d phases.\n\n", res);
    }
    else{
        printf("I'm lost [>.<] ! \n\n");
    }
}

int mission(){
    int mission;
    printf("Do you want to start a mission ? Enter 1 for YES or 0 for NO : \n");
    scanf("%d",&mission);
    return mission;
}

t_map chooseMap(){
    char* allMaps[]= {"expedition", "intermediate", "middle", "tiny","wide"};
    printf("Choose a map among the following ones :");
    for(int i=0; i<NBMAP; i++){
        printf("%d - %s \n",i,allMaps[i]);
    }
    int choice;
    do{
        printf("To choose a map enter its number :");
        scanf("%d",&choice);
        if (choice >NBMAP || choice <= 0){
            printf("Your choice is not in the list!\n");
        }
    }while(choice >NBMAP || choice <= 0);
    t_map map = createMapFromFile(Maps[choice]);
    return map;
}

t_localisation chooseLocalisation(int x_max, int y_max){
    t_localisation chosenLoc;

    // choice of orientation
    printf("In which direction do you want MARC to start ? Choose from :\n");
    for(int i =0; i<4; i++){
        printf("%d - %s\n", i+1, orientations[i]);
    }
    chosenLoc.ori = userInput(1,4) -1;

    // choice of position
    printf("Choose your beginning localisation :\n");
    printf("Choose your x coordinate : ");
    chosenLoc.pos.x = userInput(0,x_max);
    printf("Choose your y coordinate : ");
    chosenLoc.pos.y = userInput(0,y_max);

    return chosenLoc;
}

void displayParameters(t_localisation loc, t_map map){
    printf("________________________________\n");
    printf("MARC beginning parameters :\n");
    printf("Position : (%d,%d) \nOrientation : %s\n", loc.pos.x, loc.pos.y, orientations[loc.ori]);
    printf("Map name : map x\n");
    printf("________________________________\n");
}

void initialiseCplx(){
    timeCplxTree = 0;
    timeCplxMinLeaf = 0;
    timeCplxPath = 0;
    timeCplxExample = 0;
}

void menu(){
    int nbDrawndmoves = 9;
    int nbOfMoves = 5;
    do{
        // proposition de scenario
        printf("Which scenario do you want to chose? (Enter your number of choice)");
        printf("\n 1. Pre-defined scenario 1 : great crossing ");
        printf("\n 2. Pre-defined scenario 2 : quick return to base ");
        printf("\n 3. Pre-defined scenario 3 : few miles away" );
        printf("\n 4. User-defined scenario : let's define your scenario");
        int scenario = userInput(1,4);

        switch(scenario){
            // hard filled
            case 1:{
                printf("** Scenario 1 **\nMarc is far away from the base, he needs to achieve a huge way to go back to it. \nLet's see how he manages the path thanks to an animated map.\n");
                t_map map = createMapFromFile(Maps[4]);
                t_orientation ori = EAST;
                t_localisation loca = loc_init(3,3,ori);
                displayParameters(loca, map);
                printf("\nLet's start the way to go to the base ! \n");
                int nbPhase = phaseUntilBase(map, loca, nbDrawndmoves, nbOfMoves,1);
                messageEnd(nbPhase);
                break;
            }

            case 2:{
                printf("** Scenario 2 **\n\nIn this scenario Marc is not far away from the base, he needs few phases to get back to it.\nHere details about Marc's movement and the complexity time will be displayed.\n");
                t_map map = createMapFromFile(Maps[1]);
                t_orientation ori = NORTH;
                t_localisation loca = loc_init(2,26, ori);
                COMPLEXITY = 0;
                displayParameters(loca, map);
                printf("\nLet's start the way to go to the base !\n");
                int nbPhase = phaseUntilBase(map, loca, nbDrawndmoves, nbOfMoves,0);
                messageEnd(nbPhase);
                break;
            }
            case 3:{
                printf("** Scenario 3 **\n\nIn this scenario Marc is not far away from the base, he needs few phases to get back to it.\nThe map will be displayed to follow it's progress.\n");
                t_map map = createMapFromFile(Maps[0]);
                t_orientation ori = SOUTH;
                t_localisation loca = loc_init(4,6, ori);
                displayParameters(loca, map);
                printf("\nLet's start the way to go to the base\n");
                COMPLEXITY = 1;
                int nbPhase = phaseUntilBase(map, loca, nbDrawndmoves, nbOfMoves,1);
                messageEnd(nbPhase);
                printf("**** CPLX ****");
                printf("\nTree : %f\nMin leaf :%f\nPath: %f\n", timeCplxTree, timeCplxExample, timeCplxPath);
                initialiseCplx();
                break;

            }
            case 4:{
                t_map map = chooseMap();
                t_localisation loc = chooseLocalisation(map.y_max, map.x_max);
                printf("Do you want to see MARC moving or not ?\n Enter 1 for YES and 0 for NO :");
                int followMarc = userInput(0,1);
                printf("Do you want to see the complexity of the main functions ?\nEnter 1 for YES and 0 for NO :");
                COMPLEXITY = userInput(0,1);
                printf("\nLet's start the way to go to the base\n");
                int nbPhase = phaseUntilBase(map, loc, nbDrawndmoves, nbOfMoves,followMarc);
                messageEnd(nbPhase);
                break;
            }
        }
    }while(mission);
    return;
}



