/*
 *  LSys.cpp
 *  Lsystem
 *
 *  Created by Daan on 01-04-11.
 *  Copyright 2011 Daan van Hasselt. All rights reserved.
 *
 */

#include "LSys.h"


LSys::LSys(){
	level = 0;	
}

void LSys::addVariable(string var){
	variables.push_back(var);
}

void LSys::removeVariable(string var){
	for(int i = 0; i < variables.size(); i++){
		if(variables[i] == var) variables.erase(variables.begin() + i);
	}
}

void LSys::printVariables(){
	cout << "LSys variables:" << endl;
	for(int i = 0; i < variables.size(); i++){
		cout << "\t\t\t\t" << variables[i] << endl;
	}
}

void LSys::addConstant(string cons){
	constants.push_back(cons);
}

void LSys::removeConstant(string cons){
	for(int i = 0; i < constants.size(); i++){
		if(constants[i] == cons) constants.erase(constants.begin() + i);
	}
}

void LSys::printConstants(){
	cout << "LSys constants:" << endl;
	for(int i = 0; i < constants.size(); i++){
		cout << "\t\t\t\t" << constants[i] << endl;
	}
}

void LSys::addRule(LRule rule){
	rules.push_back(rule);
}

void LSys::removeRule(LRule rule){
	for(int i = 0; i < rules.size(); i++){
		if(rules[i] == rule) rules.erase(rules.begin()+i);
	}
}

void LSys::printRules(){
	cout << "LSys rules:" << endl;
	for(int i = 0; i < rules.size(); i++){
		rules[i].print();
	}
}

void LSys::setStart(string _start){
	start = _start;
	curString = start;
}

void LSys::printStart(){
	cout << "LSys start:" << endl;
	cout << "\t\t\t\t" << start << endl;
}

string LSys::getNextLevel(){
	int length = curString.length();	// length of the current string

	string substr[length];				// split into 1-char substrings
	for(int i = 0; i < length; i++){
		substr[i] = curString.substr(i,1);
	}
    
//THIS IS BY RULE FIRST
    //start with first rule
    for (int i = 0; i < rules.size(); i++) {
        //go through each letter with each rule
        for (int j = 0; j < length; j++) {
            if (rules[i].CSPredecessor == substr[j]) {
                //check the directions
                if(rules[i].CSDirection == "left") {
                    if (rules[i].checkContext(substr[j-1])) {
                        substr[j] = rules[i].CSSuccessor;
                        //after this rule is applied skip over the letters changed
                        j += rules[i].CSSuccessor.length();
                    }
                } else if (rules[i].CSDirection == "right") {
                    if (rules[i].checkContext(substr[j+1])) {
                        substr[j] = rules[i].CSSuccessor;
                        //after this rule is applied skip over the letters changed
                        j += rules[i].CSSuccessor.length();
                    }
                } else {
                    ofLog() << "Type left or right for context direction";
                }
                
                

            } else if (rules[i].predecessor == substr[j]) {
                substr[j] = rules[i].successor;
                j += rules[i].successor.length();

            } else if (rules[i].stochasticPredecessor == substr[j]) {
                string stochSuccessor = rules[i].stochasticProbability();
                substr[j] = stochSuccessor;
                j += stochSuccessor.length();

            }
        }
    }
    
    
//THIS IS BY LETTER BY LETTER
//    //for each i which is each letter in the string+
//	for(int i = 0; i < length; i++){
//        // apply all rules in the rules vector
//		for(int j = 0; j < rules.size(); j++){
//            //do context sensitive rules first
//            //if the rule predecessor matches a letter in the string execute rule
//            if(substr[i] == rules[j].CSPredecessor){
//                //check if the left context matches the one in the rules
//                if (rules[j].checkLeftContext(substr[i-1])) {
//                    substr[i] = rules[j].CSSuccessor;
//                    j = rules.size();        // if one rule is applied, skip rest of rules only applied if the left context matches.
//                }
//            } else if(substr[i] == rules[j].predecessor){
//				substr[i] = rules[j].successor;
//				j = rules.size();		// if one rule is applied, skip rest of rules
//            } else if(substr[i] == rules[j].stochasticPredecessor){     //if not a predecessor check if it is stochastic
//                substr[i] = rules[j].stochasticProbability();
//                j = rules.size();        // if one rule is applied, skip rest of rules
//            }
//		}
//	}
	
	string result;						// merge into resulting string
	for(int i = 0; i < length; i++){
		result.append(substr[i]);
	}
	curString = result;

	level++;
	return curString;						// return current result
}

string LSys::getLevel(int _level){
	curString = start;
	string result;
	for(int i = 0; i < _level; i++){
		result = getNextLevel();
	}
	return result;
}

vector<string> LSys::getLevels(int _level){
    curString = start;
    vector<string> finalSentence;
    string result;
    
    //push the first starting sentence so that it is the 0 axiom
    finalSentence.push_back(curString);
    
    for(int i = 0; i < _level; i++){
        result = getNextLevel();
        finalSentence.push_back(result);
    }
    return finalSentence;
}
