#include <iostream>
#include <string.h>
extern "C"{
    #include "asm.h"
}
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "LexerToken.h"
#include "Lexer.h"

using namespace std;

void init(){
    glClearColor(0, 0, 0, 1);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    draw();

    glFlush();
}

void reshape(int x, int y){
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 256 * scale_size, 144 * scale_size, 0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char**argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(256 * scale_size, 144 * scale_size);

    glutCreateWindow("Program");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    init();
    init_asm();

    /*
    const char prog[] =
    "STR;"
    "END:;"
    "SRG,A,1;"
    "JMP,END;"
    "SRG,A,0;"
    "IF,A;"
    "SRG,B,0;"
    "SRG,B,1;"
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

    display();
    */

    LexerToken a = LexerToken("INT", "12");

    cout << a << endl;

    glutMainLoop();
    return 0;
}
