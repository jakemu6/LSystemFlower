//
//  stringEdit.cpp
//  LSystemFlower
//
//  Created by Jake Mu on 2/1/22.
//

#include "stringEdit.hpp"

stringEdit::stringEdit(){
}

void stringEdit::setup(int _position, string _successor, int _closingPos){
    position = _position;
    successor = _successor;
    closingPos = _closingPos;
}
