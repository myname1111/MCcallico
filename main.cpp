#include <iostream>
#include <fstream>
#include <string.h>
extern "C"{
    #include "asm.h"
}
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

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

    string mystring;
    ifstream myfile (argv[1]);

    if (myfile.is_open()) {
        myfile >> mystring;
        cout << mystring;
    }

    const char prog[] =
    "";
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
    glutMainLoop();

    return 0;
}
