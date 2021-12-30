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
    
    //Context Sensitive Rule
    LRule(string pre, string contextDir, string context, string succ);

//    //Parametric Rules
    LRule(string pre, string succ, string parametric);
    string paraPredecessor;
    string parameterKey;
    string parameterBool;
    string parameterSuccessor;

    
    
	void print();
    string stochasticProbability();
    
    bool checkContext(string context);
    string contextSensitive();

	
	friend bool operator== (LRule &rule1, LRule &rule2);

    //CS-ContextSensitive
    string CSPredecessor;
    string CSSuccessor;
    string CSContext;
    string CSDirection;
    
    //Stochastic
    string stochasticPredecessor;
    string stochasticSuccessor1;
    float stochasticSuccessor1Probability;
    string stochasticSuccessor2;
    float stochasticSuccessor2Probability;

    
    //No-Contex
	string predecessor;
	string successor;	
};
