#include <iostream>
extern "C"{
    #include "asm.h"
}
using namespace std;
int main(){
    char prog[] =
    "STR;"
    "SRM,0,0;"
    "END";
    char* bin = assemble(prog);
    cout << bin << endl;
    char* HD = bin;
    char reg[][25] = {"\0"};
    char* ram = "";
    run(HD, ram, reg, 0);
    return 0;
}
