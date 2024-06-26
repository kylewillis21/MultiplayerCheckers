#include "board.h"
#include <iostream>

#ifndef GAME_H
#define GAME_H

class game{
    public:
        // Constructors
        game(piece* red, piece* black, piece* blackKing, piece* redKing);

        // Accessors
        int getTurnNum() {return turnNum;}
        int getBlackPieces() {return blackPieces;}
        int getRedPieces() {return redPieces;}

        // Setters
        void setTurnNum(int num) {turnNum = num;}
        void setBlackPieces(int num) {blackPieces = num;}
        void setRedPieces(int num) {redPieces = num;}
        void incrementTurnNum() {turnNum++;}

        // Helper functions
        bool legalMove();
        bool makeMove(std::string target, std::string destination);
        void playGame(std::string target, std::string destination); // No longer in use
        bool checkWin(); // done
        bool checkRedWin(); // done
        bool checkBlackWin(); // done
        void updatePieceCount(); // done
        bool rightColor(int y1, int x1); // done
        std::string getTurn(); // done
        std::string toString() {return gameBoard.boardToString();}
        void stringToGame(std::string s);
        std::string gameToString();

        // Output
        void output(std::ostream& outs)const;

    private:
        int turnNum;
        int blackPieces;
        int redPieces;
        board gameBoard;
};

std::ostream& operator<<(std::ostream& outs, const game& g);

#endif