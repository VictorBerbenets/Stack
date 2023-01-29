#ifndef Stack_program
#define Stack_program


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#include "stack_defense.h"

typedef double Data;


#define _StackDump(st) StackDump(st, __LINE__, __PRETTY_FUNCTION__, #st)
#define _StackCheck(st) StackCheck(st, __LINE__, __PRETTY_FUNCTION__, __FILE__)

const Data Epsilon = 1e-17;

typedef struct{

    Data canary_1 ;
    Data* data    ;
    Data* data_ptr;  
    size_t size   ;         // сколько реально лежит элементов в стеке
    size_t capacity;        // Сколько может вместить участок памяти, который я выделил для стека
    size_t hash_stk;        // st.size + st.capacity
    Data   hash_data;      // Сумма элементов в стеке
    char stack_is_damaged;
    Data canary_2;

} stack;


enum{
    ElemIsPoison    = 234567,
    NoPoison        = 345678,
    Pop_Is_Ok       = 456789,
    StackNotEmpty   = 0x25,
    StackIsEmpty    = 0x26,
    StackNotFull    = 0x1,
    StackFull       = 0x2,
    POISON          = 0xDEADBABE,
    MinusSize       = 3,
    MinSize         = 2,
    MaxStayedSize   = 5,
    PUSH            = 111,
    POP             = 222
};

enum ErrorCodes{
    NULL_STACK          = 0x325235,
    INVALID_SIZE        = (1 << 1),
    INVALID_CAPACITY    = (1 << 2),
    ElemOfStackIsPoison = (1 << 3),
    STACK_IS_NULLPTR    = (1 << 4),
    

};

void StackDump (stack* st, int line, const char func[], const char* stack_name);

void StackCtor (stack* st);

void StackDtor (stack* st);

void StackPush (stack* st, Data value);

void StackCheck (stack* st, int line, const char* func, const char* file);

Data StackPop (stack* st);

void StackResize(stack* st, int Push_or_Pop);

void StackRecalloc (int Push_or_POP, stack* st, int new_size);

int IsStackEmpty (stack* st);

int IsStackFull (stack* st);

void DoPoison (stack* st);

int IsDataValid(stack* st);

void PrintError (stack* st, int ErrCode, int line, const char* func, const char* file);

int is_equal(Data value1, Data value2);

Data hash_data(stack* st);

size_t hash_stack(stack* st);

#endif