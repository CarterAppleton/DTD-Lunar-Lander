//
//  fonts.c
//  LunarLander
//
//  Created by Carter Appleton on 4/10/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "fonts.h"

/*
 static int char_![5][5] = 
 {
 {0,0,0,0,0},
 {0,0,0,0,0},
 {0,0,0,0,0},
 {0,0,0,0,0},
 {0,0,0,0,0},};
 */

static int char_a[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,1,0},
    {1,1,1,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},};

static int char_b[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,1,0},
    {1,0,1,1,0},
    {1,0,0,1,0},
    {1,1,1,1,0},};

static int char_c[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,1,1,1,0},};

static int char_d[5][5] = 
{
    {1,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,1,1,0,0},};

static int char_e[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,0,0},
    {1,1,1,0,0},
    {1,0,0,0,0},
    {1,1,1,1,0},};

static int char_f[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,0,0},
    {1,1,1,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},};

static int char_g[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,0,0},
    {1,0,1,1,0},
    {1,0,0,1,0},
    {1,1,1,1,0},};

static int char_h[5][5] = 
{
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,1,1,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},};

static int char_i[5][5] = 
{
    {1,1,1,1,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {1,1,1,1,0},};

static int char_j[5][5] = 
{
    {0,0,0,1,0},
    {0,0,0,1,0},
    {1,1,0,1,0},
    {1,0,0,1,0},
    {1,1,1,1,0},};

static int char_k[5][5] = 
{
    {1,0,0,1,0},
    {1,0,1,0,0},
    {1,1,0,0,0},
    {1,0,1,0,0},
    {1,0,0,1,0},};

static int char_l[5][5] = 
{
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,1,1,1,0},};

static int char_m[5][5] = 
{
    {1,0,0,1,0},
    {1,1,1,1,0},
    {1,1,0,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},};

static int char_n[5][5] = 
{
    {1,0,0,1,0},
    {1,1,0,1,0},
    {1,0,1,1,0},
    {1,0,1,1,0},
    {1,0,0,1,0},};

static int char_o[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,1,1,1,0},};

static int char_p[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,1,0},
    {1,1,1,1,0},
    {1,0,0,0,0},
    {1,0,0,0,0},};

static int char_q[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,0,1,0,0},
    {1,1,0,1,0},};

static int char_r[5][5] = 
{
    {1,1,1,0,0},
    {1,0,1,0,0},
    {1,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},};

static int char_s[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,0,0},
    {1,1,1,1,0},
    {0,0,0,1,0},
    {1,1,1,1,0},};

static int char_t[5][5] = 
{
    {1,1,1,1,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},};

static int char_u[5][5] = 
{
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,1,1,1,0},};

static int char_v[5][5] = 
{
    {1,0,0,1,0},
    {1,0,0,1,0},
    {0,1,0,1,0},
    {0,1,0,1,0},
    {0,0,1,0,0},};

static int char_w[5][5] = 
{
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,1,0,1,0},
    {1,1,0,1,0},
    {1,1,1,1,0},};

static int char_x[5][5] = 
{
    {1,0,0,1,0},
    {0,1,0,1,0},
    {0,0,1,0,0},
    {0,1,0,1,0},
    {1,0,0,1,0},};

static int char_y[5][5] = 
{
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,1,1,1,0},
    {0,0,0,1,0},
    {0,0,1,1,0},};

static int char_z[5][5] = 
{
    {1,1,1,1,0},
    {0,0,1,0,0},
    {0,1,0,0,0},
    {1,0,0,0,0},
    {1,1,1,1,0},};

static int char_1[5][5] = 
{
    {0,1,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {1,1,1,1,0},};

static int char_2[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,1,0},
    {0,1,1,1,0},
    {1,0,0,0,0},
    {1,1,1,1,0},};

static int char_3[5][5] = 
{
    {1,1,1,1,0},
    {0,0,0,1,0},
    {0,1,1,1,0},
    {0,0,0,1,0},
    {1,1,1,1,0},};

static int char_4[5][5] = 
{
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,1,1,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0},};

static int char_5[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,0,0},
    {1,1,1,0,0},
    {0,0,0,1,0},
    {1,1,1,1,0},};

static int char_6[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,0,0},
    {1,1,1,1,0},
    {1,0,0,1,0},
    {1,1,1,1,0},};

static int char_7[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0},};

