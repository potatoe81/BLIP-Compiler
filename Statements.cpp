#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include "Parse.h"
#include "Statements.h"
#include "Stacks.h"


using namespace std;
Stmt* new_Statement = new Stmt;


Stmt* readStmt(){
    read_next_token();
    if(next_token_type==END){
            new_Statement->type=FIN;
            //cout<<"end"<<endl;
    }
    if(next_token_type==NAME){
        string statementType=next_token();
        if(statementType=="var"){
            new_Statement->type=VAR;
            //cout<<"var";
        }
        if(statementType=="set"){
            new_Statement->type=SET;
            //cout<<"set";
        }
        if(statementType=="text"){
            new_Statement->type=TEXT;
            //cout<<"text";
        }
        if(statementType=="output"){
            new_Statement->type=OUTPUT;
            //cout<<"output";
        }
    }
    if(next_token_type==SYMBOL){
        string newSymbol=next_token();
        if(newSymbol=="//"){
            new_Statement->type=COMMENT;
        }
    }
    return new_Statement;


}

bool executeStmt(Stmt*my_Stmt){
    if(my_Stmt->type==FIN){
        return false;
    }
    if(my_Stmt->type==COMMENT){
        skip_line();
        return true;
    }
    if(my_Stmt->type==TEXT){
        displayText();
        return true;
    }
    if(my_Stmt->type==OUTPUT){
        displayNum();
        return true;
    }
    if(my_Stmt->type==VAR){
        evaluateVar();
        return true;
    }
    if(my_Stmt->type==SET){
        setVar();
        return true;
    }
}

void displayText(){//if statement is of type text
    read_next_token();
    string textToDisplay=next_token();
    cout<<textToDisplay;

}

void displayNum(){//used to display the result of a stack operation for output
    read_next_token();
    if(next_token_type==NAME){
        num_Out();
    }
    else if(next_token_type==NUMBER) {
        int numToDisplay = token_number_value;
        cout << numToDisplay;
    }
    else if(next_token_type==SYMBOL){ //some kind of expression
        fillVector();
        int answer = stackElements();
        cout << answer;
    }
}



