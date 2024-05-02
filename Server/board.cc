#include "board.h"
#include "piece.h"
#include "space.h"
#include "colors.h"
#include <iostream>
#include <string>

using namespace std;

board::board(){
    redKing = nullptr;
    blackKing = nullptr;
}

board::board(piece* red, piece* black, piece* kingBlack, piece* kingRed){ // this constructs a new board for a new game
    redKing = kingRed;
    blackKing = kingBlack;
    redPiece = red;
    blackPiece = black;
    space redpiece(false, true, red);
    space blackpiece(false, true, black);
    space emptyPlayable(true, true, nullptr);
    space emptyNoPlay(true, false, nullptr);
    // laid out in formay y,x
    
    //  placing the red pieces on the board
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 8; j++){
            if(i%2 == 0) {
                if(j%2 == 0){
                    mainBoard[i][j] = redpiece;
                }
                else if(j%2 == 1){
                    mainBoard[i][j] = emptyNoPlay;
                }
            }
            else if(i%2 == 1){
                if(j%2 == 0){
                    mainBoard[i][j] = emptyNoPlay;
                }
                else if(j%2 == 1){
                    mainBoard[i][j] = redpiece;
                }
            }
        }
    }

    // creating the open spaces on the board
    for(int i = 3; i < 5; i++) {
        for(int j = 0; j < 8; j++) {
            if(i%2 == 0) {
                if(j%2 == 0){
                    mainBoard[i][j] = emptyPlayable;
                }
                else if(j%2 == 1){
                    mainBoard[i][j] = emptyNoPlay;
                }
            }
            else if(i%2 == 1){
                if(j%2 == 0){
                    mainBoard[i][j] = emptyNoPlay;
                }
                else if(j%2 == 1){
                    mainBoard[i][j] = emptyPlayable;
                }
            }
        }
    }

    // placing the black pieces on the board
    for(int i = 5; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(i%2 == 0) {
                if(j%2 == 0){
                    mainBoard[i][j] = blackpiece;
                }
                else if(j%2 == 1){
                    mainBoard[i][j] = emptyNoPlay;
                }
            }
            else if(i%2 == 1){
                if(j%2 == 0){
                    mainBoard[i][j] = emptyNoPlay;
                }
                else if(j%2 == 1){
                    mainBoard[i][j] = blackpiece;
                }
            }
        }
    }
}

// This will move a piece on the board by going through a series of checks to make sure it is possible
bool board::movePiece(int y1, int x1, int y2, int x2){
    // A variable to see if a piece has jumped another piece in this turn
    bool hasJumped = false;

    // Check to make sure there is a piece where the target is
    if(mainBoard[y1][x1].getIsEmpty() == true){
        cout << "Error: there is no piece to move" << endl;
        return false;
    }
    else if(!mainBoard[y1][x1].getPlayableSpot() || !mainBoard[y2][x2].getPlayableSpot()){
        cout << "Error: Unplayable spot involved in this move" << endl;
        return false;
    }
    // Check to make sure the destination is also empty
    else if(mainBoard[y2][x2].getIsEmpty() == false){
        cout << "Error: there is already a piece there" << endl;
        return false;
    }
    // Check to make sure the destination is a playable spot
    else if(mainBoard[y2][x2].getPlayableSpot() == false){
        cout << "Error: this is an illegal move" << endl;
        return false;
    }

    if(!isLegalMove(y1,x1,y2,x2)){
        cout << "Error: This is not a legal move" << endl;
        return false;
    }
    
    // Move the piece to where it needs to go
    mainBoard[y2][x2].setIsEmpty(false);
    mainBoard[y2][x2].setCurrentPiece(mainBoard[y1][x1].getCurrentPiece());

    // Update original spot
    mainBoard[y1][x1].setCurrentPiece(nullptr);
    mainBoard[y1][x1].setIsEmpty(true);

    // Check to see if the piece needs to be set to king
    if(mainBoard[y2][x2].getCurrentPiece()->getColor() == "black"){
        if(isKingMe(y2, "black")){
            mainBoard[y2][x2].makeKing(blackKing);
        }
    }
    else{
        if(isKingMe(y2, "red")){
            mainBoard[y2][x2].makeKing(redKing);
        }
    }

    // At this point the move has been made and we can check to see if the
    // original move jumped any pieces
    if(abs(y1-y2) == 2 && abs(x1-x2) == 2){
        hasJumped = true;
    }
    
    if(canDoubleJump(y2,x2) && hasJumped){
        string destination;
        output(cout);
        cout << "A double jump is possible!" << endl;
        cout << "Where would you like the piece on " << y2 << x2 << " to jump?: ";
        cin >> destination;
        int y3 = destination[0] - '0';
        int x3 = destination[1] - '0';
        movePiece(y2, x2, y3, x3);
    }
    return true;
}

// Helper functions
bool board::isLegalMove(int y1, int x1, int y2, int x2){
    piece currentPiece = *mainBoard[y1][x1].getCurrentPiece();

    if(currentPiece.getColor() == "red"){
        return isRedLegalMove(y1,x1,y2,x2);
    }
    else if(currentPiece.getColor() == "black"){
        return isBlackLegalMove(y1,x1,y2,x2);
    }
    else{ // This should never hit but in case it somehow does
        return false;
    }
}

