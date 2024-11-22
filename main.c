#include <stdio.h>
#include "modified\map.h"
#include "created\tree.h"
#include "menu.h"
#include <time.h>

int main() {
    srand(time(NULL));
    // asks the user if he wants to start a mission and the parameters of it
    menu();
    return 0;
}
