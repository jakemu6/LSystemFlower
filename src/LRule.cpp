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

LRule::LRule(string pre, string succ, string _ruleType){
    //record ruletype
    ruleType = _ruleType;
    
    if (ruleType == "parametric") {
        //divide the different parts of the predacessor
        vector<string> splitString = ofSplitString(pre, ":");
        
        //make a substring of the length of first split to get the pre and parameter
        int length = splitString[0].length();
        string substr[length];
        for(int i = 0; i < length; i++){
            substr[i] = splitString[0].substr(i,1);
        }

        //getting the positions of the parentheses and then acquiring the contents between
        unsigned open = splitString[0].find("(");
        unsigned closed = splitString[0].find(")");
        
        //get the string between the parentheses - the parentheses
        string parStr = splitString[0].substr(open + 1, closed - 2);
        string parPre = splitString[0].substr(0 , open);
            
        //identified the pre and parameter by the position of parentheses and colon
        //in future parKey may need to be separated further to check if there are two parameters
        predecessor = parPre;
        parameterKey = parStr;
        parameterBool = splitString[1];
        successor = succ;
        
    } else if (ruleType == "rewrite") {
        //reminder that rewrite rules predecessors can only be one letter for now
        predecessor = pre;
        successor = succ;
    }
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


