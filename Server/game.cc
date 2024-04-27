#include "game.h"
#include "colors.h"
#include <iostream>
#include <string>

using namespace std;

game::game(piece* red, piece* black, piece* blackKing, piece* redKing){
    turnNum = 0;
    blackPieces = 12;
    redPieces = 12;
    gameBoard = board(red, black, blackKing, redKing);
}

bool game::makeMove(std::string target, std::string destination){
    // Need to convert the strings into integers
    int y1 , y2, x1, x2;
    y1 = target[0] - '0';
    x1 = target[1] - '0';
    y2 = destination[0] - '0';
    x2 = destination[1] - '0';
    if(!rightColor(y1,x1)){
        return false;
    }

    if(gameBoard.movePiece(y1,x1,y2,x2)){
        // If this hits the move was correctly made
        return true;
    }
    return false;
}

void game::playGame(std::string target, std::string destination){
    while(!checkWin()){ //  Program will be in this loop until there is a winner
        cout << gameBoard;
        cout << "\nIt is " << getTurn() << " turn" << endl;
        do {
            cout << "What piece would you like to move: ";
            cin >> target;
            cout << "Where would you like to move " << target << ": ";
            cin >> destination;
        } while(!makeMove(target,destination));
        turnNum++;
        updatePieceCount();
    }
    return;
}

bool game::checkWin(){
    if(checkBlackWin() || checkRedWin()){
        return true;
    }
    return false;
}

bool game::checkRedWin(){
    if (blackPieces == 0){
        cout << "RED WINS!" << endl;
        return true;
    }
    return false;
}

bool game::checkBlackWin(){
    if (redPieces == 0){
        cout << "BLACK WINS!" << endl;
        return true;
    }
    return false;
}

void game::updatePieceCount(){
    int redCount = 0;
    int blackCount = 0;

    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(!gameBoard.getSpaceFromBoard(i, j).getIsEmpty()){
                if(gameBoard.getSpaceFromBoard(i, j).getCurrentPiece()->getColor() == "red"){
                    redCount++;
                }
                else if(gameBoard.getSpaceFromBoard(i, j).getCurrentPiece()->getColor() == "black"){
                    blackCount++;
                }
            }
        }
    }

    redPieces = redCount;
    blackPieces = blackCount;
    return;
}

bool game::rightColor(int y1, int x1){
    string color;
    if(turnNum%2 == 0){
        color = "black";
    }
    else{
        color = "red";
    }
    if(gameBoard.getSpaceFromBoard(y1,x1).getIsEmpty() == false){
        if(gameBoard.getSpaceFromBoard(y1,x1).getCurrentPiece()->getColor() == color){
            return true;
        }
        else{
            cout << "Error: trying to play the other players piece" << endl;
        }
    }
    cout << "Error: this is an unplayable/empty space" << endl;
    return false;
}

std::string game::getTurn(){
    if(turnNum%2==0){
        return FCYN("blues");
    }
    return FRED("reds");
}


// Output functions

void game::output(std::ostream& outs)const{
    outs << gameBoard;
}

ostream& operator <<(ostream& outs, const game& g){
    g.output(outs);
    return outs;
}