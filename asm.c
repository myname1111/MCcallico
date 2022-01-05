#include "asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>

char draw_table[36864];
int draw_used = 0;
int scale_size = 7;

struct Dict{
    char* key;
    int val;
};

void draw_to_out(char in_str[]){
    if (draw_used == 36864){
        draw_used = 0;
    }
    for (int i = draw_used;(i - draw_used) < strlen(in_str);i++){
        draw_table[i] = in_str[i - draw_used];
    }
    draw_used += 24;
}

void init_asm(){
    for (int i = 0;i < sizeof(draw_table) / sizeof(draw_table[0]);i++){
        draw_table[i] = '0';
    }
}

char* reg2bin(char reg[10]){
    char* out = "";
    switch(reg[0]){
        case 'A':
            out = "00";
            break;
        case 'B':
            out = "01";
            break;
        case 'C':
            out = "10";
            break;
        case 'D':
            out = "11";
            break;
        default:
            printf("ERROR UKNOWN REGISTER '%s'\n", reg);
    }
    return out;
}

int bin2dec(char* n){
    return strtol(n, NULL, 2);
}

char* dec2binr(char num[]){
    char out[1000] = "";
    char* output = malloc(10000);
    if (strcmp(num, "0") == 0){
        strcpy(out, "0");
    }
    else if (strcmp(num, "1") == 0){
        strcpy(out, "1");
    }
    else {
        char digit[1000] = "";
        char new_in[1000] = "";
        sprintf(digit, "%d", atoi(num) % 2);
        sprintf(new_in, "%d", atoi(num) / 2);
        strcat(out, digit);
        strcat(out, dec2binr(new_in));
    }
    strcpy(output, out);
    return output;
}

char* strmul(char x, int times){
    char* out = malloc(10000);
    char output[times+1];
    memset(output, x, times);
    output[times] = '\0';
    strcpy(out, output);
    return out;
}

char* dec2bin(char num[]){
    char bin[10000] = "";
    char* out = malloc(10000 * sizeof(char));
    strcat(bin, dec2binr(num));
    strcat(bin, strmul('0', 24 - strlen(bin)));
    strrev(bin);
    strcpy(out, bin);
    return out;
}

char* strsplice(char str[], int from, int to){
    char* t_out = malloc(100000);
    char out[(to-from) + 1];
    memset(out, '\0', (to-from));
    for (int i = 0; i <= to-1;i++){
        if (i >= from){
            out[i - from] = str[i];
        }
    }
    out[to-from] = '\0';
    strcpy(t_out, out);
    return t_out;
}

