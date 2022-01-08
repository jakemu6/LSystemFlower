/*
 *  LSys.cpp
 *  Lsystem
 *
 *  Created by Daan on 01-04-11.
 *  Copyright 2011 Daan van Hasselt. All rights reserved.
 *
 */



#include "LSys.h"
#include "stringEdit.hpp"


// a boolean function that tells ofSort how to compare two items
bool sortMe(stringEdit & a, stringEdit & b){
    if (a.position > b.position){
        return true;
    } else {
        return false;
    }
}

#include "muParser.h"
using namespace mu;

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

//TOO: have it read the parametric letters indicated by ( and )

string LSys::getNextLevel(){
    
    
    //record the current string
    //place into a substring vector
    int leng = curString.length();
    vector <string> curStringVec;
    for(int i = 0; i < leng; i++){
        curStringVec.push_back(curString.substr(i,1));
    }
    
    //record all the rules and booleans
    vector<string> predecessors;
    vector<string> paraBools;
    vector<string> paraKey;
    vector<string> successor;


    for (int i = 0; i < rules.size(); i++) {
        
        //for the parametric rules
        if (rules[i].ruleType == "parametric") {
            predecessors.push_back(rules[i].predecessor);
            paraBools.push_back(rules[i].parameterBool);
            paraKey.push_back(rules[i].parameterKey);
            successor.push_back(rules[i].successor);
        } else if (rules[i].ruleType == "rewrite") {
            predecessors.push_back(rules[i].predecessor);
            paraBools.push_back("NO BOOL EXISTING");
            paraKey.push_back("NO KEY EXISTING");
            successor.push_back(rules[i].successor);
        }
        else {
            predecessors.push_back("NO PREDECESSOR EXISTING");
            paraBools.push_back("NO BOOL EXISTING");
            paraKey.push_back("NO KEY EXISTING");
            successor.push_back("NO SUCCESSOR EXISTING");
        }
    }
            
    //record the position of where each of the edits are to take place along the string.
    vector<stringEdit> edits;

    for (int i = 0; i < predecessors.size(); i++) {
        for (int j = 0; j < curStringVec.size(); j++) {
            
            //check if any of the predeccessors match the current string
            if (predecessors[i] == curStringVec[j]) {
                
                if (rules[i].ruleType == "parametric") {
                    //if parametric check the paraBools to see if it satisfies
                    //need to get the value in brackets and substitute values into the bool
                    string truncatedCurrentStr = curString.substr(j, curStringVec.size());
                    
                    //Bracket as a string to find in successor and predecessors
                    string openBracket = "(";
                    string closedBracket = ")";
                    
                    //getting the positions of the parentheses and then acquiring the contents between as a string in the cut substring
                    int open = truncatedCurrentStr.find("(");
                    int closed = truncatedCurrentStr.find(")");
                    
                    string paraValueString = truncatedCurrentStr.substr(open + 1, closed - 2);

                    //check if the contents within brackets has a comma for two values
                    vector<string> splitKey;
                    vector<string> splitValue;
                    
                    if (paraValueString.find(",") != std::string::npos) {
                        //split the key to get two letter x and y
                        splitKey = ofSplitString(paraKey[i], ",");
                        splitValue = ofSplitString(paraValueString, ",");
                    }else {
                        splitKey.push_back(paraKey[i]);
                        splitValue.push_back(paraValueString);
                    }
                    
                    string boolCheck = paraBools[i];
                    
                    for (int k = 0; k < splitKey.size(); k++) {
                        ofStringReplace(boolCheck, splitKey[k], splitValue[k]);
                    }

                    bool conditionCheck = parseBoolean(boolCheck);
                    if (conditionCheck) {
                        
                        //Get the successor and start replacing the key with the values
                        string succ = successor[i];

                        for (int k = 0; k < splitKey.size(); k++) {
                            ofStringReplace(succ, splitKey[k], splitValue[k]);
                        }
                        
                        
                        if (succ.find("(") != std::string::npos && succ.find(")") != std::string::npos) {
                            
                            //find locations of a character in a string for the brackets
                            //currently only uses positioning to tell.
                            //Can not use bracket inside bracket yet.
                            vector<int> openLocations;
                            for (int k = 0; k < succ.size(); k++) {
                                if(succ[k] == '(') {
                                    openLocations.push_back(k);
                                }
                            }
                            vector<int> closedLocations;
                            for (int k = 0; k < succ.size(); k++) {
                                if(succ[k] == ')') {
                                    closedLocations.push_back(k);
                                }
                            }
                            
                            //convert the succ to a substring to find the equations
                            vector<string> succSubstring;
                            for(int k = 0; k < succ.size(); k++){
                                succSubstring.push_back(succ.substr(k,1));
                            }

                            //create a vector to contain all of the expressions that need to be done
                            //Currently accomodates only two expressions per bracket max
                            vector<string> expressions;
                            for (int k = 0; k < openLocations.size(); k++) {
                                
                                string exp;
                                for (int l = openLocations[k] + 1; l < closedLocations[k]; l++) {
                                    exp += succSubstring[l];
                                }
                                
                                //check if the expression has a comma in it
                                if (exp.find(",") != std::string::npos) {
                                    vector<string> splitExp = ofSplitString(exp, ",");
                                    expressions.push_back(splitExp[0]);
                                    expressions.push_back(splitExp[1]);
                                } else {
                                    expressions.push_back(exp);
                                }
                            }
                            
                            //for each of the expressions parse the math in it.
                            //then replace the string in the paraSucc
                            for (int k = 0; k < expressions.size(); k++) {
                                try
                                {
                                    mu::Parser p;
                                    p.SetExpr(expressions[k]);
                                    string parsedExpression = ofToString(p.Eval());
                                    ofStringReplace(succ, expressions[k], parsedExpression);
                                }
                                catch (mu::Parser::exception_type &e)
                                {
                                    std::cout << e.GetMsg() << std::endl;
                                }
                            }
                        }

                        stringEdit tempEdit;
                        tempEdit.setup(j, succ, closed);
                        edits.push_back(tempEdit);
                    }
                } else if (rules[i].ruleType == "rewrite") {
                    string succ = successor[i];
                    int preClosePos = predecessors[i].length();
                    
                    stringEdit tempEdit;
                    tempEdit.setup(j, succ, preClosePos-1);
                    edits.push_back(tempEdit);
//                    ofLog() << predecessors[i];
                }
            }
        }
    }
    
    ofSort(edits, &sortMe);
    
    //0. START THE EDITS AT THE BACK POSITION
    for (int i = 0; i < edits.size(); i++) {
        
        //1. REMOVE THE STRING AT POSITION

        vector<string>::iterator it = curStringVec.begin();
        vector<string>::iterator it1 = curStringVec.begin();

        advance(it,edits[i].position);
        advance(it1,edits[i].position + edits[i].closingPos + 1);
        
        curStringVec.erase(it,it1);
        
        //2. ADD THE NEW STRING IN
        vector<string>::iterator it2 = curStringVec.begin();
        advance(it2,edits[i].position);
        curStringVec.insert(it2,edits[i].successor);
    }
    

    //ATTEMPT 3 ENDS HERE
    
	int length = curString.length();	// length of the current string
    vector <string> substring;
//    list <string> sub;
	
    for(int i = 0; i < length; i++){
        substring.push_back(curString.substr(i,1));
//        sub.push_back(curString.substr(i,1));
	}
    
    //DEPRECATED CONTEXT SENSITIVE AND STOCHASTIC METHODS
    
////THIS IS BY RULE FIRST
//    //start with first rule
//    for (int i = 0; i < rules.size(); i++) {
//
//
//        for (int j = 0; j < length; j++) {
//
//
//            if (rules[i].CSPredecessor == substring[j]) {
//
//                //check the directions
//                if(rules[i].CSDirection == "left") {
//                    if (rules[i].checkContext(substring[j-1])) {
//                        substring[j] = rules[i].CSSuccessor;
//                        //after this rule is applied skip over the letters changed
//                        j += rules[i].CSSuccessor.length();
//                    }
//                } else if (rules[i].CSDirection == "right") {
//                    if (rules[i].checkContext(substring[j+1])) {
//                        substring[j] = rules[i].CSSuccessor;
//                        //after this rule is applied skip over the letters changed
//                        j += rules[i].CSSuccessor.length();
//                    }
//                } else {
////                    ofLog() << "Type left or right for context direction";
//                }
//            } else if (rules[i].predecessor == substring[j]) {
//                substring[j] = rules[i].successor;
//                j += rules[i].successor.length();
//
//            } else if (rules[i].stochasticPredecessor == substring[j]) {
//                string stochSuccessor = rules[i].stochasticProbability();
//                substring[j] = stochSuccessor;
//                j += stochSuccessor.length();
//
//            }
//        }
//    }
	
    std::string s = std::accumulate(curStringVec.begin(), curStringVec.end(), std::string{});

//    ofLog() << s;
    
//	string result;						// merge into resulting string
//	for(int i = 0; i < length; i++){
//		result.append(substring[i]);
//	}
	curString = s;

	level++;
	return curString;						// return current result
}


