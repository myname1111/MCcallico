#include <iostream>
#include <string.h>
extern "C"{
    #include "asm.h"
}
using namespace std;

int main(){
    const char prog[] =
    "STR;"
    "SRG,A,18;"
    "RGRG,B,A;"
    "ADD,C,A,B;"
    "END";
    char* bin = assemble(prog);
    cout << bin << endl;
    int a = 0;
    char HD[1000][25] = {"000000000000000000000000"};
    for (int i = 0;i < 100;i++){
        strcpy(HD[i], "000000000000000000000000");
    }
    for (int i = 0;bin[i] != NULL;i++){
            HD[i / 24][i % 24] = bin[i];
            HD[i / 24][24] = '\0';
    }
    char reg[1000][25] = {"\0"};
    char ram[][25] = {"\0"};
    run(HD, ram, reg, 0);
    return 0;
}
