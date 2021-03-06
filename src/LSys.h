/*
 *  LSys.h
 *  Lsystem
 *
 *  Created by Daan on 01-04-11.
 *  Copyright 2011 Daan van Hasselt. All rights reserved.
 *
 */

#pragma once

#include <vector>
#include "ofMain.h"
#include "LRule.h"

class LSys {
	
public:
	
	LSys();
	void addVariable(string var);
	void removeVariable(string var);
	void printVariables();
	
	void addConstant(string cons);
	void removeConstant(string cons);
	void printConstants();
	
	void addRule(const LRule & rule);
	void removeRule(LRule rule);
	void printRules();
	
	void setStart(const string & start);
	void printStart();
	
    bool parseBoolean(const std::string &str);
    
	string getNextLevel();
	string getLevel(const int & level);
    
    vector<string> getLevels(const int & _level);
	
	vector<string> variables;
	vector<string> constants;
	vector<LRule> rules;
	string start;
	
protected:
	int level;
	string curString;
};
