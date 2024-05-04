#include "space.h"
#include "piece.h"
#include "colors.h"
#include <iostream>
#include <string>

using namespace std;

space::space(){ // This constructor should never be used
    isEmpty = true;
    playableSpot = false;
    currentPiece = nullptr;
}

space::space(bool empty, bool playable, piece* p){
    isEmpty = empty;
    playableSpot = playable;
    currentPiece = p;
}

void space::clearSpace(){
    isEmpty = true;
    currentPiece = nullptr;
}

void space::output(std::ostream& outs)const{
    // # Will represent all black playable spaces
    // $ Will represent all red non playable spaces
    // Any space with a piece in it will display the piece
    if(isEmpty && playableSpot){
        outs << " ";
    }
    else if(isEmpty && !playableSpot){
        outs << BOLD("X");
    }
    else if(!isEmpty && playableSpot && currentPiece != nullptr){
        outs << *currentPiece;
    }
    else{
        outs << " ";
    }
}

std::ostream& operator<<(std::ostream& outs, const space& s){
    s.output(outs);
    return outs;
}
