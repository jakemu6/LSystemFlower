/*
 *  LRule.cpp
 *  Lsystem
 *
 *  Created by Daan on 01-04-11.
 *  Copyright 2011 Daan van Hasselt. All rights reserved.
 *
 */

#include "LRule.h"


LRule::LRule(string pre, string succ, string _ruleType){
    //record ruletype
    ruleType = _ruleType;
    
    if (ruleType == "parametric") {
        //divide the different parts of the predacessor
        vector<string> splitString = ofSplitString(pre, ":");
        
        //make a substring of the length of first split to get the pre and parameter
        typename string::size_type length = splitString[0].length();
        string substr[length];
        for(int i = 0; i < length; i++){
            substr[i] = splitString[0].substr(i,1);
        }

        //getting the positions of the parentheses and then acquiring the contents between
        typename string::size_type open = splitString[0].find("(");
        typename string::size_type closed = splitString[0].find(")");
        
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

bool operator== (LRule &rule1, LRule &rule2){
	return (rule1.predecessor == rule2.predecessor &&
			rule1.successor == rule2.successor);
}


