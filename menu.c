//
// Created by pierr on 11/19/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "created\tree.h"
#include "modified\map.h"

#include <unistd.h>

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
        printf("\nBase found in %d phases.\n\n", res);
    }
    else{
        printf("I'm lost [>.<] ! \n\n");
    }
}

int isMission(int beginning){
    // brief of the mission from the given
    if(beginning)printf("\tHello ! A very intense solar storm has just hit... The MARC - MArs Rover Cartograph rover, which was carrying out its mission very well, has suffered a malfunction. Its programming, guidance and movement systems have been seriously affected.\n Let's see if MARC can go back to the base !\n");
    printf("\nDo you want to start a mission ? (1 for YES or 0 for NO) \n");
    int mission = userInput(0,1);
    return mission;
}

t_map chooseMap(){
    char* allMaps[]= {"expedition", "intermediate", "middle", "tiny","wide"};
    printf("Choose a map among the following ones :\n");
    for(int i=0; i<NBMAP; i++){
        printf("%d - %s \n",i,allMaps[i]);
    }
    int choice;
    do{
        printf("To choose a map enter its number :");
        scanf("%d",&choice);
        if (choice >NBMAP || choice < 0){
            printf("Your choice is not in the list!\n");
        }
    }while(choice >NBMAP || choice < 0);
    t_map map = createMapFromFile(Maps[choice]);
    map.name = Maps[choice];

    displayMap(map);
    printf("\nIs this map (%s) good for you? (1 for YES or 0 for NO) \n",allMaps[choice]);
    if(userInput(0,1)) return map;
    else{
        freeMap(map);
        return chooseMap();
    }
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
    do{
        printf("Choose your beginning localisation (top left is 0,0):\n");
        printf("Choose your x coordinate : ");
        chosenLoc.pos.x = userInput(0,x_max-1);
        printf("Choose your y coordinate : ");
        chosenLoc.pos.y = userInput(0,y_max-1);
        if(!isValidLocalisation(chosenLoc.pos, x_max, y_max)){
            printf("\nYour localisation is not valid !\n");
        }
    }while(!isValidLocalisation(chosenLoc.pos, x_max, y_max));

    return chosenLoc;
}

void displayParameters(t_localisation loc, t_map map){
    printf("________________________________\n");
    printf("MARC beginning parameters :\n");
    printf("Position : (%d,%d) \nOrientation : %s\n", loc.pos.x, loc.pos.y, orientations[loc.ori]);
    printf("Map name : %s\n", map.name);
    printf("________________________________\n");
}

void manageComplexity(double* timeCplx, int display){
    if(display)printf("\n** Time complexity **\n");
    if(display)printf("\nTree : %f seconds\nMin leaf :%f seconds\nPath: %f microseconds\nPhases until the base: %f seconds\n", timeCplx[0], timeCplx[1], timeCplx[2], timeCplx[3]);
    for(int i= 0; i<4; i++){
        timeCplx[i] = 0.0;
    }
}

void menu(){
    int exit = 0;
    int nbDrawnMoves = 9;
    int nbOfMoves = 5;
    // to save complexity : tree, min leaf, path, phase until base
    double* timeCplx = (double*)malloc(sizeof(double)*5);
    manageComplexity(timeCplx,0);
    int mission = isMission(1);
    while(mission == 1){
        // proposition of scenarios
        printf("Which scenario do you want to chose? (Enter the number of your choice)");
        printf("\n 1. Pre-defined scenario 1 : great crossing ");
        printf("\n 2. Pre-defined scenario 2 : quick return to base ");
        printf("\n 3. Pre-defined scenario 3 : few miles away" );
        printf("\n 4. User-defined scenario : let's define your scenario");
        printf("\n 5. Exit ");
        int scenario = userInput(1,5);

        switch(scenario){
            // hard filled
            case 1:{
                printf("** Scenario 1 **\nMarc is far away from the base, he needs to achieve a huge way to go back to it. \nLet's see how he manages the path thanks to an animated map.\n");
                t_map map = createMapFromFile(Maps[4]);
                map.name = Maps[4];
                t_orientation ori = EAST;
                t_localisation loca = loc_init(3,3,ori);
                displayParameters(loca, map);
                COMPLEXITY = 0;
                printf("\nLet's start the way to go to the base ! \n");
                int nbPhase = phaseUntilBase(map, loca, nbDrawnMoves, nbOfMoves,1, timeCplx);
                messageEnd(nbPhase);
                freeMap(map);
                break;
            }

            case 2:{
                printf("** Scenario 2 **\n\nIn this scenario Marc is not far away from the base, he needs few phases to get back to it.\nHere details about Marc's movement and the complexity time will be displayed.\n");
                t_map map = createMapFromFile(Maps[1]);
                map.name = Maps[1];
                t_orientation ori = NORTH;
                t_localisation loca = loc_init(1,1, ori);
                COMPLEXITY = 1;
                displayParameters(loca, map);
                printf("\nLet's start the way to go to the base !\n");
                int nbPhase = phaseUntilBase(map, loca, nbDrawnMoves, nbOfMoves,0, timeCplx);
                messageEnd(nbPhase);
                manageComplexity(timeCplx,1);
                freeMap(map);
                break;
            }
            case 3:{
                printf("** Scenario 3 **\n\nIn this scenario Marc is not far away from the base, he needs few phases to get back to it.\nThe map will be displayed to follow it's progress.\n");
                t_map map = createMapFromFile(Maps[0]);
                map.name = Maps[0];
                t_orientation ori = SOUTH;
                t_localisation loca = loc_init(4,6, ori);
                displayParameters(loca, map);
                printf("\nLet's start the way to go to the base\n");
                COMPLEXITY = 1;
                int nbPhase = phaseUntilBase(map, loca, nbDrawnMoves, nbOfMoves,1, timeCplx);
                messageEnd(nbPhase);
                manageComplexity(timeCplx,1);
                freeMap(map);
                break;

            }
            //user filled
            case 4:{
                t_map map = chooseMap();
                t_localisation loc = chooseLocalisation(map.x_max, map.y_max);
                printf("\nDo you want to see MARC moving or not ?\n Enter 1 for YES and 0 for NO :");
                int followMarc = userInput(0,1);
                printf("Do you want to see the complexity of the main functions ?\nEnter 1 for YES and 0 for NO :");
                COMPLEXITY = userInput(0,1);
                printf("\nLet's start the way to go to the base\n");
                int nbPhase = phaseUntilBase(map, loc, nbDrawnMoves, nbOfMoves,followMarc, timeCplx);
                messageEnd(nbPhase);
                if(COMPLEXITY)manageComplexity(timeCplx, COMPLEXITY);
                freeMap(map);
                break;
            }
            case 5:{
                exit = 1;
                mission = 0;
                break;
            }
        }
        if(!exit)mission = isMission(0);
    }
    printf("\nGood bye ;) !");
    free(timeCplx);
    sleep(1);
}



