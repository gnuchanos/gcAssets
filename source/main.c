#include "Include/main.h"



int main() {



    char *games = (char*)malloc(sizeof(char) * 50);
    strcpy(games, "Half Life/Lef 4 Dead/Portal/TF3");
    printf("%s", games);


    free(games);
    return 0; }
