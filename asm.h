#ifndef ASM_H_INCLUDED
#define ASM_H_INCLUDED

char *assemble(char asm_prog[]);

void run(char HD[], char ram[], char reg[][25], int prog);

#endif // ASM_H_INCLUDED
