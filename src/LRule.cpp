/*
 *  LRule.cpp
 *  Lsystem
 *
 *  Created by Daan on 01-04-11.
 *  Copyright 2011 Daan van Hasselt. All rights reserved.
 *
 */

#include "LRule.h"

LRule::LRule(string pre, string succ){
	predecessor = pre;
	successor = succ;
}

LRule::LRule(string pre, string succ1, float probability1, string succ2, float probability2){
    stochasticPredecessor = pre;
    stochasticSuccessor1 = succ1;
    stochasticSuccessor2 = succ2;

    stochasticSuccessor1Probability = probability1;
    stochasticSuccessor2Probability = probability2;
}

LRule::LRule(string pre, string contextDir, string context, string succ){
    CSPredecessor = pre;
    CSSuccessor = succ;
    CSContext = context;
    CSDirection = contextDir;
}

bool LRule::checkContext(string context) {
    if (CSContext == context) {
        return true;
    } else {
        return false;
    }
}


string LRule::stochasticProbability(){
    if (stochasticSuccessor1Probability + stochasticSuccessor2Probability == 1.0) {
        float r = ofRandom(1.0);
        if (r < stochasticSuccessor1Probability) {
            return stochasticSuccessor1;
        } else if ( r > stochasticSuccessor1Probability) {
            return stochasticSuccessor2;
        }
    } else {
        ofLog() << "error: stochastic probabilities are not adding up to 1.0";
    }
}

void LRule::print(){
	cout << "\t\t\t\t" << predecessor << "->" << successor << endl;
}

bool operator== (LRule &rule1, LRule &rule2){
	return (rule1.predecessor == rule2.predecessor &&
			rule1.successor == rule2.successor);
}