char* assemble(const char asm_prog[]){
    char lines[10000][100];
    char* bin = malloc(100000);
    char out[100000];

    char* token;
    token = strtok(asm_prog, ";");
    for (int i = 0;token != NULL;i++) {
        strcpy(lines[i], token);
        token = strtok(NULL, ";");
    }
    free(token);

    struct Dict jump_point[10000] = {{.key = NULL, .val=NULL}};
    int jump_point_len = 0;


    for (int i = 0;strcmp(lines[i], "\0") != 0;i++){
        char insts[10][20];
        char* tok;
        tok = strtok(lines[i], ",");
        for(int k = 0;tok != NULL;k++){
            strcpy(insts[k], tok);
            tok = strtok(NULL, ",");
        }
        if (insts[0][strlen(insts[0])-1] == ':'){
                jump_point[jump_point_len].key = strsplice(insts[0], 0, strlen(insts[0]) - 1);
                jump_point[jump_point_len].val = i;
                jump_point_len++;
        }
        else if (strcmp(insts[0], "STR") == 0){
            strcat(out, "00000");
        }
        else if (strcmp(insts[0], "END") == 0){
            strcat(out, "00001");
        }
        else if (strcmp(insts[0], "ADD") == 0){
            strcat(out, "00010");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "SUB") == 0){
            strcat(out, "00011");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "MUL") == 0){
            strcat(out, "00100");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "DIV") == 0){
            strcat(out, "00101");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "AND") == 0){
            strcat(out, "00110");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "OR") == 0){
            strcat(out, "00111");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "XOR") == 0){
            strcat(out, "01000");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "NAND") == 0){
            strcat(out, "01001");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "NOR") == 0){
            strcat(out, "01010");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "XNOR") == 0){
            strcat(out, "01011");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "SRG") == 0){
            strcat(out, "01100");
            strcat(out, reg2bin(insts[1]));
            strcat(out, dec2bin(insts[2]));
        }
        else if (strcmp(insts[0], "SRM") == 0){
            strcat(out, "01101");
            strcat(out, dec2bin(insts[1]));
            strcat(out, dec2bin(insts[2]));
        }
        else if (strcmp(insts[0], "RGRG") == 0){
            strcat(out, "01110");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
        }
        else if (strcmp(insts[0], "RMRM") == 0){
            strcat(out, "01111");
            strcat(out, dec2bin(insts[1]));
            strcat(out, dec2bin(insts[2]));
        }
        else if (strcmp(insts[0], "RGRM") == 0){
            strcat(out, "10000");
            strcat(out, dec2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
        }
        else if (strcmp(insts[0], "RMRG") == 0){
            strcat(out, "10001");
            strcat(out, reg2bin(insts[1]));
            strcat(out, dec2bin(insts[2]));
        }
        else if (strcmp(insts[0], "HDRM") == 0){
            strcat(out, "10010");
            strcat(out, dec2bin(insts[1]));
            strcat(out, dec2bin(insts[2]));
        }
        else if (strcmp(insts[0], "RMHD") == 0){
            strcat(out, "10011");
            strcat(out, dec2bin(insts[1]));
            strcat(out, dec2bin(insts[2]));
        }
        else if (strcmp(insts[0], "INPT") == 0){
            strcat(out, "10100");
            strcat(out, dec2bin(insts[1]));
            strcat(out, dec2bin(insts[2]));
            strcat(out, dec2bin(insts[3]));
        }
        else if (strcmp(insts[0], "OUPT") == 0){
            strcat(out, "10101");
            strcat(out, dec2bin(insts[1]));
            strcat(out, dec2bin(insts[2]));
            strcat(out, dec2bin(insts[3]));
        }
        else if (strcmp(insts[0], "IF") == 0){
            strcat(out, "10110");
            strcat(out, reg2bin(insts[1]));
        }
        else if (strcmp(insts[0], "GOTO") == 0){
            strcat(out, "10111");
            strcat(out, reg2bin(insts[1]));
        }
        else if (strcmp(insts[0], "JMP") == 0){
            strcat(out, "11000");
            int i = 0;
            while (jump_point[i].key == NULL){
                if (strcmp(jump_point[i].key, insts[1]) == 0){
                    i++;
                }
                else {
                    break;
                }
            }
            char val_str[1000];
            sprintf(val_str, "%d", jump_point[i].val);
            strcat(out, dec2bin(val_str));
        }
        else if (strcmp(insts[0], "PUSH") == 0){
            strcat(out, "11001");
            strcat(out, dec2bin(insts[1]));
            strcat(out, dec2bin(insts[2]));
            strcat(out, dec2bin(insts[3]));
        }
        else if (strcmp(insts[0], "PULL") == 0){
            strcat(out, "11010");
            strcat(out, dec2bin(insts[1]));
            strcat(out, dec2bin(insts[2]));
            strcat(out, dec2bin(insts[3]));
        }
        else if (strcmp(insts[0], "MOR") == 0){
            strcat(out, "11011");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "LES") == 0){
            strcat(out, "11100");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "EQL") == 0){
            strcat(out, "11101");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
            strcat(out, reg2bin(insts[3]));
        }
        else if (strcmp(insts[0], "IMP") == 0){
            strcat(out, "11110");
            strcat(out, dec2bin(insts[1]));
        }
        else if (strcmp(insts[0], "GRM") == 0){
            strcat(out, "11111");
            strcat(out, reg2bin(insts[1]));
            strcat(out, reg2bin(insts[2]));
        }
        else {
            fprintf(stderr, "Assembly error: unable to recognize instruction %s\n", insts[0]);
        }
    }

    strcpy(bin, out);

    return bin;
}

char* to_char_arr(const char arr[][25]){
    char* r_out = malloc(10000);
    char out[10000] = "";
    for(int i = 0;strcmp(arr[i], "\0");i++){
        strcat(out, arr[i]);
    }
    strncpy(r_out, out, 10000);
    return r_out;
}


