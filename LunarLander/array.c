//
//  array.c
//  LunarLander
//
//  Created by Carter Appleton on 4/3/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array arrayMake(int length)
{
    Array a = malloc(sizeof(struct array));
    
    a->data = malloc(sizeof(int) * length);
    a->length = length;
    a->count = 0;
    
    return a;
}

Array arrayMakeFromArray(int length, int* array)
{
    Array a = arrayMake(length);
    
    for(int i=0; i<length; i++)
        arrayAdd(array[i], a);
    
    return a;
}

void arrayFree(Array a)
{
    free(a->data);
    free(a);
}

int arrayIsIndexValid(int index, Array a)
{
    return index >= 0 && index < a->count;
}

void arrayAdd(int value, Array a)
{
    if(a->count < a->length)
    {
        a->data[a->count] = value;
        a->count++;
        return;
    }
    
    int* tmp = malloc(sizeof(int) * a->length * 2);
    
    for(int i=0; i<a->count; i++)
        tmp[i] = a->data[i];
    
    free(a->data);
    
    a->data = tmp;
    a->length *= 2;
    tmp = NULL;
    
    arrayAdd(value, a);
}

void arrayReplaceAtIndex(int value, int index, Array a)
{
    if(!arrayIsIndexValid(index, a))
        return;
    
    a->data[index] = value;
}

int arrayValueAtIndex(int index, Array a)
{
    if(!arrayIsIndexValid(index, a))
        return -1;
    
    return a->data[index];
}

int arrayRemoveAtIndex(int index, Array a)
{
    if(!arrayIsIndexValid(index, a))
        return -1;
    
    int tmp = a->data[index];
    
    for(int i=index; i<a->count-1; i++)
        a->data[i] = a->data[i+1];
    
    a->count--;
    
    return tmp;
}

void arrayPrint(Array a)
{
    printf("Array c[%d] = {",a->count);
    for(int i=0; i<a->count; i++)
        printf("%d,",arrayValueAtIndex(i, a));
    printf("}\n");
}

