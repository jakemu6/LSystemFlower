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
    
    string ruleType;

//    //Parametric Rules
    LRule(string pre, string succ, string _ruleType);
    string paraPredecessor;
    string parameterKey;
    string parameterBool;
    string parameterSuccessor;

    
    
	void print();
    string stochasticProbability();
    
    bool checkContext(string context);
    string contextSensitive();

	
	friend bool operator== (LRule &rule1, LRule &rule2);

    //No-Contex
	string predecessor;
	string successor;	
};
