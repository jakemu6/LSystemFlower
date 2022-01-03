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
    int leng = curString.length();
    vector <string> curStringVec;
    for(int i = 0; i < leng; i++){
        curStringVec.push_back(curString.substr(i,1));

    }
    
    //ATTEMPT 3
    //record all the rules and booleans
    vector<string> predecessors;
    vector<string> paraBools;
    vector<string> paraKey;
    vector<string> paraSuccs;


    for (int i = 0; i < rules.size(); i++) {
        
        //for the parametric rules
        if (rules[i].ruleType == "parametric") {
            predecessors.push_back(rules[i].paraPredecessor);
            paraBools.push_back(rules[i].parameterBool);
            paraKey.push_back(rules[i].parameterKey);
            paraSuccs.push_back(rules[i].parameterSuccessor);
        } else {
            predecessors.push_back("NO PREDECESSOR EXISTING");
            paraBools.push_back("NO RULE EXISTING");
            paraKey.push_back("NO KEY EXISTING");
            paraSuccs.push_back("NO SUCCESSOR EXISTING");
        }
    }
    

        
    //record the position of where each of the edits are to take place along the string.
    vector<stringEdit> edits;

    for (int i = 0; i < predecessors.size(); i++) {
        for (int j = 0; j < curStringVec.size(); j++) {
            
            //check if the predeccessors match the string
            if (predecessors[i] == curStringVec[j]) {
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
                    
//                    cout << splitKey[1] << endl;
//                        cout << splitValue[0] << endl;
//                        cout << splitValue[1] << endl;
                }else {
                    splitKey.push_back(paraKey[i]);
                    splitValue.push_back(paraValueString);
                }
                
                string boolCheck = paraBools[i];
                
                for (int k = 0; k < splitKey.size(); k++) {

                    ofStringReplace(boolCheck, splitKey[k], splitValue[k]);
//                    cout << "BOOL: " << boolCheck << "   KEY: " << splitKey[k] << "   VALUE: " << splitValue[k] <<  endl;

                }

                bool conditionCheck = parseBoolean(boolCheck);
                
//                ofLog() << paraSuccs[i];
//                ofLog() << paraValueString;
                if (conditionCheck) {
                    

                    
                    //                    //for the number of keys, replace the strings in the boolean check
                    //                    for (int k = 0; k < splitKey.size(); k++) {
                    //                        ofStringReplace(paraSucc, splitKey[k], splitValue[k]);
                    //                    }
                    string successor = paraSuccs[i];

                    
                    for (int k = 0; k < splitKey.size(); k++) {
//                        ofStringReplace(paraSuccs[i], splitKey[k], splitValue[k]);
                        ofStringReplace(successor, splitKey[k], splitValue[k]);

                    }
                    
//                    ofLog() << successor;
                    
                    if (successor.find("(") != std::string::npos && successor.find(")") != std::string::npos) {
                        
                        //find locations of a character in a string for the brackets
                        //currently only uses positioning to tell.
                        //Can not use bracket inside bracket yet.
                        vector<int> openLocations;
                        for (int k = 0; k < successor.size(); k++) {
                            if(successor[k] == '(') {
                                openLocations.push_back(k);
                            }
                        }
                        vector<int> closedLocations;
                        for (int k = 0; k < successor.size(); k++) {
                            if(successor[k] == ')') {
                                closedLocations.push_back(k);
                            }
                        }
                        
                        //convert the successor to a substring to find the equations
                        vector<string> succSubstring;
                        for(int k = 0; k < successor.size(); k++){
                            succSubstring.push_back(successor.substr(k,1));
                        }

//                            for (const string &i: succSubstring) {
//                                std::cout << i << "";
//                            }
//                                std::cout << "\n";
//
                        //create a vector to contain all of the expressions that need to be done
                        //Currently accomodates only two expressions per bracket max
                        vector<string> expressions;
                        for (int k = 0; k < openLocations.size(); k++) {
//                            ofLog() << "open: " << openLocations[k] << "    closed: " << closedLocations[k];
                            
                            string exp;
                            for (int l = openLocations[k] + 1; l < closedLocations[k]; l++) {
                                exp += succSubstring[l];
                            }
//                            ofLog() << exp;

                            
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
                        //then replace the string in the paraSucc
                        for (int k = 0; k < expressions.size(); k++) {
//                                ofLog() << "expression: " << expressions[n];
                            try
                            {
                                mu::Parser p;
                                p.SetExpr(expressions[k]);
//                                std::cout << p.Eval() << std::endl;
                                string parsedExpression = ofToString(p.Eval());

                                ofStringReplace(successor, expressions[k], parsedExpression);
                            }
                            catch (mu::Parser::exception_type &e)
                            {
                                std::cout << e.GetMsg() << std::endl;
                            }
                        }

                        
                    }

//
//                    //process the math inside the successor
//                    //search for any parenthesis in the successor
//                    if (paraSucc.find("(") != std::string::npos && paraSucc.find(")") != std::string::npos) {
//
//                        vector<int> openLocations;
//                        //find locations of a character in a string for the brackets
//                        for (int l = 0; l < paraSucc.size(); l++) {
//                            if(paraSucc[l] == openB) {
//                                openLocations.push_back(l);
//                            }
//                        }
//
//
//                        vector<int> closedLocations;
//                        //find locations of a character in a string for the brackets
//                        for (int l = 0; l < paraSucc.size(); l++) {
//                            if(paraSucc[l] == closedB) {
//                                closedLocations.push_back(l);
//                            }
//                        }
//
//                        //convert the successor to a substring to find the equations
//                        vector<string> succSubstring;
//
//                        for(int l = 0; l < paraSucc.length(); l++){
//                            succSubstring.push_back(paraSucc.substr(l,1));
//                        }
//
//                        //create a vector to contain all of the expressions that need to be done
//                        //Currently accomodates only two expressions per bracket max
//                        vector<string> expressions;
//                        for (int l = 0; l < openLocations.size(); l++) {
//                            string exp;
//                            for (int m = openLocations[l] + 1; m < closedLocations[l]; m++) {
//                                exp += succSubstring[m];
//                            }
//                            //check if the expression has a comma in it
//                            if (exp.find(",") != std::string::npos) {
//                                vector<string> splitExp = ofSplitString(exp, ",");
//                                expressions.push_back(splitExp[0]);
//                                expressions.push_back(splitExp[1]);
////                                    ofLog() << "splitexp 1: " << splitExp[0];
////                                    ofLog() << "splitexp 2: " << splitExp[1];
//                            } else {
//                                expressions.push_back(exp);
//                            }
//                        }
//
//                        //for each of the expressions parse the math in it.
//                        //then replace the string in the paraSucc
//                        for (int n = 0; n < expressions.size(); n++) {
////                                ofLog() << "expression: " << expressions[n];
//                            try
//                            {
//                                mu::Parser p;
//                                p.SetExpr(expressions[n]);
////                                    std::cout << p.Eval() << std::endl;
//                                string parsedExpression = ofToString(p.Eval());
//
//                                ofStringReplace(paraSucc, expressions[n], parsedExpression);
//                            }
//                            catch (mu::Parser::exception_type &e)
//                            {
//                                std::cout << e.GetMsg() << std::endl;
//                            }
//                        }
//                    ofLog() << paraSuccs[i];
                    
                    stringEdit tempEdit;
                    tempEdit.setup(j, successor, closed);
                    edits.push_back(tempEdit);
                }
            }
        }
    }
    
    ofSort(edits, &sortMe);
    
