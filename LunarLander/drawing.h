//
//  drawing.h
//  LunarLander
//
//  Created by Carter Appleton on 4/3/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#include "chipmunk.h"
#include <GLUT/glut.h>

#ifndef LunarLander_drawing_h
#define LunarLander_drawing_h

#include "array.h"

typedef Array HeightMap;

typedef struct Color {
	GLfloat r, g, b, a;
} Color;

static inline Color 
RGBAColor(float r, float g, float b, float a)
{
	Color color = {r, g, b, a};
	return color;
}

static void glColor_from_color(Color color);
void drawCircle(cpVect center, cpFloat angle, cpFloat radius, Color lineColor, Color fillColor);
void drawRect(cpVect upperLeft, cpVect dimensions, Color fillColor);
void drawString(int x, int y, const char *str, Color stringColor);

//void drawCALetter(char c, GLfloat size, GLfloat px, GLfloat py);
void drawCALetter(int** c, GLfloat size, GLfloat px, GLfloat py);

void drawCAWord(char* string, GLfloat size, GLfloat px, GLfloat py);

void drawHeightMap(HeightMap h, int totalWidth);
                   
#endif