static int char_8[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,1,0},
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,1,1,1,0},};

static int char_9[5][5] = 
{
    {1,1,1,1,0},
    {1,0,0,1,0},
    {1,1,1,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0},};

static int char_0[5][5] = 
{
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {0,1,1,0,0},};
 
typedef struct CarterChar
{
    char c;
    int** map;
} CarterChar;

typedef CarterChar* CAChar;

static CAChar* cachar_array = NULL;

CAChar CACharMake(char ch)
{
    CAChar cac = malloc(sizeof(struct CarterChar));
    
    cac->c = ch;
    
    cac->map = malloc(sizeof(int*) * 5);
    
    for (int r = 0; r < 5; r++)
    {
        cac->map[r] = malloc(sizeof(int) * 5);
        
        for (int c = 0; c < 5; c++)
        {            
            switch (ch) 
            {
                case 'a':
                    cac->map[r][c] = char_a[r][c];
                    break;
                case 'b':
                    cac->map[r][c] = char_b[r][c];
                    break;   
                case 'c':
                    cac->map[r][c] = char_c[r][c];
                    break;    
                case 'd':
                    cac->map[r][c] = char_d[r][c];
                    break;
                case 'e':
                    cac->map[r][c] = char_e[r][c];
                    break;
                case 'f':
                    cac->map[r][c] = char_f[r][c];
                    break;    
                case 'g':
                    cac->map[r][c] = char_g[r][c];
                    break;    
                case 'h':
                    cac->map[r][c] = char_h[r][c];
                    break;
                case 'i':
                    cac->map[r][c] = char_i[r][c];
                    break;
                case 'j':
                    cac->map[r][c] = char_j[r][c];
                    break;  
                case 'k':
                    cac->map[r][c] = char_k[r][c];
                    break;    
                case 'l':
                    cac->map[r][c] = char_l[r][c];
                    break;
                case 'm':
                    cac->map[r][c] = char_m[r][c];
                    break;
                case 'n':
                    cac->map[r][c] = char_n[r][c];
                    break;
                case 'o':
                    cac->map[r][c] = char_o[r][c];
                    break;    
                case 'p':
                    cac->map[r][c] = char_p[r][c];
                    break;   
                case 'q':
                    cac->map[r][c] = char_q[r][c];
                    break;    
                case 'r':
                    cac->map[r][c] = char_r[r][c];
                    break;
                case 's':
                    cac->map[r][c] = char_s[r][c];
                    break;
                case 't':
                    cac->map[r][c] = char_t[r][c];
                    break;    
                case 'u':
                    cac->map[r][c] = char_u[r][c];
                    break;
                case 'v':
                    cac->map[r][c] = char_v[r][c];
                    break;    
                case 'w':
                    cac->map[r][c] = char_w[r][c];
                    break;    
                case 'x':
                    cac->map[r][c] = char_x[r][c];
                    break;    
                case 'y':
                    cac->map[r][c] = char_y[r][c];
                    break;
                case 'z':
                    cac->map[r][c] = char_z[r][c];
                    break; 
                case '1':
                    cac->map[r][c] = char_1[r][c];
                    break;   
                case '2':
                    cac->map[r][c] = char_2[r][c];
                    break;  
                case '3':
                    cac->map[r][c] = char_3[r][c];
                    break;   
                case '4':
                    cac->map[r][c] = char_4[r][c];
                    break;   
                case '5':
                    cac->map[r][c] = char_5[r][c];
                    break;   
                case '6':
                    cac->map[r][c] = char_6[r][c];
                    break;   
                case '7':
                    cac->map[r][c] = char_7[r][c];
                    break;   
                case '8':
                    cac->map[r][c] = char_8[r][c];
                    break;   
                case '9':
                    cac->map[r][c] = char_9[r][c];
                    break;   
                case '0':
                    cac->map[r][c] = char_0[r][c];
                    break;    
                default:
                    break;
            }
        }
    }
    
    return cac;
}

int** CALetter(char c)
{
    if(!cachar_array)
    {
        cachar_array =  malloc(sizeof(CAChar) * (26 + 10));
        
        for(int i=0; i<26+10; i++)
            cachar_array[i] = NULL;
    }
    
    int val = c - 97;
    
    if(c < 58)
        val = 26 + c - 48;
                    
    if(!cachar_array[val])
        cachar_array[val] = CACharMake(c);
    
    return cachar_array[val]->map;
}