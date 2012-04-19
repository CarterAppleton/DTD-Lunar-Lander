//
//  main.c
//  LunarLander
//
//  Created by Carter Appleton on 4/3/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>

#include "chipmunk.h"

#include "drawing.h"
#include "array.h"
#include "lander.h"
#include "constants.h"

#include "SceneManager.h"

static GLboolean fullScreen = 0;

void init(void);
void display(void);
void reshape(int, int);

void mouse(int, int, int, int);
void mouseMotionFunc(int x, int y);

void keyboard(unsigned char key, int a, int b);
void timercall(int value);
void update(int ticks);

#if EDIT_LANDSCAPE
static Array makeArray = NULL;
static int selectedIndex = -1;
static int mouse_x = 0;
static int mouse_y = 0;
#endif

/* Tell the scene manager to update
 */

void
update(int ticks)
{
#if !EDIT_LANDSCAPE
    scene_manager_update();
#endif
}

/* Run the display function again after we've waited for drawing
 */

void
timercall(int value)
{
	glutTimerFunc(SLEEP_TICKS, timercall, 0);
	glutPostRedisplay();
}

/* Initialize the graphics
 */

void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
    
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);
}

/* Update everything then tell scene manager to display
 */

void display(void)
{
    //Update everything
    update(1);

#if EDIT_LANDSCAPE
    //Draw the new landscape
    drawHeightMap((HeightMap)makeArray, DEFAULT_WIDTH);
    
    GLfloat stepWidth = ((GLfloat)glutGet(GLUT_WINDOW_WIDTH)) / ((GLfloat)makeArray->count-1);

    glColor3f(1.0, 1.0, 1.0);
    glPointSize(10);
    glBegin(GL_POINTS);
    //glVertex2f(mouse_x, glutGet(GLUT_WINDOW_HEIGHT) - mouse_y);
    glEnd();  
#else
    //Tell scene manager to display
    scene_manager_display();
#endif
        
    //Swap the buffers and clear to display on the screen
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);
}

/* Reshape the scene to display correclty in the window
 */

void
reshape(int w, int h)
{
#if DEBUG
	glViewport(0, 0, w, h);
	
	double scale = cpfmin(w/DEFAULT_WIDTH, h/DEFAULT_HEIGHT);
	double hw = w*(1.0/scale);
	double hh = h*(1.0/scale);
	
	glLineWidth(scale);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(0, hw, 0, hh, -1.0, 1.0);
#else
    
    glLoadIdentity();
    glOrtho(0, DEFAULT_WIDTH, 0, DEFAULT_HEIGHT, -1.0, 1.0);
    
#endif
}

/* Respond to mouse events - not implemented now
 */

void mouse(int button, int state, int x, int y)
{
#if EDIT_LANDSCAPE
    if(state == GLUT_DOWN)  //Pressed
    {
        //Get the closest index
        GLfloat stepWidth = ((GLfloat)glutGet(GLUT_WINDOW_WIDTH)) / ((GLfloat)makeArray->count-1);
        selectedIndex = x / stepWidth;
    }else                   //Released
    {
        selectedIndex = -1;
    }
#endif
}

void mouseMotionFunc(int x, int y)
{
#if EDIT_LANDSCAPE
    if(selectedIndex >= 0 && selectedIndex < makeArray->count)
        arrayReplaceAtIndex(glutGet(GLUT_WINDOW_HEIGHT)-y, selectedIndex, makeArray);
    
    mouse_x = x;
    mouse_y = y;
#endif
}

/* Respond to keyboard pressed - forward all key presses to 
 * scene manager except for 'f', which toggles fullscreen
 */

void keyboard(unsigned char key, int x, int y)
{    
    switch (key) {
        case 'f':
            if(fullScreen)
            {
                glutReshapeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT);    
                glutPositionWindow(0,0);
                fullScreen = 0;
            }else
            {
                glutFullScreen();
                fullScreen = 1;
            }
            break;
#if EDIT_LANDSCAPE
        case 'p':
            arrayPrint(makeArray);
            break;
#endif

        default:
            scene_manager_keyboard_pressed(key);
            break;
    }

}

/* Respond to keyboard released - forward all key presses to 
 * scene manager.
 */

void keyboardUp(unsigned char key, int x, int y)
{
#if !EDIT_LANDSCAPE
    scene_manager_keyboard_released(key);
#endif
}

/* Respond to special keyboard keys (arrow keys)
 * these are mapped to wasd and then the normal 
 * keyboard function is called.
 */

void specialFunction(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_DOWN:
            keyboard('s', x, y);
            break;
        case GLUT_KEY_UP:
            keyboard('w', x, y);
            break;
        case GLUT_KEY_RIGHT:
            keyboard('d', x, y);
            break;
        case GLUT_KEY_LEFT:
            keyboard('a', x, y);
            break;
        default:
            break;
    }
}

/* Setup our game
 */

int main(int argc, char *argv[])
{    
#if EDIT_LANDSCAPE
    int c[100] = {151,155,151,145,141,136,125,125,125,128,125,116,105,101,97,90,84,72,48,39,39,39,39,39,39,43,49,54,57,58,54,51,51,47,41,43,58,88,112,140,154,163,169,176,180,181,182,167,161,161,161,161,174,181,182,187,188,183,174,155,151,141,135,128,124,101,92,91,91,91,91,91,91,95,97,94,89,78,72,70,73,81,91,96,101,108,109,114,124,136,147,176,217,229,235,236,235,243,245,246};
    
    int amount = 100;
    makeArray = arrayMakeFromArray(amount, c);

#endif
    
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); /* Sets the window to double buffered with RGB colour profile */
	glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT); /* Sets the size of the window */
	glutInitWindowPosition(100, 100); /* Sets the window position */
	glutCreateWindow("Lunar Lander"); /* Creates the window with title GLUT Template */
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
    glutMotionFunc(mouseMotionFunc);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialFunction);
    glutTimerFunc(SLEEP_TICKS, timercall, 0);
	glutMainLoop();
    
    return 0;
}
