//
// Created by pierr on 11/19/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include "menu.h"

void mission(){
    int mission;
    printf("Do you want to start a mission ? Enter 1 for YES or 0 for NO : \n");
    scanf("%d",&mission);
    if(mission){
        choose_map();
        
    }
}



