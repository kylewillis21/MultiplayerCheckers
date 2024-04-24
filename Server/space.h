#include <iostream>
#include "piece.h"
#ifndef SPACE_H
#define SPACE_H

class space{
    public:
        // Constructors
        space();
        space(bool empty, bool playable, piece* p = nullptr);
        
        // Getters
        piece* getCurrentPiece() {return currentPiece;}
        bool getIsEmpty() {return isEmpty;}
        bool getPlayableSpot() {return playableSpot;}

        // Modifiers
        void setIsEmpty(bool b) {isEmpty = b;}
        void setCurrentPiece(piece* p) {currentPiece = p;}
        void clearSpace();
        void makeKing(piece* k) {currentPiece = k;}

        void output(std::ostream& outs)const;
    private:
        bool isEmpty;
        bool playableSpot;
        piece* currentPiece;
};

std::ostream& operator<<(std::ostream& outs, const space& s);

#endif