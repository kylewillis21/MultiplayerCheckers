#include <iostream>
#include "piece.h"
#include "space.h"
#ifndef BOARD_H
#define BOARD_H

class board{
    public:
        // Constructors
        board();
        board(piece* red, piece* black, piece* kingBlack, piece* kingRed); // Will create a new board ready to be played on

        // Getters
        space getSpaceFromBoard(int y, int x) {return mainBoard[y][x];}

        // Modifiers
        bool movePiece(int y1, int x1, int y2, int x2);
        
        void output(std::ostream& outs)const;

        
    private:
        space mainBoard[8][8];
        piece* redKing;
        piece* blackKing;

        // Helper functions inside of other functions
        bool isLegalMove(int y1, int x1, int y2, int x2);
        bool isBlackLegalMove(int y1, int x1, int y2, int x2);
        bool isRedLegalMove(int y1, int x1, int y2, int x2);
        bool isLegalJump(int y1, int x1, int y2, int x2, std::string color);
        bool isKingMe(int y2, std::string color);
        
};

std::ostream& operator<<(std::ostream& outs, const board& b);

#endif