// This will return whether a move is legal for black specific pieces
bool board::isBlackLegalMove(int y1, int x1, int y2, int x2){
    piece currentPiece = *mainBoard[y1][x1].getCurrentPiece();
    
    // Making sure that the move is within the boundaries of the board
    if(y1 >= 0 && y1 <= 7 && x1 >= 0 && x1 <= 7 && y2 >= 0 && y2 <= 7 && x2 >= 0 && x2 <= 7){
        // Checking to make sure a non king piece isn't moving backwards
        if(currentPiece.getIsKing() == false && y1 <= y2){
            cout << "Non king black pieces can't move backwards" << endl;
            return false;
        }
        // Check to see if the player is trying to jump the other players piece
        else if(abs(y1-y2) == 2 && abs(x1-x2) == 2){
            if(!isLegalJump(y1,x1,y2,x2,"black")){
                return false;
            }
        }
        // Have to make sure the piece only moves one spot at a time
        else if (abs(y1-y2) != 1 && abs(x1-x2) != 1){
            cout << "Only 1 space can be moved at a time" << endl;
            return false;
        }
    }
    else { // If the move is not within the board
        cout << "Error: trying to move a piece out of bounds" << endl;
        return false;
    }

    // If it gets down to this statement it is a legal move
    // Will need to check if the piece needs to be turned to a king
    return true;
}

bool board::isRedLegalMove(int y1, int x1, int y2, int x2){
    piece currentPiece = *mainBoard[y1][x1].getCurrentPiece();
    
    // Making sure that the move is within the boundaries of the board
    if(y1 >= 0 && y1 <= 7 && x1 >= 0 && x1 <= 7 && y2 >= 0 && y2 <= 7 && x2 >= 0 && x2 <= 7){
        // Checking to make sure a non king piece isn't moving backwards
        if(currentPiece.getIsKing() == false && y1 >= y2){
            cout << "Non king red pieces can't move backwards" << endl;
            return false;
        }
        // Check to see if the player is trying to jump the other players piece
        else if(abs(y1-y2) == 2 && abs(x1-x2) == 2){
            if(!isLegalJump(y1,x1,y2,x2,"red")){
                return false;
            }
        }
        // Have to make sure the piece only moves one spot at a time
        else if (abs(y1-y2) != 1 && abs(x1-x2) != 1){
            cout << "Only 1 space can be moved at a time" << endl;
            return false;
        }
    }
    else { // If the move is not within the board
        cout << "Error: trying to move a piece out of bounds" << endl;
        return false;
    }

    // If it gets down to this statement it is a legal move
    return true;
}

bool board::isLegalJump(int y1, int x1, int y2, int x2, std::string color){
    int targetY = (y1 + y2)/2;
    int targetX = (x1 + x2)/2;
    // Checking to make sure there is a piece to be jumped
    if (mainBoard[targetY][targetX].getIsEmpty() == true){
        cout << "Error: no target to be jumped" << endl;
        return false;
    }
    
    // Checking color specific rules
    if (color == "black"){
        // Checking to make sure the piece is being jumped is the opposite color
        if(mainBoard[targetY][targetX].getCurrentPiece()->getColor() == "black"){
            cout << "Error: cannot jump your own pieces" << endl;
            return false;
        }
    }
    else { // This will be for all of the red pieces trying to jump
        // Checking to make sure the piece is being jumped is the opposite color
        if(mainBoard[targetY][targetX].getCurrentPiece()->getColor() == "red"){
            cout << "Error: cannot jump your own pieces" << endl;
            return false;
        }
    }
    // If the function gets down to this statement it is a legal jump
    // Remove the piece that was jumped
    mainBoard[targetY][targetX].clearSpace();
    return true;
}

bool board::isKingMe(int y2, std::string color) {
    if(y2 == 0 && color == "black"){
        return true;
    }
    else if(y2 == 7 && color == "red"){
        return true;
    } 
    else {
        return false;
    }
}

bool board::canDoubleJump(int y, int x) {
    string color = mainBoard[y][x].getCurrentPiece()->getColor();

    if(color == "red") {
        return canDoubleJumpRed(y,x);
    }
    else if(color == "black"){
        return canDoubleJumpBlack(y,x);
    }
    return false;
}

