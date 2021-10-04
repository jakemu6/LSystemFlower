/*
 *  LRule.h
 *  Lsystem
 *
 *  Created by Daan on 01-04-11.
 *  Copyright 2011 Daan van Hasselt. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class LRule {
	
public:
	LRule(string pre, string succ);
    
    //stochastic LRule
    LRule(string pre, string succ1, float probability1, string succ2, float probability2);
    
    
	void print();
    string stochasticProbability();
	
	friend bool operator== (LRule &rule1, LRule &rule2);

    string stochasticPredecessor;
    string stochasticSuccessor1;
    float stochasticSuccessor1Probability;
    string stochasticSuccessor2;
    float stochasticSuccessor2Probability;

    

	string predecessor;
	string successor;	
};
