/***********************************************************************
	The implementation file for piece.h, which desciebes a single piece
    on the board.

    Kyle Willis
***********************************************************************/

#include "piece.h"
#include "colors.h"
#include <iostream>
#include <string>

using namespace std;

// Constructors
piece::piece(){ // This constructor will most likely never be used
    color = "undefined";
    isKing = false;
}

piece::piece(std::string col){
    color = col;
    isKing = false;
}

void piece::output(std::ostream& outs)const{
    // We will use capital letters to represent if a piece is a king or not
    if (isKing && color == "red") {
        outs << FRED("R");
    }
    else if(isKing && color == "black"){
        outs << FCYN("B");
    }
    else if (color == "red") {
        outs << FRED("r");
    }
    else if (color == "black"){
        outs << FCYN("b");
    }

    else {
        outs << " ";
    }
}

ostream& operator <<(ostream& outs, const piece& p){
    p.output(outs);
    return outs;
}

