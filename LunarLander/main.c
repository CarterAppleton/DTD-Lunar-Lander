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
void keyboard(unsigned char key, int a, int b);
void timercall(int value);
void update(int ticks);

void
update(int ticks)
{
    scene_manager_update();
}

void
timercall(int value)
{
	glutTimerFunc(SLEEP_TICKS, timercall, 0);
	glutPostRedisplay();
}

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

void display(void)
{
    scene_manager_display();

    update(1);
        
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);
}

void
reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	
	double scale = cpfmin(w/DEFAULT_WIDTH, h/DEFAULT_HEIGHT);
	double hw = w*(1.0/scale);
	double hh = h*(1.0/scale);
	
	glLineWidth(scale);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(0, hw, 0, hh, -1.0, 1.0);
}

void mouse(int button, int state, int x, int y)
{
	/* mouse handling function */
}

void keyboard(unsigned char key, int x, int y)
{
    scene_manager_keyboard_pressed(key);
    
    switch (key) {
        case 'f':
            if(fullScreen)
            {
                glutReshapeWindow(800, 600);    
                glutPositionWindow(0,0);
                fullScreen = 0;
            }else
            {
                glutFullScreen();
                fullScreen = 1;
            }
            break;
        default:
            break;
    }
}

void keyboardUp(unsigned char key, int x, int y)
{
    scene_manager_keyboard_released(key);
}

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

int main(int argc, char *argv[])
{    
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); /* Sets the window to double buffered with RGB colour profile */
	glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT); /* Sets the size of the window */
	glutInitWindowPosition(100, 100); /* Sets the window position */
	glutCreateWindow("Lunar Lander"); /* Creates the window with title GLUT Template */
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialFunction);
    glutTimerFunc(SLEEP_TICKS, timercall, 0);
	glutMainLoop();
    
    return 0;
}
