#include <stdio.h>
#include <stdlib.h>
#include "asm.h"

int main(){
    char prog[] = "STR;END";
    printf("%s", assemble(prog));
    return 0;
}
