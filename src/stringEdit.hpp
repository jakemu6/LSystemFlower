//
//  stringEdit.hpp
//  LSystemFlower
//
//  Created by Jake Mu on 2/1/22.
//

#ifndef stringEdit_hpp
#define stringEdit_hpp

#include "ofMain.h"

class stringEdit {
    public: // place public functions or variables declarations here

    // methods, equivalent to specific functions of your class objects
    void setup(int _position, string _successor, int _closingPos);    // setup method, use this to setup your object's initial state
//    void update();  // update method, used to refresh your objects properties
//    void draw();    // draw method, this where you'll do the object's drawing
    
    // variables
    int position;
    
    //closing bracket position so that we know how many characters to remove from the string
    int closingPos;
    
    
    string successor;

    stringEdit();  // constructor - used to initialize an object, if no properties are passed the program sets them to the default value
    private: // place private functions or variables declarations here
};

#endif /* stringEdit_hpp */
