#include <GL/gl.h>
#include<GL/glut.h>
#include "header.h"
#include <windows.h>
#include <stdlib.h>

#define Col 100
#define Row 100
#define FPS 20

extern short dir;
bool over=false;
int score=0;

void timerCB(int);
void CB();
void KeyBoard(int,int,int);
void reshapeCB(int,int);
void init()
{
    glClearColor(0.0,0.0,0.0,1.0);
    Grid(Col,Row);
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600,600);
    glutCreateWindow("Snake");
    glutDisplayFunc(CB);
    glutReshapeFunc(reshapeCB);
    glutTimerFunc(0,timerCB,0);
    glutSpecialFunc(KeyBoard);
    init();
    glutMainLoop();
    return 0;
}

void CB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GridDraw();
    snake();
    food();
    glutSwapBuffers();
    if(over)
    {
        char Score[20];
        itoa(score,Score,10);
        char text[50]="Score: ";
        strcat(text,Score);
        MessageBox(NULL,text,"The Game is Over!!!",0);
        exit(0);
    }
}

void reshapeCB(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,Col,0.0,Row,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timerCB(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timerCB,0);
}

void KeyBoard(int key,int,int)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            if(dir!=DOWN)
                dir=UP;
            break;
        case GLUT_KEY_DOWN:
            if(dir!=UP)
                dir=DOWN;
            break;
        case GLUT_KEY_RIGHT:
            if(dir!=LEFT)
                dir=RIGHT;
            break;
        case GLUT_KEY_LEFT:
            if(dir!=RIGHT)
                dir=LEFT;
            break;
    }
}
