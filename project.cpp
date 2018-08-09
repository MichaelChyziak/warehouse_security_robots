#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<math.h>
using namespace std;

#define LIMIT 50    // limit
#define BOUNDARY 45
#define CENTER -1

const float DEG2RAD = 3.14159/180;

float dataMatrix[12][3];
const int LENGTH = 10;

int layout[LENGTH][LENGTH] =  { { 1, 1, 1, 1, 1, 1, 1, 5, 1, 1 }, ///1
                                { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, ///2
                                { 1, 0, 0, 0, 1, 0, 1, 3, 0, 1 }, ///3
                                { 1, 0, 1, 0, 1, 0, 0, 0, 0, 1 }, ///4
                                { 1, 0, 1, 0, 0, 4, 1, 1, 0, 1 }, ///5
                                { 5, 0, 1, 3, 1, 0, 0, 0, 0, 1 }, ///6
                                { 1, 0, 1, 0, 1, 0, 0, 1, 0, 1 }, ///7
                                { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1 }, ///8
                                { 1, 0, 3, 0, 0, 0, 0, 0, 0, 1 }, ///9
                                { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }};//10

int k =0;

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
    gluOrtho2D(CENTER, LIMIT, CENTER, LIMIT); // -x1, x2, -y1, y2
}

//keyboard movement
void keyboard(int key, int x, int y)
{
   //modify the intruder position
   if (key == GLUT_KEY_RIGHT)
        {
            layout[8][2]=0 ;
            layout[8][3]=3 ;
                
        }
    else if (key == GLUT_KEY_LEFT)
        {
               // rY -= 15;
        }
    else if (key == GLUT_KEY_DOWN)
        {
               // rX -= 15;
        }
    else if (key == GLUT_KEY_UP)
        {
                //rX += 15;
        }
    // Request display update
    glutPostRedisplay();
}

//robot animation
void moveRobot(int value)
{
   //modify matrix on robot positions
    if(k==0)
    {
        layout[8][2]=0 ;
        layout[8][3]=3 ;
    
    }

    if(k==1)
    {
        layout[8][3]=0 ;
        layout[8][4]=3 ;
    
    }

    if(k==2)
    {
        layout[8][4]=0 ;
        layout[8][5]=3 ;
    
    
    }

    if(k==3)
    {
        layout[8][5]=0 ;
        layout[8][6]=3 ;
    
    }


	
	glutPostRedisplay();
    k++;
    glutTimerFunc(500, moveRobot, 0);

}

void warehouse()
{
    float startx =0,starty =0;
    for(int i =LENGTH-1; i>=0; i--)
    {
        for(int j=0; j<LENGTH; j++)
        {   //walls
            if(layout[i][j]==1)
            {
                grid("wall",startx,starty,4,4);
            }
            //doors
            else if(layout[i][j]==5)
            {
                grid("door",startx,starty,4,4);
            }
            //robot
            else if(layout[i][j]==3)
            {
                grid("robot",startx,starty,4,4);
            }
			
			 //intruder
            else if(layout[i][j]==4)
            {
                grid("intruder",startx+1,starty,4,4);
            }

            startx +=4;
        }
        starty +=4;
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
