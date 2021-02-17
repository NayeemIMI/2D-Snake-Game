#include <GL/gl.h>
#include<GL/glut.h>
#include "header.h"
#include <windows.h>
#include <ctime>

extern int score;

int gridX,gridY;
int len=5;
short dir=RIGHT;
bool Food=true;
int FoodX,FoodY;
extern bool over;

int posX[200]={50,50,50,50,50},posY[200]={50,49,48,47,46};

void Grid(int x,int y)
{
    gridX=x;
    gridY=y;
}
void SqUnit(int,int);
void GridDraw()
{
    for(int x=0;x<gridX;x++)
    {
        for(int y=0;y<gridY;y++)
        {
            SqUnit(x,y);
        }
    }
}

void SqUnit(int x,int y)
{
    if(x==0||y==0||x==gridX-1||y==gridY-1)
    {
        glLineWidth(2.0);
        glColor3f(1.0,0.0,0.0);
    }
    else
    {
        glLineWidth(1.0);
        glColor3f(0.0,0.0,0.0);
    }

    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
}

void food()
{
    if(Food)
        random(FoodX,FoodY);
    Food=false;
    glColor3f(0.0,1.0,0.0);
    glRectf(FoodX,FoodY,FoodX+1,FoodY+1);
}

void snake()
{
    for(int i=len-1;i>0;i--)
    {
        posX[i]=posX[i-1];
        posY[i]=posY[i-1];
    }
    if(dir==UP)
        posY[0]++;
    else if(dir==DOWN)
        posY[0]--;
    else if(dir==RIGHT)
        posX[0]++;
    else if(dir==LEFT)
        posX[0]--;
    for(int i=0;i<len;i++)
    {
        if(i==0)
            glColor3f(1.0,1.0,0.0);
        else
            glColor3f(1.0,0.0,1.0);
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);
    }

    if(posX[0]==0||posX[0]==gridX-1||posY[0]==0||posY[0]==gridY-1)
        over=true;
    for(int j=1;j<len;j++)
    {
        if(posX[j]==posX[0]&&posY[j]==posY[0])
        over=true;
    }

    if(posX[0]==FoodX&&posY[0]==FoodY)
    {
        score++;
        len++;
        if(len>MAX)
            len=MAX;
        Food=true;
    }
}

void random(int &x,int &y)
{
    int maxX=gridX-2;
    int maxY=gridY-2;
    int min=1;
    srand(time(NULL));
    x=min+rand()%(maxX-min);
    y=min+rand()%(maxY-min);
}
