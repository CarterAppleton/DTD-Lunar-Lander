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
                case 'd':
                    cac->map[r][c] = char_d[r][c];
                    break;
                case 'e':
                    cac->map[r][c] = char_e[r][c];
                    break;
                case 'h':
                    cac->map[r][c] = char_h[r][c];
                    break;
                case 'i':
                    cac->map[r][c] = char_i[r][c];
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
                case 'r':
                    cac->map[r][c] = char_r[r][c];
                    break;
                case 's':
                    cac->map[r][c] = char_s[r][c];
                    break;
                case 'u':
                    cac->map[r][c] = char_u[r][c];
                    break;
                case 'y':
                    printf("w %c",ch);

                    cac->map[r][c] = char_y[r][c];
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
        cachar_array =  malloc(sizeof(CAChar) * 26);
        
        for(int i=0; i<26; i++)
            cachar_array[i] = NULL;
    }
    
    int val = c - 97;
                
    if(!cachar_array[val])
        cachar_array[val] = CACharMake(c);
    
    return cachar_array[val]->map;
}