void print_2d_char_arr(char arr[][25]){
    printf("[");
    for (int i = 0;i < sizeof(*arr) / sizeof(arr);i++){
        printf("%s, ", arr[i]);
    }
    printf("]\n");
}

void draw(){
    glPointSize(scale_size);
    glBegin(GL_POINTS);
    float coord_x;
    float coord_y;
    for (int i = 0;i < sizeof(draw_table) / sizeof(draw_table[0]);i++){
        coord_x = i % 256 + 0.5;
        coord_y = i / 256 + 0.5;
        if (draw_table[i] == '1'){
            glVertex2d(coord_x * scale_size, coord_y * scale_size);
        }
    }
    glEnd();
}

int run(char HD[][25], char ram[][25], char reg[][25], int prog){
    int code_runned = 5;
    int c_code = prog + code_runned;
    char* insts;
    int line = 0;
    int loop = 1;
    int reg1;
    int reg2;
    int res_int;
    char* res;
    int if_line = 0;
    int if_line_new = 0;
    int if_result = 0;
    char HD_used[10000] = "";
    int jump_point = 0;
    int history[1000];
    strncpy(HD_used, to_char_arr(HD), 10000);
    while (strcmp(strsplice(HD_used, prog, prog + 5), "00000") == 0 && loop){
        history[line] = c_code;
        strcpy(HD_used, to_char_arr(HD));
        insts = strsplice(HD_used, c_code, c_code + 5);
        if (if_line == 0){
            if (line >= jump_point){
                if (strcmp(insts, "00001") == 0){
                    printf("\ndone\n");
                    loop = 0;
                }
                else if (strcmp(insts, "00010") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 + reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00011") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 - reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00100") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 * reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00101") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 / reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00110") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 & reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00111") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 | reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01000") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 ^ reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01001") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = ~(reg1 & reg2);
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01010") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = ~(reg1 | reg2);
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01011") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = ~(reg1 ^ reg2);
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01100") == 0) {
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], strsplice(HD_used, c_code + 7, c_code + 31));
                    c_code += 31;
                }
                else if (strcmp(insts, "01101") == 0) {
                    strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], strsplice(HD_used, c_code + 29, c_code + 53));
                    c_code += 53;
                }
                else if (strcmp(insts, "01110") == 0) {
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    c_code += 9;
                }
                else if (strcmp(insts, "01111") == 0) {
                    strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], ram[bin2dec(strsplice(HD_used, c_code + 29, c_code + 53))]);
                    c_code += 53;
                }
                else if (strcmp(insts, "10000") == 0) {
                    strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], reg[bin2dec(strsplice(HD_used, c_code + 29, c_code + 31))]);
                    c_code += 31;
                }
                else if (strcmp(insts, "10001") == 0) {
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], ram[bin2dec(strsplice(HD_used, c_code + 7, c_code + 31))]);
                    c_code += 31;
                }
                else if (strcmp(insts, "10010") == 0) {
                    strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], HD[bin2dec(strsplice(HD_used, c_code + 29, c_code + 53))]);
                    c_code += 53;
                }
                else if (strcmp(insts, "10011") == 0) {
                    strcpy(HD[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], ram[bin2dec(strsplice(HD_used, c_code + 29, c_code + 53))]);
                    c_code += 53;
                }
                else if (strcmp(insts, "10100") == 0) {
                    if (kbhit() && bin2dec(strsplice(HD_used, c_code + 29, c_code + 53)) == 0){
                        char input_char = getch();
                        int inpch_int = input_char;
                        char inpch_str[10];
                        itoa(inpch_int, inpch_str, 10);
                        strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], dec2bin(inpch_str));
                    }
                    c_code += 77;
                }
                else if (strcmp(insts, "10101") == 0){
                    if (bin2dec(strsplice(HD_used, c_code + 29, c_code + 53)) == 0){
                        draw_to_out(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))]);
                    }
                    c_code += 77;
                }
                else if (strcmp(insts, "10110") == 0){
                    if_line_new = 2;
                    if_result = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))]);
                    c_code += 7;
                }
                else if (strcmp(insts, "10111") == 0){
                    int new_jump = bin2dec(reg[bin2dec(strsplice(HD_used, 5, 7))]);
                    if (new_jump < line){
                        c_code = history[new_jump];
                    }
                    else {
                        jump_point = new_jump;
                        c_code += 7;
                    }
                }
                else if (strcmp(insts, "11000") == 0){
                    int new_jump = bin2dec(strsplice(HD_used, c_code + 5, c_code + 29));
                    if (new_jump < line){
                        c_code = history[new_jump];
                    }
                    else {
                        jump_point = new_jump;
                        c_code += 29;
                    }
                }
                else {
                    printf("\ndone with error with insts \"%s\" at line %d\n", insts, line);
                    loop = 0;
                }
                line++;
            }
            else {
                if (strcmp(insts, "00001") == 0){
                    printf("\ndone\n");
                    loop = 0;
                }
                else if (strcmp(insts, "00010") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00011") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00100") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00101") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00110") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00111") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01000") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01001") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01010") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01011") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01100") == 0) {
                    c_code += 31;
                }
                else if (strcmp(insts, "01101") == 0) {
                    c_code += 53;
                }
                else if (strcmp(insts, "01110") == 0) {
                    c_code += 9;
                }
                else if (strcmp(insts, "01111") == 0) {
                    c_code += 53;
                }
                else if (strcmp(insts, "10000") == 0) {
                    c_code += 31;
                }
                else if (strcmp(insts, "10001") == 0) {
                    c_code += 31;
                }
                else if (strcmp(insts, "10010") == 0) {
                    c_code += 53;
                }
                else if (strcmp(insts, "10011") == 0) {
                    c_code += 53;
                }
                else if (strcmp(insts, "10100") == 0) {
                    c_code += 77;
                }
                else if (strcmp(insts, "10101") == 0){
                    c_code += 77;
                }
                else if (strcmp(insts, "10110") == 0){
                    c_code += 7;
                }
                else if (strcmp(insts, "10111") == 0){
                    c_code += 7;
                }
                else if (strcmp(insts, "11000") == 0){
                    c_code += 29;
                }
                else {
                    loop = 0;
                }
                line++;
            }
        }
        if (if_line == 1){
            if (if_result == 0 && line >= jump_point){
                if (strcmp(insts, "00001") == 0){
                    printf("\ndone\n");
                    loop = 0;
                }
                else if (strcmp(insts, "00010") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 + reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00011") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 - reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00100") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 * reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00101") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 / reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00110") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 & reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00111") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 | reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01000") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 ^ reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01001") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = ~(reg1 & reg2);
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01010") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = ~(reg1 | reg2);
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01011") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = ~(reg1 ^ reg2);
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01100") == 0) {
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], strsplice(HD_used, c_code + 7, c_code + 31));
                    c_code += 31;
                }
                else if (strcmp(insts, "01101") == 0) {
                    strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], strsplice(HD_used, c_code + 29, c_code + 53));
                    c_code += 53;
                }
                else if (strcmp(insts, "01110") == 0) {
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    c_code += 9;
                }
                else if (strcmp(insts, "01111") == 0) {
                    strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], ram[bin2dec(strsplice(HD_used, c_code + 29, c_code + 53))]);
                    c_code += 53;
                }
                else if (strcmp(insts, "10000") == 0) {
                    strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], reg[bin2dec(strsplice(HD_used, c_code + 29, c_code + 31))]);
                    c_code += 31;
                }
                else if (strcmp(insts, "10001") == 0) {
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], ram[bin2dec(strsplice(HD_used, c_code + 7, c_code + 31))]);
                    c_code += 31;
                }
                else if (strcmp(insts, "10010") == 0) {
                    strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], HD[bin2dec(strsplice(HD_used, c_code + 29, c_code + 53))]);
                    c_code += 53;
                }
                else if (strcmp(insts, "10011") == 0) {
                    strcpy(HD[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], ram[bin2dec(strsplice(HD_used, c_code + 29, c_code + 53))]);
                    c_code += 53;
                }
                else if (strcmp(insts, "10100") == 0) {
                    if (kbhit() && bin2dec(strsplice(HD_used, c_code + 29, c_code + 53)) == 0){
                        char input_char = getch();
                        int inpch_int = input_char;
                        char inpch_str[10];
                        itoa(inpch_int, inpch_str, 10);
                        strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], dec2bin(inpch_str));
                    }
                    c_code += 77;
                }
                else if (strcmp(insts, "10101") == 0){
                    if (bin2dec(strsplice(HD_used, c_code + 29, c_code + 53)) == 0){
                        draw_to_out(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))]);
                    }
                    c_code += 77;
                }
                else if (strcmp(insts, "10110") == 0){
                    if_line_new = 2;
                    if_result = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))]);
                    c_code += 7;
                }
                else if (strcmp(insts, "10111") == 0){
                    int new_jump = bin2dec(reg[bin2dec(strsplice(HD_used, 5, 7))]);
                    if (new_jump < line){
                        c_code = history[new_jump];
                    }
                    else {
                        jump_point = new_jump;
                        c_code += 7;
                    }
                }
                else if (strcmp(insts, "11000") == 0){
                    int new_jump = bin2dec(strsplice(HD_used, c_code + 5, c_code + 29));
                    if (new_jump < line){
                        c_code = history[new_jump];
                    }
                    else {
                        jump_point = new_jump;
                        c_code += 29;
                    }
                }
                else {
                    printf("\ndone with error with insts \"%s\" at line %d\n", insts, line);
                    loop = 0;
                }
                line++;
            }
            else {
                if (strcmp(insts, "00001") == 0){
                    printf("\ndone\n");
                    loop = 0;
                }
                else if (strcmp(insts, "00010") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00011") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00100") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00101") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00110") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00111") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01000") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01001") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01010") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01011") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01100") == 0) {
                    c_code += 31;
                }
                else if (strcmp(insts, "01101") == 0) {
                    c_code += 53;
                }
                else if (strcmp(insts, "01110") == 0) {
                    c_code += 9;
                }
                else if (strcmp(insts, "01111") == 0) {
                    c_code += 53;
                }
                else if (strcmp(insts, "10000") == 0) {
                    c_code += 31;
                }
                else if (strcmp(insts, "10001") == 0) {
                    c_code += 31;
                }
                else if (strcmp(insts, "10010") == 0) {
                    c_code += 53;
                }
                else if (strcmp(insts, "10011") == 0) {
                    c_code += 53;
                }
                else if (strcmp(insts, "10100") == 0) {
                    c_code += 77;
                }
                else if (strcmp(insts, "10101") == 0){
                    c_code += 77;
                }
                else if (strcmp(insts, "10110") == 0){
                    c_code += 7;
                }
                else if (strcmp(insts, "10111") == 0){
                    c_code += 7;
                }
                else if (strcmp(insts, "11000") == 0){
                    c_code += 29;
                }
                else {
                    loop = 0;
                }
                line++;
            }
            if_line_new--;
        }
        if (if_line == 2){
            if (if_result == 1 && line >= jump_point){
                if (strcmp(insts, "00001") == 0){
                    printf("\ndone\n");
                    loop = 0;
                }
                else if (strcmp(insts, "00010") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 + reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00011") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 - reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00100") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 * reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00101") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 / reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00110") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 & reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "00111") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 | reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01000") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = reg1 ^ reg2;
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01001") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = ~(reg1 & reg2);
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01010") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = ~(reg1 | reg2);
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01011") == 0){
                    reg1 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    reg2 = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 9, c_code + 11))]);
                    res_int = ~(reg1 ^ reg2);
                    sprintf(res, "%d", res_int);
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], dec2bin(res));
                    c_code += 11;
                }
                else if (strcmp(insts, "01100") == 0) {
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], strsplice(HD_used, c_code + 7, c_code + 31));
                    c_code += 31;
                }
                else if (strcmp(insts, "01101") == 0) {
                    strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], strsplice(HD_used, c_code + 29, c_code + 53));
                    c_code += 53;
                }
                else if (strcmp(insts, "01110") == 0) {
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], reg[bin2dec(strsplice(HD_used, c_code + 7, c_code + 9))]);
                    c_code += 9;
                }
                else if (strcmp(insts, "01111") == 0) {
                    strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], ram[bin2dec(strsplice(HD_used, c_code + 29, c_code + 53))]);
                    c_code += 53;
                }
                else if (strcmp(insts, "10000") == 0) {
                    strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], reg[bin2dec(strsplice(HD_used, c_code + 29, c_code + 31))]);
                    c_code += 31;
                }
                else if (strcmp(insts, "10001") == 0) {
                    strcpy(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))], ram[bin2dec(strsplice(HD_used, c_code + 7, c_code + 31))]);
                    c_code += 31;
                }
                else if (strcmp(insts, "10010") == 0) {
                    strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], HD[bin2dec(strsplice(HD_used, c_code + 29, c_code + 53))]);
                    c_code += 53;
                }
                else if (strcmp(insts, "10011") == 0) {
                    strcpy(HD[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], ram[bin2dec(strsplice(HD_used, c_code + 29, c_code + 53))]);
                    c_code += 53;
                }
                else if (strcmp(insts, "10100") == 0) {
                    if (kbhit() && bin2dec(strsplice(HD_used, c_code + 29, c_code + 53)) == 0){
                        char input_char = getch();
                        int inpch_int = input_char;
                        char inpch_str[10];
                        itoa(inpch_int, inpch_str, 10);
                        strcpy(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))], dec2bin(inpch_str));
                    }
                    c_code += 77;
                }
                else if (strcmp(insts, "10101") == 0){
                    if (bin2dec(strsplice(HD_used, c_code + 29, c_code + 53)) == 0){
                        draw_to_out(ram[bin2dec(strsplice(HD_used, c_code + 5, c_code + 29))]);
                    }
                    c_code += 77;
                }
                else if (strcmp(insts, "10110") == 0){
                    if_line_new = 2;
                    if_result = bin2dec(reg[bin2dec(strsplice(HD_used, c_code + 5, c_code + 7))]);
                    c_code += 7;
                }
                else if (strcmp(insts, "10111") == 0){
                    int new_jump = bin2dec(reg[bin2dec(strsplice(HD_used, 5, 7))]);
                    if (new_jump < line){
                        c_code = history[new_jump];
                    }
                    else {
                        jump_point = new_jump;
                        c_code += 7;
                    }
                }
                else if (strcmp(insts, "11000") == 0){
                    int new_jump = bin2dec(strsplice(HD_used, c_code + 5, c_code + 29));
                    if (new_jump < line){
                        c_code = history[new_jump];
                    }
                    else {
                        jump_point = new_jump;
                        c_code += 29;
                    }
                }
                else {
                    printf("\ndone with error with insts \"%s\" at line %d\n", insts, line);
                    loop = 0;
                }
                line++;
            }
            else {
                if (strcmp(insts, "00001") == 0){
                    printf("\ndone\n");
                    loop = 0;
                }
                else if (strcmp(insts, "00010") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00011") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00100") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00101") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00110") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "00111") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01000") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01001") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01010") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01011") == 0){
                    c_code += 11;
                }
                else if (strcmp(insts, "01100") == 0) {
                    c_code += 31;
                }
                else if (strcmp(insts, "01101") == 0) {
                    c_code += 53;
                }
                else if (strcmp(insts, "01110") == 0) {
                    c_code += 9;
                }
                else if (strcmp(insts, "01111") == 0) {
                    c_code += 53;
                }
                else if (strcmp(insts, "10000") == 0) {
                    c_code += 31;
                }
                else if (strcmp(insts, "10001") == 0) {
                    c_code += 31;
                }
                else if (strcmp(insts, "10010") == 0) {
                    c_code += 53;
                }
                else if (strcmp(insts, "10011") == 0) {
                    c_code += 53;
                }
                else if (strcmp(insts, "10100") == 0) {
                    c_code += 77;
                }
                else if (strcmp(insts, "10101") == 0){
                    c_code += 77;
                }
                else if (strcmp(insts, "10110") == 0){
                    c_code += 7;
                }
                else if (strcmp(insts, "10111") == 0){
                    c_code += 7;
                }
                else if (strcmp(insts, "11000") == 0){
                    c_code += 29;
                }
                else {
                    loop = 0;
                }
                line++;
            }
            if_line_new--;
        }
        if_line = if_line_new;
    }
    return 0;
}
