//
//  array.h
//  LunarLander
//
//  Created by Carter Appleton on 4/3/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#ifndef LunarLander_array_h
#define LunarLander_array_h

typedef struct array
{
    int* data;
    int length;
    int count;
} array;
typedef array* Array;

Array arrayMake(int length);
Array arrayMakeFromArray(int length, int* array);
void arrayFree(Array a);

int arrayIsIndexValid(int index, Array a);

void arrayAdd(int value, Array a);
void arrayReplaceAtIndex(int value, int index, Array a);
int arrayValueAtIndex(int index, Array a);
int arrayRemoveAtIndex(int index, Array a);

void arrayPrint(Array a);


#endif