//    std::cout << "after ofSort()" << std::endl;
//    for (auto & obj : edits) {
//        std::cout << obj.position << " " << obj.rule << std::endl;
//    }

//    std::vector<string> result(curStringVec.begin(), curStringVec.end());
//
//    //Make changes to the string starting from the end of the string to avoid messing with the order
//    std::list<string> dest(curStringVec.begin(), curStringVec.end());

    
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
    
    
//    list<string>::iterator it2 = dest.begin();
    
    // iterator to point to j position
//    advance(it2,j);
//                            dest.insert(it2,"Q");
    
//                            auto it = substring.emplace ( substring.begin()+j, "HI" );

    
//                            //VECTOR
//                            for (string i: substring)
//                                std::cout << i;
//                                std::cout << "\n";
    
//    for (const string &i: curStringVec) {
//        std::cout << i << "";
//    }
//        std::cout << "\n";
    

    
    
    
    
    //ATTEMPT 3 ENDS HERE
    
	int length = curString.length();	// length of the current string
    vector <string> substring;
//    list <string> sub;
	
    for(int i = 0; i < length; i++){
        substring.push_back(curString.substr(i,1));
//        sub.push_back(curString.substr(i,1));
	}
    
//THIS IS BY RULE FIRST
    //start with first rule
    for (int i = 0; i < rules.size(); i++) {
        
    //go through each letter with each rule
        
        
        
//        //using iterator
//        vector<string>::iterator it; // iterator points to first element
//
//        it = substring.insert ( substring.begin() , "c" );
//        it = substring.begin();
//
//
//        for (it = substring.begin(); it < substring.end(); it++) {
//
//            //If there is a match between rule and predecessor
//            if (*it == rules[i].paraPredecessor) {
//                //and if there is a bracket directly after the match
//                string openBracket = "(";
//                string closedBracket = ")";
//
//                advance(it, 1);
//                if (*it == openBracket) {
//
//                    string paraPre = rules[i].paraPredecessor; //A
//                    string paraBool = rules[i].parameterBool; //y>3
//                    string paraKey = rules[i].parameterKey; //x,y
//                    string paraSucc = rules[i].parameterSuccessor; //A(x*2,x+y)
//
//
////                    std::cout << ' ' << substring.at(i);
//
//
//
//
//                    //distance from the beginning to iterator position
//                    int dist = distance(substring.begin(), it);
//
//                    //make the truncated string because this is only to find reference points of where brackets go
//                    string truncatedCurrentStr = curString.substr(dist, length);
//                    unsigned open = truncatedCurrentStr.find("(");
//                    unsigned closed = truncatedCurrentStr.find(")");
//
//                    string paraValueString = truncatedCurrentStr.substr(open + 1, closed - 1);
//
//                    //check if the contents within brackets has a comma for two values
//                    vector<string> splitKey;
//                    vector<string> splitValue;
//
//                    if (paraValueString.find(",") != std::string::npos) {
//                        //split the key to get two letter x and y
//                        splitKey = ofSplitString(paraKey, ",");
////                        cout << splitKey[0] << endl;
////                        cout << splitKey[1] << endl;
//                        splitValue = ofSplitString(paraValueString, ",");
////                        cout << "The key: " << splitKey[0] << "  corresponds to: " << splitValue[0] << endl;
////                        cout << "The key: " << splitKey[1] << "  corresponds to: " << splitValue[1] << endl;
//                    }else {
//                        splitKey.push_back(paraKey);
//                        splitValue.push_back(paraValueString);
//                    }
//
//                    //for the number of keys, replace the strings in the boolean check
//                    for (int m = 0; m < splitKey.size(); m++) {
//                        ofStringReplace(paraBool, splitKey[m], splitValue[m]);
//                    }
//
//                    bool conditionCheck = parseBoolean(paraBool);
//
////                    cout << paraBool << " has beem checked: " << conditionCheck << endl;
//                    if (conditionCheck) {
//
//                        //remove the strings in the substring Doing this later!!!!
//////                        auto it1 = next(it, 1);
////////                         Displaying iterator position
//////                        cout << "The position of new iterator using prev()  is : ";
//////                        cout << *it1 << " ";
//////                        cout << endl;
////
////                        if (it == substring.begin() + 1) {
////                            it = substring.erase(it);
////                             // i now points to the element after the
////                             // deleted element
////                         }
//
//                        //replaces the keys in the successor
//                        for (int m = 0; m < splitKey.size(); m++) {
//                            ofStringReplace(paraSucc, splitKey[m], splitValue[m]);
//                        }
//
//                        //process the math inside the successor
//                        //search for any parenthesis in the successor
//                        if (paraSucc.find("(") != std::string::npos && paraSucc.find(")") != std::string::npos) {
//
//                            vector<int> openLocations;
//                            //find locations of a character in a string for the brackets
//                            for (int n = 0; n < paraSucc.size(); n++) {
//                                if(paraSucc[n] == '(') {
//                                    openLocations.push_back(n);
//                                }
//                            }
//
//                            vector<int> closedLocations;
//                            //find locations of a character in a string for the brackets
//                            for (int n = 0; n < paraSucc.size(); n++) {
//                                if(paraSucc[n] == ')') {
//                                    closedLocations.push_back(n);
//                                }
//                            }
//
//                            //convert the successor to a substring to find the equations
//                            vector<string> succSubstring;
//
//                            for(int n = 0; n < paraSucc.length(); n++){
//                                succSubstring.push_back(paraSucc.substr(n,1));
//                            }
//
//                            vector<string> expressions;
//                            for (int l = 0; l < openLocations.size(); l++) {
//                                string exp;
//                                for (int m = openLocations[l] + 1; m < closedLocations[l]; m++) {
//                                    exp += succSubstring[m];
//                                }
//                                //check if the expression has a comma in it
//                                if (exp.find(",") != std::string::npos) {
//                                    vector<string> splitExp = ofSplitString(exp, ",");
//                                    expressions.push_back(splitExp[0]);
//                                    expressions.push_back(splitExp[1]);
////                                    ofLog() << "splitexp 1: " << splitExp[0];
////                                    ofLog() << "splitexp 2: " << splitExp[1];
//                                } else {
//                                    expressions.push_back(exp);
//                                }
//                            }
//
//                            //for each of the expressions parse the math in it.
//                            for (int n = 0; n < expressions.size(); n++) {
////                                ofLog() << "expression: " << expressions[n];
//                                try
//                                {
//                                    mu::Parser p;
//                                    p.SetExpr(expressions[n]);
////                                    std::cout << p.Eval() << std::endl;
//                                    string parsedExpression = ofToString(p.Eval());
//
//                                    ofStringReplace(paraSucc, expressions[n], parsedExpression);
//                                }
//                                catch (mu::Parser::exception_type &e)
//                                {
////                                    std::cout << e.GetMsg() << std::endl;
//                                }
//                            }
//
////                            ofLog() << paraSucc;
//                            //turn the paraSucc into a vector
//                            int length = paraSucc.length();    // length of the current string
//                            vector<string> succVec;
//                            for(int i = 0; i < length; i++){
//                                succVec.push_back(paraSucc.substr(i,1));
//                            }
//
//
//
////                            substring[j-1] += paraSucc;
//                        } else {
//                            ofLog() << "No brackets have been found in the successor continue!. This is not an error...yet";
//                        }
//                        //END OF THE IF THE SUCCESSOR HAD BRACKETS
//                    } else {
////                        ofLog() << "condition of bool has not been met. This is not an error...yet";
//                    }
//                    //END OF THE CONDITION CHECK
//
//
//                } else {
//                    ofLog() << "No bracket found after a parametric predecessor";
//                }
//            }
//
//        }
//        //ENDING HERE

        //LISTS
//        //if matching with the parametric predacessor
//        //check to be sure that the para has a bracket and the right number of variables after it
//        auto it = std::find(sub.begin(), sub.end(), rules[i].paraPredecessor);
//        if (it != sub.end()) {
//            sub.insert(it, "HI");
//        }
//
//        // Print out the list
//        std::cout << "sub = { ";
//        for (string n : sub) {
//            std::cout << n << " ";
//        }
//        std::cout << "};\n";
        
        
        for (int j = 0; j < length; j++) {

            
            
            if (rules[i].paraPredecessor == substring[j]) {
                
                
                //this will also need to later check if there are the right number of commas inside the parentheses
                if (substring[j+1] == "(") {

//                    cout << "matched at " << j << endl;

                    
                    //cut the currentstring to just this letter and after
                    string truncatedCurrentStr = curString.substr(j, length);
                    
                    //Bracket as a string to find in successor and predecessors
                    string openBracket = "(";
                    string closedBracket = ")";
                    

                    
                    char openB = '(';
                    char closedB = ')';


                    //getting the positions of the parentheses and then acquiring the contents between as a string in the cut substring
                    unsigned open = truncatedCurrentStr.find("(");
                    unsigned closed = truncatedCurrentStr.find(")");
                    
//                    //find the positions in the substring instead of truncated and then in the erase reference both the open and close
//                    //it will need to be open - 1 == j too to only remove the first
//                    vector<int> openSubs;
//                    //find locations of a character in a string for the brackets
//                    for (int n = 0; n < substring.size(); n++) {
//                        if(substring[n] == openBracket) {
//                            openSubs.push_back(n);
//                        }
//                    }
//
//
//                    vector<int> closedSubs;
//                    //find locations of a character in a string for the brackets
//                    for (int n = 0; n < substring.size(); n++) {
//                        if(substring[n] == closedBracket) {
//                            closedSubs.push_back(n);
//                        }
//                    }

                    
                    //pull all the variables from the rule
                    string paraPre = rules[i].paraPredecessor; //A
                    string paraBool = rules[i].parameterBool; //y>3
                    string paraKey = rules[i].parameterKey; //x,y
                    string paraSucc = rules[i].parameterSuccessor; //A(x*2,x+y)
                    
//                    cout << "  string: " << truncatedCurrentStr << "  bool: " << paraBool << endl;

                    
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
                    
//                    cout << paraPre << " at: " << truncatedCurrentStr << "   closed: " << closed << "   j: " << j << "   bool: " << paraBool << endl;
                    //VECTOR
//                    for (string i: substring)
//                        std::cout << i;
//                        std::cout << "\n";

                    //for the number of keys, replace the strings in the boolean check
                    for (int k = 0; k < splitKey.size(); k++) {
                        ofStringReplace(paraBool, splitKey[k], splitValue[k]);
                    }

                    bool conditionCheck = parseBoolean(paraBool);

//                    cout << paraBool << endl;

                    
                    if (conditionCheck) {
                        
//                        cout << "BOOL PASSED" << endl;
                        
                        //for the number of keys, replace the strings in the boolean check
                        for (int k = 0; k < splitKey.size(); k++) {
                            ofStringReplace(paraSucc, splitKey[k], splitValue[k]);
                        }
                        
                        //process the math inside the successor
                        //search for any parenthesis in the successor
                        if (paraSucc.find("(") != std::string::npos && paraSucc.find(")") != std::string::npos) {
                        
                            vector<int> openLocations;
                            //find locations of a character in a string for the brackets
                            for (int l = 0; l < paraSucc.size(); l++) {
                                if(paraSucc[l] == openB) {
                                    openLocations.push_back(l);
                                }
                            }


                            vector<int> closedLocations;
                            //find locations of a character in a string for the brackets
                            for (int l = 0; l < paraSucc.size(); l++) {
                                if(paraSucc[l] == closedB) {
                                    closedLocations.push_back(l);
                                }
                            }
                            
                            //convert the successor to a substring to find the equations
                            vector<string> succSubstring;

                            for(int l = 0; l < paraSucc.length(); l++){
                                succSubstring.push_back(paraSucc.substr(l,1));
                            }
                            
                            //create a vector to contain all of the expressions that need to be done
                            //Currently accomodates only two expressions per bracket max
                            vector<string> expressions;
                            for (int l = 0; l < openLocations.size(); l++) {
                                string exp;
                                for (int m = openLocations[l] + 1; m < closedLocations[l]; m++) {
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
                            //then replace the string in the paraSucc
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
                        }
                        
//                        // Print out the list
//                        std::cout << "substring = { ";
//                        for (string n : substring) {
//                            std::cout << n << "";
//                        }
//                        std::cout << "};\n";
                        
                        //this is a list of the substring
                        //using iterators to delete the original detected string in the list only
                        //list is called as dest
                        std::list<string> dest(substring.begin(), substring.end());
//                        for (const string &i: dest) {
//                            std::cout << i << "";
//                        }
//                            std::cout << "};\n";
                        
//                        list<string>::iterator it = dest.begin();
//                        list<string>::iterator it1 = dest.begin();
//
//                        advance(it,j);
//                        advance(it1,j + closed+1);
//
//                        dest.erase(it,it1);
                        

//                        for (const string &i: dest) {
//                            std::cout << i << "";
//                        }
//                            std::cout << "};\n";

//                        cout << paraPre << " at: " << j << endl;

//                        cout << substring.size() << endl;

                        
//                        string curr;
//                        for (int n = 0; n < substring.size(); n++) {
//                            curr += substring[n];
//                        }
//                        cout << curr << endl;
//                        cout << open << endl;
//                        cout << closed << endl;

//                        int openB = j+1; //position of the open brackets
//                        cout << "openB: "<< openB << endl;

                        
//                        // Stack to store opening brackets.
//                        stack <string> st;
//
//
//                        int close;
//                        //check the stack if the close bracket is the corresponding bracket.
//                        for (int n = j+1; n < substring.size(); n++) {
//////                            cout << n << endl;
//                            if (substring[n] == openBracket) {
//                                st.push(substring[n]);
//
//                            } else if (substring[n] == closedBracket) {
//                                st.pop();
//                                if (st.empty()) {
//                                    close = n;
////                                    cout << j+1 << ": " << close << "\n";
//                                }
//                            }
//                        }
//
//
//
//                        cout << "index: " << index << endl;
//                        cout << "close: " << close << endl;

//                        int numCharToRemove = closed;
//                        for (int k = 0; k < numCharToRemove; k++) {
//                            substring.erase(substring.begin() + j);
//                        }
//
//                        vector<string>::iterator it = substring.begin() + j; // iterator points to first element
////
////                        for(; it != substring.end() ;){
////
//                        while( it != substring.begin() + j + closed ){
//                            cout << *it << endl;
//                         ++it;
//                        }
//
//
//                        cout << *it << endl;
//
//                        for (int n = j; n < j + closed + 1; n++) {
//                            cout << substring[n] << endl;
//                        }
                        
//                        vector<string>::iterator it = substring.begin() + j; // iterator points to first element
//
//                        for(; it != substring.begin() + j + 3;){
//                            it = substring.erase(it); // be sure to return the iterator when erasing so it is not invalidated
//                            ++it;
//                        }

//
//                        vector<int> openSubs;
//                        //find locations of a character in a string for the brackets
//                        for (int n = 0; n < substring.size(); n++) {
//                            if(substring[n] == openBracket) {
//                                openSubs.push_back(n);
//                            }
//                        }
//
//
//                        vector<int> closedSubs;
//                        //find locations of a character in a string for the brackets
//                        for (int n = 0; n < substring.size(); n++) {
//                            if(substring[n] == closedBracket) {
//                                closedSubs.push_back(n);
//                            }
//                        }
////                        cout << substring << endl;
//                        cout << "open 0: " << openSubs[0] << "  closed 0: " << closedSubs[0] << endl;
//                        cout << "open 1: " << openSubs[1] << "  closed 1: " << closedSubs[1] << endl;
//                        substring.erase(substring.begin() + j);


//                        substring.erase(
//                            std::remove_if(
//                               substring.begin(),
//                               substring.end(),
//                                [](IInventory* element) -> bool {
//                                    // Do "some stuff", then return true if element should be removed.
//                                    return true;
//                                }
//                            ),
//                            substring.end()
//                        );
//                        for (int m = 0; m < openSubs.size(); m++) {
//                            cout << "j: " << j << "  open: " << openSubs[m] << "  close: " << closedSubs[m] << endl;
//                            if (j == openSubs[m] - 1) {
////                                cout << "winner winner chicken dinner: " << openSubs[m] - closedSubs[m] << endl;
//                                substring.erase( substring.begin() + openSubs[m], substring.begin() + closedSubs[m]);
//                            }
//                        }

//                        int numCharToRemove = closed + 1;
//                        for (int k = 0; k < numCharToRemove; k++) {
//                            substring.erase(substring.begin() + j);
////                            substring++;
//                        }
                        
//                        vector<string>::iterator it = substring.begin() + j; // iterator points to first element
//
//                        for(; it != substring.end();){
//                            if( *it == "(" ) it = substring.erase(it); // be sure to return the iterator when erasing so it is not invalidated
//                            else ++it;
//                        }


                        for (int m = 0; m < splitKey.size(); m++) {
//                            cout << "before: " << paraSucc << endl;

                            ofStringReplace(paraSucc, splitKey[m], splitValue[m]);
//                            cout << "after: " << paraSucc << endl;

                        }
                           
                        
                        //process the math inside the successor
                        //search for any parenthesis in the successor
                        if (paraSucc.find("(") != std::string::npos && paraSucc.find(")") != std::string::npos) {
                        
                            vector<int> openLocations;
                            //find locations of a character in a string for the brackets
                            for (int n = 0; n < paraSucc.size(); n++) {
                                if(paraSucc[n] == openB) {
                                    openLocations.push_back(n);
                                }
                            }


                            vector<int> closedLocations;
                            //find locations of a character in a string for the brackets
                            for (int n = 0; n < paraSucc.size(); n++) {
                                if(paraSucc[n] == closedB) {
                                    closedLocations.push_back(n);
                                }
                            }
//                            cout << paraSucc << endl;
//                            cout << "open 0: " << openLocations[0] << "  closed 0: " << closedLocations[0] << endl;
//                            cout << "open 1: " << openLocations[1] << "  closed 1: " << closedLocations[1] << endl;
                            
                            
//                            int brackets = count( paraSucc.begin(), paraSucc.end(), '(' ) ; // include algorithm header
////                            cout << "Brackets: " << brackets << endl;
//
//                            //positions of the open brackets
//                            vector<size_t> openFound;
//                            openFound.push_back(paraSucc.find(openBracket));
////                            if (openFound[0] != string::npos)
////                                cout << "First occurrence is " << openFound[0] << endl;
//
//                            for (int l = 1; l < brackets; l++) {
//                                openFound.push_back(paraSucc.find(openBracket, openFound[0] + l));
////                                if (openFound[l] != string::npos)
////                                    cout << "Next occurrence is " << openFound[l] << endl;
//                            }
//
//                            //position of closed brackets
//                            vector<size_t> closedFound;
//                            closedFound.push_back(paraSucc.find(closedBracket));
////                            if (closedFound[0] != string::npos)
////                                cout << "First occurrence is " << closedFound[0] << endl;
//
//                            for (int l = 1; l < brackets; l++) {
//                                closedFound.push_back(paraSucc.find(closedBracket, closedFound[0] + l));
////                                if (closedFound[l] != string::npos)
////                                    cout << "Next occurrence is " << closedFound[l] << endl;
//                            }
                            


                            //convert the successor to a substring to find the equations
                            vector<string> succSubstring;

                            for(int n = 0; n < paraSucc.length(); n++){
                                succSubstring.push_back(paraSucc.substr(n,1));
                            }
                            
                            vector<string> expressions;
                            for (int l = 0; l < openLocations.size(); l++) {
                                string exp;
                                for (int m = openLocations[l] + 1; m < closedLocations[l]; m++) {
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
//                                    std::cout << e.GetMsg() << std::endl;
                                }
                            }

                            list<string>::iterator it2 = dest.begin();
                            
                            // iterator to point to j position
                            advance(it2,j);
//                            dest.insert(it2,"Q");
                            
//                            auto it = substring.emplace ( substring.begin()+j, "HI" );

                            
//                            //VECTOR
//                            for (string i: substring)
//                                std::cout << i;
//                                std::cout << "\n";
                            
                            
//                            substring.clear();
                            
//                            for (int k = 0; k < paraSucc.length(); k++) {
//                                j++;
//                            }

                            
////                            vector<string> result;
//                            for (string const &c: dest) {
//                                substring.push_back(c);
////                                ofLog() << c;
//                            }
                            


                            
//                            //LIST
//                            for (const string &i: dest) {
//                                std::cout << i;
//                                std::cout << "\n";
//                            }


//
                            
//                            substring.insert(substring.end(), result.begin(), result.end());
                            
//                            ofLog() << paraSucc;
//                            substring[j-1] += paraSucc;
                            

//
//                            j += paraSucc.length();

                        } else {
//                            ofLog() << "No Bracket found in successor, continuing...";
                            substring[j-1] += paraSucc;
//                            j += paraSucc.length();
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


