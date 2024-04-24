#include "piece.h"
#include "board.h"
#include "space.h"
#include "colors.h"
#include <iostream>

using namespace std;

int main(){
    piece red("red");
    piece black("black");
    board newGame(&red, &black);
    
    cout << newGame;
    newGame.movePiece("24", "35");
    newGame.movePiece("57", "46");
    newGame.movePiece("35","57");
    newGame.movePiece("26","37");
    newGame.movePiece("37","55");
    cout << newGame;
}