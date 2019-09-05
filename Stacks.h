#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stack>

#ifndef ASSIGNMENT8_STACKS_H
#define ASSIGNMENT8_STACKS_H

using namespace std;

const int ADD=0;
const int SUBTRACT=1;
const int MULTIPLY=2;
const int DIVIDE=3;
const int MOD=4;
const int AND=5;
const int OR=6;
const int LT=7;
const int LTE=8;
const int E=9;
const int NE=10;
const int GT=11;
const int GTE=12;
const int LN=13; //logical not
const int BN=14; //bitwise not



void evaluateVar();
void setVar();

struct Polish{
    bool isOperand; //true if it's an operand, false if it's an operator
    int value;
    int op; //holds code for what kind of operator this thing is
    Polish(bool myOperand, int myVal, int myOp):isOperand(myOperand), value(myVal), op(myOp){}
};

void num_Out();

void fillVector();

int stackElements();

int stringToOp(string toConvert);

#endif //ASSIGNMENT8_STACKS_H
