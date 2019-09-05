#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "Input.cpp"
#include "Statements.h"


const char* test1 = "test1.blip";
const char* test2 = "test2.blip";
const char* test3 = "test3.blip";
const char* test4 = "test4.blip";
bool GO_ON;
using namespace std;


void run(){
    GO_ON=true;
    while(GO_ON) {
        GO_ON=executeStmt(readStmt());

    }
}

int main() {

    set_input("test_grader.blip");
    run();

}