#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include "Parse.h"
#include "Statements.h"
#include "Stacks.h"


using namespace std;

string myNext;
map<string,int>variables;
map<string,int>::iterator it;
int fToken;
int sToken;
bool nextType; //whether to keep reading or not
stack<int> Stack;
vector<Polish*>elements;
int a;
int b;
int answer;
string myVar;
string mySet;
string mySt;

void num_Out(){
    int numOut;
    mySt=next_token();
    it=variables.find(mySt);
    if(it!=variables.end()) {
        numOut = it->second;
    }
    cout << numOut;
}

void fillVector() {
    string firstOp = next_token();
    //the first element in the vector is the top operand
    elements.push_back(new Polish(false, -1, stringToOp(firstOp)));

    nextType = true;
    while (nextType) {
        myNext = peek_next_token();//TEMPORARY UNTIL I FIGURE OUT HOW TO TERMINATE THE READING WITHOUT MESSING UP SHIT
        if (myNext[0]=='\n'|| (myNext[0] >= 'a' && myNext[0] <= 'z') || (myNext[0] >= 'A' && myNext[0] <= 'Z')) {
            it=variables.find(myNext);
            if(it!=variables.end()){
                read_next_token();
                elements.push_back(new Polish(true, it->second, -1));
            }
            else {
                nextType = false;
            }
        }
        else if (myNext=="//") {
            nextType = false;
        }
        else {
            read_next_token();
            if (next_token_type == NUMBER) {
                int numVal = token_number_value;
                elements.push_back(new Polish(true, numVal, -1));


            } else {
                string nextOp = next_token();
                elements.push_back(new Polish(false, -1, stringToOp(nextOp)));
            }

        }

    }
}

int stackElements(){
    a=0;
    b=0;
    for(int i=elements.size()-1; i>=0; i--){
        if(elements[i]->isOperand){
            Stack.push(elements[i]->value);
        }
        else{ //if it's an operator
            if((elements[i]->op != BN) && (elements[i]->op!=LN)){
                a = Stack.top();
                Stack.pop();
                b = Stack.top();
                Stack.pop();

                switch(elements[i]->op){
                    case ADD: Stack.push(a+b);
                        break;
                    case SUBTRACT: Stack.push(a-b);
                        break;
                    case MULTIPLY: Stack.push(a*b);
                        break;
                    case DIVIDE: Stack.push(a/b);
                        break;
                    case MOD: Stack.push(a%b);
                        break;
                    case AND: if(a!=0 && b!=0){Stack.push(1);}else{Stack.push(0);}
                        break;
                    case OR: if(a!=0 || b!=0){Stack.push(1);}else{Stack.push(0);}
                        break;
                    case LT: if(a<b){Stack.push(1);}else{Stack.push(0);}
                        break;
                    case LTE: if(a<=b){Stack.push(1);}else{Stack.push(0);}
                        break;
                    case GT: if(a>b){Stack.push(1);}else{Stack.push(0);}
                        break;
                    case GTE: if(a>=b){Stack.push(1);}else{Stack.push(0);}
                        break;
                    case E: if(a==b){Stack.push(1);}else{Stack.push(0);}
                        break;
                    case NE: if(a!=b){Stack.push(1);}else{Stack.push(0);}
                        break;

            }
        }
            else{
                a = Stack.top();
                Stack.pop();
                switch(elements[i]->op){
                    case LN: if(a!=0){Stack.push(0);}else{Stack.push(1);}
                        break;
                    case BN: Stack.push(-1*a);
                        break;
                }
            }
        }

    }
    a= Stack.top();
    Stack.pop();
    for(int s=0; s<elements.size(); s++){
        delete(elements[s]);
    }
    elements.clear();
    return a;
}

int stringToOp(string toConvert){
    if(toConvert=="+"){return ADD;}
    if(toConvert=="-"){return SUBTRACT;}
    if(toConvert=="*"){return MULTIPLY;}
    if(toConvert=="/"){return DIVIDE;}
    if(toConvert=="%"){return MOD;}
    if(toConvert=="&&"){return AND;}
    if(toConvert=="||"){return OR;}
    if(toConvert=="<"){return LT;}
    if(toConvert=="<="){return LTE;}
    if(toConvert==">"){return GT;}
    if(toConvert==">="){return GTE;}
    if(toConvert=="=="){return E;}
    if(toConvert=="!="){return NE;}
    if(toConvert=="!"){return LN;}
    if(toConvert=="~"){return BN;}
}

void evaluateVar(){
    read_next_token();
    myVar=next_token();
    it=variables.find(myVar);
    if(it==variables.end()){
        read_next_token();
        if(next_token_type==NUMBER){
            answer=token_number_value;
            variables.insert({myVar,answer});
        }
        else if(next_token_type==SYMBOL){
            fillVector();
            answer=stackElements();
        }
}
    else{
        if(next_token_type==SYMBOL){ //type is SYMBOL
            //cout<<"symbol";
            fillVector();
            answer= stackElements();
            variables[myVar]=answer;
            //cout<<answer;
        }

        else if(next_token_type==NUMBER){
            //cout<<"number";
            answer=token_number_value;
            variables[myVar]=answer; //re-assign variable to the current value
            //also generate error message
        }
        cout<<"variable "<< myVar << " incorrectly re-initialized"<<endl;
    }
    /*
    fToken=0;
    sToken=0;
    read_next_token;
    string myVar = next_token();

    it=variables.find(myVar);
    if(it==variables.end()){
        read_next_token();
        if(next_token_type==NUMBER){sToken=1;}
        else{sToken=2;}
        if(sToken==1){
            answer=token_number_value;
            variables.insert({myVar,answer});
            //
        }
        else{ //type is SYMBOL
            fillVector();
            answer= stackElements();
            variables.insert({myVar,answer});
        }//if th variable is the map

    }
    else{// in the map
        read_next_token();
        if(next_token_type==NUMBER){
            fToken=1;
        }
        else{
            fToken=2;
        }
        if(fToken==1){
            answer=token_number_value;
            it->second=answer; //re-assign variable to the current value
            //also generate error message
        }
        else{ //type is SYMBOL
            fillVector();
            answer= stackElements();
            it->second=answer;
        }

    }
*/
}

void setVar(){
    read_next_token();
    mySet = next_token();

    it=variables.find(mySet);
    read_next_token();
    if(it!=variables.end()){ //if th variable is the map


        if(next_token_type==SYMBOL){ //type is SYMBOL
            //cout<<"symbol";
            fillVector();
            answer= stackElements();
            variables[mySet]=answer;
            //cout<<answer;
        }

        else if(next_token_type==NUMBER){
            //cout<<"number";
            answer=token_number_value;
            variables[mySet]=answer; //re-assign variable to the current value
            //also generate error message
        }
    }
    else{
        if(next_token_type==NUMBER){
            answer=token_number_value;
            variables.insert({mySet,answer});
        }
        else if(next_token_type==SYMBOL){
            fillVector();
            answer=stackElements();
        }
        cout<< "variable "<< mySet<< " not declared"<<endl;
    }
    /*
    else{//not in the map
        read_next_token();
        if(next_token_type==NUMBER){
            answer=token_number_value;
            variables[myVar]=answer;
        }
        else{ //type is SYMBOL
            fillVector();
            answer= stackElements();
            variables[myVar]=answer;
        }
    */
    }




