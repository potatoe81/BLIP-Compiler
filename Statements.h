#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stack>

#ifndef ASSIGNMENT8_STATEMENTS_H
#define ASSIGNMENT8_STATEMENTS_H

using namespace std;


const int FIN = -1;
const int VAR = 0;
const int SET = 1;
const int TEXT = 2;
const int OUTPUT = 3;

const int COMMENT=4;

struct Stmt{
    int type;
    string target; //if type is set or var
    int result; //result of evaluated expression, if any
};

Stmt* readStmt();
bool executeStmt(Stmt*my_Stmt);
void displayText();
void displayNum();

#endif //ASSIGNMENT8_STATEMENTS_H
