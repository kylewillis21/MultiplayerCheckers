#include <iostream>
#ifndef PIECE_H
#define PIECE_H

class piece{
    public:
        // Constructors
        piece();
        piece(std::string col);
        // Getters
        std::string getColor() {return color;}
        bool getIsKing() {return isKing;}
        // Modifiers
        void makeKing() {isKing = true;}
        // Output
        void output(std::ostream& outs)const;
    private:
        std::string color;
        bool isKing;
};

std::ostream& operator <<(std::ostream& outs, const piece& c);

#endif