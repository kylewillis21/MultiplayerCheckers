#include "board.h"
#include <iostream>

#ifndef GAME_H
#define GAME_H

class game{
    public:
        // Constructors
        game(piece* red, piece* black);

        // Accessors
        int getTurnNum() {return turnNum;}
        int getBlackPieces() {return blackPieces;}
        int getRedPieces() {return redPieces;}

        // Setters
        void setTurnNum(int num) {turnNum = num;}
        void setBlackPieces(int num) {blackPieces = num;}
        void setRedPieces(int num) {redPieces = num;}

        // Helper functions
        bool legalMove();
        void makeMove();

    private:
        int turnNum;
        int blackPieces;
        int redPieces;
        board gameBoard;
};

std::ostream& operator<<(std::ostream& outs, const game& g);

#endif