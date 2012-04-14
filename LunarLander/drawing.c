//
//  drawing.c
//  LunarLander
//
//  Created by Carter Appleton on 4/3/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <GLUT/glut.h>
#include "drawing.h"
#include "chipmunk.h"

#include "fonts.h"

//#include "fonts.h"

static void
glColor_from_color(Color color)
{
	glColor4fv((GLfloat *)&color);
}

static const 
GLfloat circleVAR[] = {
    0.0000f,  1.0000f,
    0.2588f,  0.9659f,
    0.5000f,  0.8660f,
    0.7071f,  0.7071f,
    0.8660f,  0.5000f,
    0.9659f,  0.2588f,
    1.0000f,  0.0000f,
    0.9659f, -0.2588f,
    0.8660f, -0.5000f,
    0.7071f, -0.7071f,
    0.5000f, -0.8660f,
    0.2588f, -0.9659f,
    0.0000f, -1.0000f,
	-0.2588f, -0.9659f,
	-0.5000f, -0.8660f,
	-0.7071f, -0.7071f,
	-0.8660f, -0.5000f,
	-0.9659f, -0.2588f,
	-1.0000f, -0.0000f,
	-0.9659f,  0.2588f,
	-0.8660f,  0.5000f,
	-0.7071f,  0.7071f,
	-0.5000f,  0.8660f,
	-0.2588f,  0.9659f,
    0.0000f,  1.0000f,
    0.0f, 0.0f, // For an extra line to see the rotation.
};
static const int circleVAR_count = sizeof(circleVAR)/sizeof(GLfloat)/2;

void 
drawCircle(cpVect center, cpFloat angle, cpFloat radius, Color lineColor, Color fillColor)
{
	glVertexPointer(2, GL_FLOAT, 0, circleVAR);
    
	glPushMatrix(); 
    {
		glTranslatef(center.x, center.y, 0.0f);
		glRotatef(angle*180.0f/M_PI, 0.0f, 0.0f, 1.0f);
		glScalef(radius, radius, 1.0f);
		
		if(fillColor.a > 0){
			glColor_from_color(fillColor);
			glDrawArrays(GL_TRIANGLE_FAN, 0, circleVAR_count-1);
		}
		
		if(lineColor.a > 0){
			glColor_from_color(lineColor);
			glDrawArrays(GL_LINE_STRIP, 0, circleVAR_count);
		}
	} 
    glPopMatrix();
}

void
drawRect(cpVect upperLeft, cpVect dimensions, Color fillColor)
{
    glColor_from_color(fillColor);

    GLfloat z = 0;

    glBegin(GL_QUADS);
    
    glVertex3f(upperLeft.x,                 upperLeft.y,                z);
    glVertex3f(upperLeft.x+dimensions.x,    upperLeft.y,                z);
    glVertex3f(upperLeft.x+dimensions.x,    upperLeft.y-dimensions.y,   z);
    glVertex3f(upperLeft.x,                 upperLeft.y-dimensions.y,   z);
    
    glEnd();
}

void drawString(int x, int y, const char *str, Color stringColor)
{
    glColor_from_color(stringColor);
	glRasterPos2i(x, y);
    
    
	
	for(int i=0, len=strlen(str); i<len; i++){
		if(str[i] == '\n'){
			y -= 16;
			glRasterPos2i(x, y);
		} else if(str[i] == '*'){ // print out the last demo key
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, 'A');
		} else {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[i]);
		}
	}
}


void drawHeightMap(HeightMap h, int totalWidth)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    GLfloat z = 0;
    GLfloat stepWidth = ((GLfloat)totalWidth) / ((GLfloat)h->count-1);

    for (int x = 0; x < h->count-1; x++)
    {
        glBegin(GL_QUADS);

        glVertex3f(x*stepWidth, arrayValueAtIndex(x, h), z);
        glVertex3f((x+1)*stepWidth, arrayValueAtIndex(x+1, h),z);
        glVertex3f((x+1)*stepWidth, 0, z);
        glVertex3f(x*stepWidth, 0,z);
        
        glEnd();
    }
    
    glTranslatef(0, -1, 0);
    glColor3f(0.0f, 0.0f, 0.0f);
        
    for (int x = 0; x < h->count-1; x++)
    {
        glBegin(GL_QUADS);
        
        glVertex3f(x*stepWidth, arrayValueAtIndex(x, h), z);
        glVertex3f((x+1)*stepWidth, arrayValueAtIndex(x+1, h),z);
        glVertex3f((x+1)*stepWidth, 0, z);
        glVertex3f(x*stepWidth, 0,z);
        
        glEnd();
    }
    glTranslatef(0, 1, 0);
}



void drawCALetter(int** c, GLfloat size, GLfloat px, GLfloat py)
{
    GLfloat z = 0;
    
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            if(!c[y][x])
                continue;
                        
            glBegin(GL_QUADS);
            
            glVertex3f(px+x*size,      py+(4-y)*size+size,    z);
            glVertex3f(px+x*size+size, py+(4-y)*size+size,    z);
            glVertex3f(px+x*size+size, py+(4-y)*size,         z);
            glVertex3f(px+x*size,      py+(4-y)*size,         z);
            
            glEnd();
        }
    }
    
}

void drawCAWord(char* string, GLfloat size, GLfloat px, GLfloat py)
{
    int length = strlen(string);
    
    for(int i=0; i<length; i++)
    {
        char c = string[i];
        
        drawCALetter(CALetter(c), size, px, py);
        
        px+=size*5;
    }
    
}