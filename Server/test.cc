#include "piece.h"
#include "board.h"
#include "space.h"
#include "colors.h"
#include "game.h"
#include <iostream>

using namespace std;

int main(){
    // Need to create all the pieces that will be used by the pointers
    piece red("red");
    piece black("black");
    piece blackKing("black");
    blackKing.makeKing();
    piece redKing("red");
    redKing.makeKing();

    game newGame(&red, &black, &blackKing, &redKing);
    newGame.startGame();
    return 0;
    
}