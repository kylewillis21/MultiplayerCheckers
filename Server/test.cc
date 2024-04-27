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
    string target = "";
    string destination = "";
    
    while(!newGame.checkWin()){
        cout << newGame;
        cout << "It is " << newGame.getTurn() << " turn" << endl;
        do {
            cout << "What piece would you like to move: ";
            cin >> target;
            cout << "Where would you like to move " << target << ": ";
            cin >> destination;
            if(target == "end" || destination == "end") {return 0;} // This is strictly for testing
        } while(!newGame.makeMove(target, destination));
        newGame.incrementTurnNum();
    }
    return 0;
    
}