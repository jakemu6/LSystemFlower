/*
 *  LSys.cpp
 *  Lsystem
 *
 *  Created by Daan on 01-04-11.
 *  Copyright 2011 Daan van Hasselt. All rights reserved.
 *
 */

#include "LSys.h"

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
	int length = curString.length();	// length of the current string

//	string substr[length];				// split into 1-char substrings
    vector<string> substring;
    //allocate memory to the substring
//    substring.resize(100);
	
    for(int i = 0; i < length; i++){
//		substr[i] = curString.substr(i,1);
        substring.push_back(curString.substr(i,1));
        
	}
    
//THIS IS BY RULE FIRST
    //start with first rule
    for (int i = 0; i < rules.size(); i++) {
        //go through each letter with each rule
        for (int j = 0; j < length; j++) {
            
            //if matching with the parametric predacessor
            //check to be sure that the para has a bracket and the right number of variables after it
            if (rules[i].paraPredecessor == substring[j]) {
                if (substring[j+1] == "(") {
                    //cut the currentstring to just this letter and after
                    string truncatedCurrentStr = curString.substr(j, length);
                    
                    //getting the positions of the parentheses and then acquiring the contents between as a string
                    unsigned open = truncatedCurrentStr.find("(");
                    unsigned closed = truncatedCurrentStr.find(")");
                    
                    //pull all the variables from the rule
                    string paraPre = rules[i].paraPredecessor; //A
                    string paraBool = rules[i].parameterBool; //y>3
                    string paraKey = rules[i].parameterKey; //x,y
                    string paraSucc = rules[i].parameterSuccessor; //A(x*2,x+y)
                    
                    string paraValueString = truncatedCurrentStr.substr(open + 1, closed - 2);

                    //check if the contents within brackets has a comma for two values
                    vector<string> splitKey;
                    vector<string> splitValue;
                    
                    if (paraValueString.find(",") != std::string::npos) {
                        //split the key to get two letter x and y
                        splitKey = ofSplitString(paraKey, ",");
//                        cout << splitKey[0] << endl;
//                        cout << splitKey[1] << endl;
                        splitValue = ofSplitString(paraValueString, ",");
//                        cout << splitValue[0] << endl;
//                        cout << splitValue[1] << endl;
                    }else {
                        splitKey.push_back(paraKey);
                        splitValue.push_back(paraValueString);
                    }
                    
                    
                    //for the number of keys, replace the strings in the boolean check
                    for (int m = 0; m < splitKey.size(); m++) {
                        ofStringReplace(paraBool, splitKey[m], splitValue[m]);
                    }
                    
                    bool conditionCheck = parseBoolean(paraBool);

                    if (conditionCheck) {
                        //erase the whole thing including the brackets so it knows the length to remove in the current string
                        int numCharToRemove = closed + 1;
                        for (int k = 0; k < numCharToRemove; k++) {
                            substring.erase(substring.begin() + j);
                        }
                        
                        //for the number of keys, replace the strings in the boolean check
                        for (int m = 0; m < splitKey.size(); m++) {
                            ofStringReplace(paraSucc, splitKey[m], splitValue[m]);
                        }
                        
                        //process the math inside the successor
                        //search for any parenthesis in the successor
                        if (paraSucc.find("(") != std::string::npos && paraSucc.find(")") != std::string::npos) {
                        
                            //Get the bracket position inside the successor
                            string openBracket = "(";
                            string closedBracket = ")";
                            
                            int brackets = count( paraSucc.begin(), paraSucc.end(), '(' ) ; // include algorithm header
//                            cout << "Brackets: " << brackets << endl;
                            
                            //positions of the open brackets
                            vector<size_t> openFound;
                            openFound.push_back(paraSucc.find(openBracket));
//                            if (openFound[0] != string::npos)
//                                cout << "First occurrence is " << openFound[0] << endl;
                            
                            for (int l = 1; l < brackets; l++) {
                                openFound.push_back(paraSucc.find(openBracket, openFound[0] + l));
//                                if (openFound[l] != string::npos)
//                                    cout << "Next occurrence is " << openFound[l] << endl;
                            }
                            
                            //position of closed brackets
                            vector<size_t> closedFound;
                            closedFound.push_back(paraSucc.find(closedBracket));
//                            if (closedFound[0] != string::npos)
//                                cout << "First occurrence is " << closedFound[0] << endl;
                            
                            for (int l = 1; l < brackets; l++) {
                                closedFound.push_back(paraSucc.find(closedBracket, closedFound[0] + l));
//                                if (closedFound[l] != string::npos)
//                                    cout << "Next occurrence is " << closedFound[l] << endl;
                            }
                            
                            //convert the successor to a substring to find the equations
                            vector<string> succSubstring;

                            for(int n = 0; n < paraSucc.length(); n++){
                                succSubstring.push_back(paraSucc.substr(n,1));
                            }
                            
                            vector<string> expressions;
                            for (int l = 0; l < brackets; l++) {
                                string exp;
                                for (int m = openFound[l] + 1; m < closedFound[l]; m++) {
                                    exp += succSubstring[m];
                                }
                                //check if the expression has a comma in it
                                if (exp.find(",") != std::string::npos) {
                                    vector<string> splitExp = ofSplitString(exp, ",");
                                    expressions.push_back(splitExp[0]);
                                    expressions.push_back(splitExp[1]);
//                                    ofLog() << "splitexp 1: " << splitExp[0];
//                                    ofLog() << "splitexp 2: " << splitExp[1];
                                } else {
                                    expressions.push_back(exp);
                                }
                            }
                            
                            //for each of the expressions parse the math in it.
                            for (int n = 0; n < expressions.size(); n++) {
//                                ofLog() << "expression: " << expressions[n];
                                try
                                {
                                    mu::Parser p;
                                    p.SetExpr(expressions[n]);
//                                    std::cout << p.Eval() << std::endl;
                                    string parsedExpression = ofToString(p.Eval());
                                    
                                    ofStringReplace(paraSucc, expressions[n], parsedExpression);
                                }
                                catch (mu::Parser::exception_type &e)
                                {
                                    std::cout << e.GetMsg() << std::endl;
                                }
                            }
//                            ofLog() << paraSucc;
                            substring[j-1] += paraSucc;
                            j += paraSucc.length();

                        } else {
//                            ofLog() << "No Bracket found in successor, continuing...";
                        }
                    }else {
//                        ofLog() << "Boolean check not satisfied, continuing...";
                    }
                  } else {
                    ofLog() << "Parametric rule found but no bracketed value found";
                }
            }
            
            if (rules[i].CSPredecessor == substring[j]) {

                //check the directions
                if(rules[i].CSDirection == "left") {
                    if (rules[i].checkContext(substring[j-1])) {
                        substring[j] = rules[i].CSSuccessor;
                        //after this rule is applied skip over the letters changed
                        j += rules[i].CSSuccessor.length();
                    }
                } else if (rules[i].CSDirection == "right") {
                    if (rules[i].checkContext(substring[j+1])) {
                        substring[j] = rules[i].CSSuccessor;
                        //after this rule is applied skip over the letters changed
                        j += rules[i].CSSuccessor.length();
                    }
                } else {
//                    ofLog() << "Type left or right for context direction";
                }
            } else if (rules[i].predecessor == substring[j]) {
                substring[j] = rules[i].successor;
                j += rules[i].successor.length();

            } else if (rules[i].stochasticPredecessor == substring[j]) {
                string stochSuccessor = rules[i].stochasticProbability();
                substring[j] = stochSuccessor;
                j += stochSuccessor.length();

            }
        }
    }
	
	string result;						// merge into resulting string
	for(int i = 0; i < length; i++){
		result.append(substring[i]);
	}
	curString = result;

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
