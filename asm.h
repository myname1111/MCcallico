#ifndef ASM_H_INCLUDED
#define ASM_H_INCLUDED

char *assemble(const char asm_prog[]);

char* to_char_arr(char arr[][25]);

void run(char HD[][25], char ram[][25], char reg[][25], int prog);

#endif // ASM_H_INCLUDED
