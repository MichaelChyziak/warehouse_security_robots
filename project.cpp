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
#include "intruder/intruder.h"

using namespace std;

#define LIMIT 120    // limit
#define BOUNDARY 45
#define START -1
#define GRID_SIZE 4

const float DEG2RAD = 3.14159/180;

float dataMatrix[12][3];
const int LENGTH = 10;

extern unsigned int robot_1;
extern unsigned int robot_2;
extern unsigned int robot_3;

enum STATES {patrol, intruder_patrol, intruder_chase};
STATES state = STATES::patrol;

int index =0; 
bool intruder_caught = false;

std::vector<std::vector<unsigned int>>layout;

void moveRobot(int value);

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

void drawVision(float x, float y, unsigned int row, unsigned int col){
    unsigned int count = 0;
    unsigned int i = row;
    unsigned int j = col - 1;
    float startx = x - GRID_SIZE;
    float starty = y;

    glColor3f(0.812, 0.820, 0.827);
        //left
    glBegin(GL_POLYGON);
        while(startx > 0 && count < vision && j >= 0){
            if(layout[i][j] != PATH){
                break;
            }
            glVertex2f(startx, starty);
            glVertex2f(startx, starty + GRID_SIZE);
            glVertex2f(startx + GRID_SIZE, starty + GRID_SIZE);
            glVertex2f(startx + GRID_SIZE, starty);
            startx -= GRID_SIZE;
            j--;
            count++;
        }
    glEnd();
    
        count = 0;
        startx = x + GRID_SIZE;
        j = col + 1;
        //right
    glBegin(GL_POLYGON);
        while(x < LIMIT && count < vision && j < layout[0].size()){
            if(layout[i][j] != PATH){
                break;
            }
            glVertex2f(startx, starty);
            glVertex2f(startx, starty + GRID_SIZE);
            glVertex2f(startx + GRID_SIZE, starty + GRID_SIZE);
            glVertex2f(startx + GRID_SIZE, starty);
            startx += GRID_SIZE;
            j++;
            count++;
        }
    glEnd();

        count = 0;
        startx = x;
        starty = y + GRID_SIZE;
        j = col;
        i = row - 1;
        //up
    glBegin(GL_POLYGON);
        while(starty < LIMIT && count < vision && i >= 0){
            if(layout[i][j] != PATH){
                break;
            }
            glVertex2f(startx, starty);
            glVertex2f(startx, starty + GRID_SIZE);
            glVertex2f(startx + GRID_SIZE, starty + GRID_SIZE);
            glVertex2f(startx + GRID_SIZE, starty);
            starty += GRID_SIZE;
            i--;
            count++;
        }
    glEnd();
    
        count = 0;
        startx = x;
        starty = y; //- GRID_SIZE;
        i = row + 1;
        //down
    glBegin(GL_POLYGON);
        while(starty > 0 && count < vision && i < layout.size()){
            if(layout[i][j] != PATH){
                break;
            }
            glVertex2f(startx, starty);
            glVertex2f(startx, starty - GRID_SIZE);
            glVertex2f(startx + GRID_SIZE, starty - GRID_SIZE);
            glVertex2f(startx + GRID_SIZE, starty);
            starty -= GRID_SIZE;
            i++;
            count++;
        }
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
void keyboard(unsigned char key, int x, int y)
{
//////////////////////////   
//modify the intruder position
    if (state == STATES::patrol) {
        if(key == 49)// 1 pressed
        {
            layout = intruderStart(1, index);
            state = STATES::intruder_patrol;
            if (intruderFound(layout) == true) {
                state = STATES::intruder_chase;
            }
            index++;
        }
         //modify the intruder position
        else if(key == 50) //2 pressed
        {
            layout = intruderStart(2, index);
            state = STATES::intruder_patrol;
            if (intruderFound(layout) == true) {
                state = STATES::intruder_chase;
            }
            index++;
        }

        //modify the intruder position
        else if(key == 51) //3 pressed
        {
            layout = intruderStart(3, index);
            state = STATES::intruder_patrol;
            if (intruderFound(layout) == true) {
                state = STATES::intruder_chase;
            }
            index++;
        }

        //modify the intruder position
        else if(key == 52) //4 pressed
        {
            layout = intruderStart(4, index);
            state = STATES::intruder_patrol;
            if (intruderFound(layout) == true) {
                state = STATES::intruder_chase;
            }
            index++;
        }
    }

    // quit program
    if (key == 27) { //escape pressed
        exit(0);
    }

    // Check if game over
    if (intruder_caught == true) {
        printf("Game Over\n");
        state = STATES::patrol;
        index = 0;
        intruder_caught = false;
        glutTimerFunc(500, moveRobot, 0);
        robot_1 = -1;
        robot_2 = -1;
        robot_3 = -1;
    }
	
    // Request display update
    glutPostRedisplay();
}

//keyboard movement for intruder
void specialKeys(int key, int x, int y)
{
    if (state == STATES::intruder_patrol) {
        //////////////////////////   
        //modify the intruder position
        if (key == GLUT_KEY_RIGHT) //right = 2
            {
            if (intruderValidMove(2) == true) {
                layout = intruderMovePatrol(2, index);
                if (intruderFound(layout) == true) {
                    state = STATES::intruder_chase;
                }
                index++;
            }
        }
        else if (key == GLUT_KEY_LEFT) //left =1
            {
            if (intruderValidMove(1) == true) {
                layout = intruderMovePatrol(1, index);
                if (intruderFound(layout) == true) {
                    state = STATES::intruder_chase;
                }
                index++;
            }
        }
        else if (key == GLUT_KEY_DOWN) //down = 4
            {
            if (intruderValidMove(4) == true) {
                layout = intruderMovePatrol(4, index);
                if (intruderFound(layout) == true) {
                    state = STATES::intruder_chase;
                }
                index++;
            }
        }
        else if (key == GLUT_KEY_UP) //up = 3
            {
            if (intruderValidMove(3) == true) {
                layout = intruderMovePatrol(3, index); 
                if (intruderFound(layout) == true) {
                    state = STATES::intruder_chase;
                }
                index++;
            }
        }
        

    }
    else if (state == STATES::intruder_chase) {
        //////////////////////////   
        //modify the intruder position
        if (key == GLUT_KEY_RIGHT) //right = 2
            {
            if (intruderValidMove(2) == true) {
                layout = intruderMoveChased(2, layout);
            }
        }
        else if (key == GLUT_KEY_LEFT) //left =1
            {
            if (intruderValidMove(1) == true) {
                layout = intruderMoveChased(1, layout);
            }
        }
        else if (key == GLUT_KEY_DOWN) //down = 4
            {
            if (intruderValidMove(4) == true) {
                layout = intruderMoveChased(4, layout);
            }
        }
        else if (key == GLUT_KEY_UP) //up = 3
            {
            if (intruderValidMove(3) == true) {
                layout = intruderMoveChased(3, layout); 
            }
        }
    }

    // Check if game over
    if (intruder_caught == true) {
        printf("Game Over\n");
        state = STATES::patrol;
        index = 0;
        intruder_caught = false;
        glutTimerFunc(500, moveRobot, 0);
        robot_1 = -1;
        robot_2 = -1;
        robot_3 = -1;
    }
    
    // Request display update
    glutPostRedisplay();
}

//robot animation
void moveRobot(int value)
{
    if (state == STATES::patrol) {
    	layout = warehousePatrolUpdate(index);
    	glutPostRedisplay();
       	index++;
    	glutTimerFunc(500, moveRobot, 0);
    }
}

void warehouse()
{
    if (layout.empty()) {
        layout = warehousePatrolUpdate(index);
    }
    if (layout.empty() == false) {
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
                    drawVision(startx, starty, i, j);
                }
                startx +=GRID_SIZE;
            }
            starty +=GRID_SIZE;
            startx =0;

        }
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
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(500,moveRobot,0);


    glutMainLoop();
    return 0;

}
