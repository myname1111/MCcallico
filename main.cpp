#include <iostream>
extern "C"{
    #include "asm.h"
}
using namespace std;
int main(){
    char prog[] =
    "STR;"
    "SRG,A,0;"
    "SRG,B,1;"
    "ADD,C,B,A;"
    "ADD,D,C,B;"
    "ADD,A,D,C;"
    "ADD,B,A,D;"
    "ADD,C,B,A;"
    "ADD,D,C,B;"
    "ADD,A,D,C;"
    "ADD,B,A,D;"
    "ADD,C,B,A;"
    "ADD,D,C,B;"
    "ADD,A,D,C;"
    "ADD,B,A,D;"
    "ADD,C,B,A;"
    "ADD,D,C,B;"
    "ADD,A,D,C;"
    "ADD,B,A,D;"
    "ADD,C,B,A;"
    "ADD,D,C,B;"
    "ADD,A,D,C;"
    "ADD,B,A,D;"
    "ADD,C,B,A;"
    "ADD,D,C,B;"
    "ADD,A,D,C;"
    "ADD,B,A,D;"
    "ADD,C,B,A;"
    "ADD,D,C,B;"
    "ADD,A,D,C;"
    "ADD,B,A,D;"
    "ADD,C,B,A;"
    "ADD,D,C,B;"
    "ADD,A,D,C;"
    "ADD,B,A,D;"
    "END";
    char* bin = assemble(prog);
    cout << bin << endl;
    char* HD = bin;
    char reg[][25] = {"\0"};
    char* ram = "";
    run(HD, ram, reg, 0);
    return 0;
}