//for the parametric rules to check if it satisfies conditions
bool LSys::parseBoolean(const std::string &str) {
    
    
    
    if (str.find("=") != std::string::npos) {
        
        //split the string at the equals
        vector<string> result;
        result = ofSplitString(str, "=");
        
        //check if there is a greater or less than symbol and remove it
        if (result[0].find(">") != std::string::npos) {
            ofStringReplace(result[0], ">", "");
        }
        
        if (result[0].find("<") != std::string::npos) {
            ofStringReplace(result[0], "<", "");
        }

        //convert to floats to compare with the operator
        float value1 = ofToFloat(result[0]);
        float value2 = ofToFloat(result[1]);
        
        if (value1 == value2) {
            return "true";
        }
    }
    
    if (str.find("<") != std::string::npos) {
        vector<string> result;
        result = ofSplitString(str, "<");
        
        //check if there is an equals symbol and remove it
        if (result[1].find("=") != std::string::npos) {
            ofStringReplace(result[1], "=", "");
        }
        float value1 = ofToFloat(result[0]);
        float value2 = ofToFloat(result[1]);
        if (value1 < value2) {
            return "true";
        }
    }
    
    if (str.find(">") != std::string::npos) {
        vector<string> result;
        result = ofSplitString(str, ">");
        
        //check if there is an equals symbol and remove it
        if (result[1].find("=") != std::string::npos) {
            ofStringReplace(result[1], "=", "");
        }
        float value1 = ofToFloat(result[0]);
        float value2 = ofToFloat(result[1]);
        if (value1 > value2) {
            return "true";
        }
    }
    
    
    
    return str == "true" || str == "yes" || str == "on";
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


