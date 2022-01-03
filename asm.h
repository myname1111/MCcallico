#ifndef ASM_H_INCLUDED
#define ASM_H_INCLUDED

extern int scale_size;

void init_asm();

char *assemble(const char asm_prog[]);

char* to_char_arr(const char arr[][25]);

void draw();

int run(char HD[][25], char ram[][25], char reg[][25], int prog);

#endif // ASM_H_INCLUDED
