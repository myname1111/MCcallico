#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* assemble(char asm_prog[]){

    char out_bin[10000];

    char * tok = strtok(asm_prog, ";");
    printf("%d", strcmp(tok, "STR"));
    if (strcmp(tok, "STR") == 0){ // the program shall only assemble if it starts with STR
        strcat(out_bin, "00000");
        while (tok != NULL){ // assemble the rest of the program
            printf(tok);
            if (strcmp(tok, "END")){
                strcat(out_bin, "00001");
            }
            strtok(NULL, ";");
        }
    }



    return out_bin;
}