bool board::canDoubleJumpBlack(int y, int x){
    piece currentPiece = *mainBoard[y][x].getCurrentPiece();
    
    if(y+2 < 8 && x+2 < 8 && currentPiece.getIsKing()){ // ++
        if(mainBoard[y+2][x+2].getIsEmpty()){
            if(!mainBoard[y+1][x+1].getIsEmpty()){
                if(mainBoard[y+1][x+1].getCurrentPiece()->getColor() != currentPiece.getColor()){
                    return true; // All checks passed
                }
            }
        }
    }
    if(y-2 >= 0 && x-2 >= 0){ // --
        if(mainBoard[y-2][x-2].getIsEmpty()){
            if(!mainBoard[y-1][x-1].getIsEmpty()){
                if(mainBoard[y-1][x-1].getCurrentPiece()->getColor() != currentPiece.getColor()){
                    return true; // All checks passed
                }
            }
        }
    }
    if(y-2 >= 0 && x+2 < 8){ // -+ 
        if(mainBoard[y-2][x+2].getIsEmpty()){
            if(!mainBoard[y-1][x+1].getIsEmpty()){
                if(mainBoard[y-1][x+1].getCurrentPiece()->getColor() != currentPiece.getColor()){
                    return true; // All checks passed
                }
            }
        }
    }
    if(y+2 < 8 && x-2 >= 0 && currentPiece.getIsKing()){ // +-
        if(mainBoard[y+2][x-2].getIsEmpty()){
            if(!mainBoard[y+1][x-1].getIsEmpty()){
                if(mainBoard[y+1][x-1].getCurrentPiece()->getColor() != currentPiece.getColor()){
                    return true; // All checks passed
                }
            }
        }
    }
    return false;
}

bool board::canDoubleJumpRed(int y, int x){
    piece currentPiece = *mainBoard[y][x].getCurrentPiece();
    
    if(y+2 < 8 && x+2 < 8){ // ++
        if(mainBoard[y+2][x+2].getIsEmpty()){
            if(!mainBoard[y+1][x+1].getIsEmpty()){
                if(mainBoard[y+1][x+1].getCurrentPiece()->getColor() != currentPiece.getColor()){
                    return true; // All checks passed
                }
            }
        }
    }
    if(y-2 >= 0 && x-2 >= 0 && currentPiece.getIsKing()){ // --
        if(mainBoard[y-2][x-2].getIsEmpty()){
            if(!mainBoard[y-1][x-1].getIsEmpty()){
                if(mainBoard[y-1][x-1].getCurrentPiece()->getColor() != currentPiece.getColor()){
                    return true; // All checks passed
                }
            }
        }
    }
    if(y-2 >= 0 && x+2 < 8 && currentPiece.getIsKing()){ // -+ Ensures that if it's jumping backwards that the piece is also a king
        if(mainBoard[y-2][x+2].getIsEmpty()){
            if(!mainBoard[y-1][x+1].getIsEmpty()){
                if(mainBoard[y-1][x+1].getCurrentPiece()->getColor() != currentPiece.getColor()){
                    return true; // All checks passed
                }
            }
        }
    }
    if(y+2 < 8 && x-2 >= 0){ // +-
        if(mainBoard[y+2][x-2].getIsEmpty()){
            if(!mainBoard[y+1][x-1].getIsEmpty()){
                if(mainBoard[y+1][x-1].getCurrentPiece()->getColor() != currentPiece.getColor()){
                    return true; // All checks passed
                }
            }
        }
    }
    return false;
}

std::string board::boardToString(){
    // Initialize a string to be 64 characters long
    std::string board(64, ' ');
    int count = 0;
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            if(!mainBoard[i][j].getPlayableSpot()) {
                board[count] = 'X';
            }
            else if(mainBoard[i][j].getIsEmpty()) {
                board[count] = 'O';
            }
            else if(mainBoard[i][j].getCurrentPiece()->getIsKing()){
                if(mainBoard[i][j].getCurrentPiece()->getColor() == "black"){
                    board[count] = 'B';
                }
                else{
                    board[count] = 'R';
                }
            }
            else {
                if(mainBoard[i][j].getCurrentPiece()->getColor() == "black"){
                    board[count] = 'b';
                }
                else {
                    board[count] = 'r';
                }
            }
            count++;
        }
    }

    return board;
}

void board::stringToBoard(std::string b){
    // Check to make sure that the string is 64 characters long
    if(b.length() != 64){
        cout << "String not the right length" << endl;
        return;
    }

    int count = 0;
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            if(b[count] == 'X'){
                mainBoard[i][j] = space(true, false, nullptr);
            }
            else if(b[count] == 'O'){
                mainBoard[i][j] = space(true, true, nullptr);
            }
            else if(b[count] == 'b'){
                mainBoard[i][j] = space(false, true, blackPiece);
            }
            else if(b[count] == 'r'){
                mainBoard[i][j] = space(false, true, redPiece);
            }
            else if(b[count] == 'B'){
                mainBoard[i][j] = space(false, true, blackKing);
            }
            else if(b[count] == 'R'){
                mainBoard[i][j] = space(false, true, redKing);
            }
            else {
                cout << "Error: Invalid character in board::stringToBoard()" << endl;
                return;
            }
            count++;
        }
    }
}

// a function that will print out the current state of the board
void board::output(std::ostream& outs)const{
    outs << "\n   0 1 2 3 4 5 6 7\n";
    outs << "  _________________\n";
    for(int i = 7; i >= 0; i--){
        outs << i << " ";
        for(int j = 0; j  < 8; j++){
            outs << "|" << mainBoard[i][j];
        }
        outs << "|\n" << "  _________________\n";
    }
}

ostream& operator <<(ostream& outs, const board& b){
    b.output(outs);
    return outs;
}