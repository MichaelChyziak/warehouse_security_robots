#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<math.h>
#include "warehouse/warehouse.h"

using namespace std;

#define LIMIT 120    // limit
#define BOUNDARY 45
#define START -1
#define GRID_SIZE 4

const float DEG2RAD = 3.14159/180;

float dataMatrix[12][3];
const int LENGTH = 10;


int index =0; 

//for writng texts 
void writeText(GLfloat x, GLfloat y, int length, const char* text)
{
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(x, y);

    for(int i =0 ; i< length; i++)
    {
       glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
    }
}


////robot will be squares
void grid(string type, float x, float y, float width, float height)
{
    
	if(type == "wall")
	{glColor3f(1.0,0,0);}
	else if(type == "door")
	{glColor3f(0.0,0,1.0);}
	else if(type == "robot")
	{glColor3f(0.0,1.0,0);}
	else if(type == "intruder")
	{glColor3f(1.0,0,1.0);}

	glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x, y+height);
        glVertex2f(x+width, y+height);
        glVertex2f(x+width, y);
    glEnd();
}



void Coordinate(){
    glBegin(GL_LINES);
        // horizontal lines
        glColor3f(0.0,0.0,0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(LIMIT, 0.0);

        // vertical lines
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, LIMIT);
    glEnd();
}

void setup()
{   //reset the background color to whire
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //set the window size in X and Y direction
    gluOrtho2D(START, LIMIT, START, LIMIT); // -x1, x2, -y1, y2
}

//keyboard movement for intruder
void keyboard(int key, int x, int y)
{
//////////////////////////   
//modify the intruder position
  if(key ==49)// 1 pressed
  {
	intruderStart(1,index);
  }
	 //modify the intruder position
  else if(key ==50) //2 pressed
  {
	intruderStart(2,index);
  }
	
  //modify the intruder position
  else if(key ==51) //3 pressed
  {
	intruder(3,index);
  }
	
   //modify the intruder position
  else if(key ==52) //4 pressed
  {
	intruder(4,index);
  }
///////////////////////////

   if (key == GLUT_KEY_RIGHT) //right = 2
        {
             intruderMove(2,index);   
        }
    else if (key == GLUT_KEY_LEFT) //left =1
        {
              intruderMove(1,index);   
        }
    else if (key == GLUT_KEY_DOWN) //down = 4
        {
               intruderMove(4,index);   
        }
    else if (key == GLUT_KEY_UP) //up = 3
        {
                intruderMove(3,index);   
        }
	
    intruderFound();
	
    // Request display update
    glutPostRedisplay();
}

//robot animation
void moveRobot(int value)
{
	warehousePatrolUpdate(index);
	glutPostRedisplay();
       	index++;
    	glutTimerFunc(500, moveRobot, 0);

}

void warehouse()
{
    std::vector<std::vector<unsigned int>>layout = warehousePatrolUpdate(index);
    float startx =0,starty =0;
    for(int i =layout.size()-1; i>=0; i--)
    {
        for(int j=0; j<layout.size(); j++)
        {   //walls
            if(layout[i][j]==1)
            {
                grid("wall",startx,starty,GRID_SIZE,GRID_SIZE);
            }
            //doors
            else if(layout[i][j]==2)
            {
                grid("door",startx,starty,GRID_SIZE,GRID_SIZE);
            }
            //robot
            else if(layout[i][j]==3)
            {
                grid("robot",startx,starty,GRID_SIZE,GRID_SIZE);
            }
			
	    //intruder
            else if(layout[i][j]==4)
            {
                grid("intruder",startx,starty,GRID_SIZE,GRID_SIZE);
            }

            startx +=GRID_SIZE;
        }
        starty +=GRID_SIZE;
        startx =0;

    }

}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    warehouse();
    glFlush();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(600, 150);
    glutInitWindowSize(500, 400);
    glutCreateWindow("Robot Security");

    setup();
    glutDisplayFunc(display);
    //glutSpecialFunc(keyboard);
    glutTimerFunc(500,moveRobot,0);


    glutMainLoop();
    return 0;

}
