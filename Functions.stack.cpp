#include "stack.h"

#define Grey   "\033[0m"
#define Red    "\033[0;31m"
#define White  "\033[1m"
#define Blue   "\033[0;36m"
#define Under  "\033[4m"

const int Two_canarys = 2;
const int One_canary  = 1;


void StackCtor(stack* st){

    st -> canary_1         = Canary_Value;
    st -> canary_2         = Canary_Value;
    st -> stack_is_damaged = 0;
    st -> hash_data        = 0;
    st -> hash_stk         = 0;

    st -> data             = (Data*) calloc(Two_canarys, sizeof(Data));
    st -> data_ptr         = st -> data  ;
    st -> capacity         = 0;
    st -> size             = 0;

    st -> data[0]          = Canary_Value;
    st -> data[1]          = Canary_Value;
    st -> data ++;
}

void StackDtor(stack* st){ 

    DoPoison(st); 
    
    free(st -> data_ptr);

    st -> data_ptr         = nullptr;
    st -> data             = nullptr;
    st -> size             = 0;
    st -> canary_1         = 0;
    st -> hash_data        = 0;
    st -> hash_stk         = 0;
    st -> stack_is_damaged = 0;
    st -> capacity         = 0;
    st -> canary_2         = 0;
}

void StackPush(stack* st, Data value){

    _StackCheck(st);

    if (IsStackFull(st) == StackFull || st->capacity == 0){
        StackResize(st, PUSH);
    }

    st -> data[st -> size] = value;
    st -> size ++;

    st -> hash_stk  = hash_stack(st);
    st -> hash_data = hash_data(st);

    DoPoison(st);

    _StackCheck(st);
}

Data StackPop (stack* st){

    _StackCheck(st);
    if (st -> size > 0) {

        Data res = 0;
        res = st -> data[(st -> size) - 1];

        if ((st->capacity - st->size) > MaxStayedSize){
            StackResize(st, POP);
        }

        if (IsStackEmpty(st) == StackNotEmpty){
            st -> size --;

            st -> hash_stk  = hash_stack(st);
            st -> hash_data = hash_data(st);

            DoPoison(st);
            
            return res;
        }
    }

    return StackIsEmpty;   
}

void StackResize(stack* st, int Push_or_Pop){

    _StackCheck(st);

    switch(Push_or_Pop){

        case PUSH:{ 
            StackRecalloc(Push_or_Pop, st, st->capacity + (st->size / 2) + 1); // увеличиваем capacity, когда нужно место для Push
            break;
        }
        case POP:{ 
            StackRecalloc(Push_or_Pop, st, st->capacity - MinusSize); // уменьшаем capacity, когда достали много элементов из стэка
            break;
        }   
    }
}

void StackRecalloc (int Push_or_POP, stack* st, int new_size){

    _StackCheck(st);
    st -> capacity           = new_size;
    st -> hash_stk           = hash_stack(st);

    st -> data = (Data*)realloc(st -> data_ptr, sizeof(Data) * (st -> capacity + Two_canarys));

    st -> data_ptr = st -> data;
    st -> data ++;

    st -> data[st -> capacity] = Canary_Value;
}


void StackCheck(stack* st, int line, const char* func, const char* file){ // StackVerificate()

    printf("st->size = %d\n", st->size);
    int err_code = 0;

    if (!(st -> data)) { 
        err_code += STACK_IS_NULLPTR; 
    } 
    else {
        if (st -> data[st -> capacity] != Canary_Value) { err_code += DATA_CANARY_TWO_ERR; }

        if (st -> data[-1] != Canary_Value)             { err_code += DATA_CANARY_ONE_ERR;}

        if (st -> canary_1 != Canary_Value)             { err_code += STACK_CANARY_ONE_ERR; }

        if (st -> canary_2 != Canary_Value)             { err_code += STACK_CANARY_TWO_ERR; }

        if (st -> size < 0)                             { err_code += INVALID_SIZE; }

        else {
            if   (st -> size > st -> capacity)                  { err_code += INVALID_CAPACITY; }
            else {
                if (IsDataValid(st) == ElemIsPoison)            { err_code += ElemOfStackIsPoison; }
                if (!is_equal(st -> hash_data, hash_data(st)))  { err_code += HASH_DATA_ERROR; }
                if (st -> hash_stk != hash_stack(st))           { err_code += HASH_STACK_ERROR; } 
            }
        }

        if (err_code)                                   { st -> stack_is_damaged = 1; }
    }

    PrintError(st, err_code, line, func, file);
}

void PrintError (stack* st, int ErrCode, int line, const char* func, const char* file){

    int number_of_errors = 0;

    if (ErrCode & INVALID_CAPACITY) { 
        fprintf(stderr, ""White"%s:%d:"Grey"In function "White"'%s':"Grey"\n", __FILE__, line, func);
        fprintf(stderr, ""White"%s:%d:"Red" error: "Grey"Size of the Stack > capacity. Size of stack must be '<= capacity' (check log.txt for more information)\n\t|\t"Blue"'st -> size = %d > st ->capacity = %d'"Grey"\n\t|"
        "\n", __FILE__, line, st -> size, st ->capacity);
        number_of_errors ++;
    }
    if (ErrCode & INVALID_SIZE) {
        fprintf(stderr, ""White"%s:%d:"Grey"In function "White"'%s':"Grey"\n", __FILE__, line, func);
        fprintf(stderr, ""White"%s:%d:"Red" error: "Grey"Invalid size of stack. Size of stack must be '> 0' (check log.txt for more information)\n\t|\t"Blue"'st -> size = %d < 0'"Grey"\n\t|\n", __FILE__, line, st -> size);
        number_of_errors ++;
    }
    if (ErrCode & ElemOfStackIsPoison) {
        fprintf(stderr, ""White"%s:%d:"Grey"In function "White"'%s':"Grey"\n", __FILE__, line, func);
        fprintf(stderr, ""White"%s:%d:"Red" error: "Grey"Element of stack is poison(check log.txt for more information)\n", __FILE__, line);
        number_of_errors ++;
    }
    if (ErrCode & STACK_IS_NULLPTR) {
        fprintf(stderr, ""White"%s:%d:"Grey"In function "White"'%s':"Grey"\n", __FILE__, line, func);
        fprintf(stderr, ""White"%s:%d:"Red" error: "Grey"Stack is nullptr(check log.txt for more information)\n\t|\t"Blue"'st = %s'"Grey"\n\t|\n", __FILE__, line, st -> data);
        number_of_errors ++;
    }
    if (ErrCode & DATA_CANARY_ONE_ERR) { 
        fprintf(stderr, ""White"%s:%d:"Grey"In function "White"'%s':"Grey"\n", __FILE__, line, func);
        fprintf(stderr, ""White"%s:%d:"Red" error: "Grey"Canary 1 was damaged(check log.txt for more information)\n\t|\t"Blue"'st[%d] = %lg != %lg'"Grey"\n\t|\n", __FILE__, line, -1, st->data[-1], Canary_Value);
        number_of_errors ++;
    }
    if (ErrCode & DATA_CANARY_TWO_ERR) { 
        fprintf(stderr, ""White"%s:%d:"Grey"In function "White"'%s':"Grey"\n", __FILE__, line, func);
        fprintf(stderr, ""White"%s:%d:"Red" error: "Grey"Canary 2 was damaged(check log.txt for more information)\n\t|\t"Blue"'st[%d] = %lg != %lg'"Grey"\n\t|\n", __FILE__, line, st -> capacity, st->data[st -> capacity], Canary_Value);
        number_of_errors ++;
    }
    if (ErrCode & STACK_CANARY_ONE_ERR) { 
        fprintf(stderr, ""White"%s:%d:"Grey"In function "White"'%s':"Grey"\n", __FILE__, line, func);
        fprintf(stderr, ""White"%s:%d:"Red" error: "Grey"Stack canary 1 was damaged(check log.txt for more information)\n\t|\t"Blue"'st->canary_2 = %lg != %lg'"Grey"\n\t|\n", __FILE__, line, st->canary_1, Canary_Value);
        number_of_errors ++;
    }
    if (ErrCode & STACK_CANARY_TWO_ERR) { 
        fprintf(stderr, ""White"%s:%d:"Grey"In function "White"'%s':"Grey"\n", __FILE__, line, func);
        fprintf(stderr, ""White"%s:%d:"Red" error: "Grey"Stack canary 2 was damaged(check log.txt for more information)\n\t|\t"Blue"'st->canary_2 = %lg != %lg'"Grey"\n\t|\n", __FILE__, line, st->canary_2, Canary_Value);
        number_of_errors ++;
    }
    if (ErrCode & HASH_STACK_ERROR) {
        fprintf(stderr, ""White"%s:%d:"Grey"In function "White"'%s':"Grey"\n", __FILE__, line, func);
        fprintf(stderr, ""White"%s:%d:"Red" error: "Grey"Hash of stack was damaged(check log.txt for more information)\n\t|\t"Blue"'hash_stk = %zd != %zd'"Grey"\n\t|\n", __FILE__, line, st -> hash_stk, hash_stack(st));
        number_of_errors ++;
    }
    if (ErrCode & HASH_DATA_ERROR) {
        fprintf(stderr, ""White"%s:%d:"Grey"In function "White"'%s':"Grey"\n", __FILE__, line, func);
        fprintf(stderr, ""White"%s:%d:"Red" error: "Grey"Hash of data was damaged(check log.txt for more information)\n\t|\t"Blue"'hash_data = %lg != %lg'"Grey"\n\t|\n", __FILE__, line, st -> hash_data, hash_data(st));
        number_of_errors ++;
    }

    if (ErrCode) {
        StackDtor(st);
        exit(EXIT_FAILURE);
    }
}

int IsStackFull(stack* st){

    _StackCheck(st);
    
    if (st -> size ==  st -> capacity)
        return StackFull;
    return StackNotFull;
}


int IsStackEmpty(stack* st){

    _StackCheck(st);

    if ((st -> size == 0))
        return StackIsEmpty;
    return StackNotEmpty;
}

void DoPoison(stack*st){

    int difference = st->capacity - st->size;

    for (int stack_number = 0; stack_number < difference; stack_number++) {
        st->data[st->size + stack_number] = POISON;
    }
}

int IsDataValid(stack* st){  // IsDataValid

    int stack_number = 0;

    for ( ; stack_number < st->size; stack_number++){
        if (st->data[stack_number] == POISON){
            return ElemIsPoison;
        }
    }
    return NoPoison;
}

Data hash_data(stack* st) {

    Data stk_summa = 0;
    for (int st_number = 0; st_number < st -> size; st_number++) {
        stk_summa += st -> data[st_number];
    }

    return stk_summa;
}

int is_equal(Data value1, Data value2) {

    return (fabs(value1 - value2) < Epsilon);
}

int hash_stack(stack* st) {

    return (st -> size + st -> capacity);
}

void StackDump (stack* st, int line, const char func[], const char* stack_name)
{          
    /*Вывод общей информации*/
    _StackCheck(st);
    FILE* log_txt = fopen("log.txt", "a");

    fprintf(log_txt, "\n***********************************************************************************\n");

    fprintf(log_txt, "StackDump was called from '%d' line and function: '%s'\n", line, func);
    fprintf(log_txt, "Stack name: %s\n",                          stack_name);
    fprintf(log_txt, "\t\tElements in stack(st.size):   %d\n",     st->size);
    fprintf(log_txt, "\t\tStack capacity:               %d\n", st->capacity); 
    fprintf(log_txt, "\t\tStack pointer(data):          %X\n",      st->data);
    fprintf(log_txt, "\t\tStack is damaged?:           <%s>\n", st -> stack_is_damaged == 1 ? "YES":"NO");
    fprintf(log_txt, "%s\n", st->capacity == 0 ? "Stack is empty":"Elements in stack:");

    fprintf(log_txt, " [%d] = %lg Canary_1\n", -1, st ->data[-1]);
    for (int stack_number = 0; stack_number < st->capacity; stack_number++){

        if (st->data[stack_number] != POISON){
            fprintf(log_txt, "*[%d] = %lg\n", stack_number, st->data[stack_number]);
        }
        else {
            fprintf(log_txt, " [%d] = %lg POISON\n", stack_number, st->data[stack_number]);
        }
    }
    fprintf(log_txt, " [%d] = %lg Canary_2\n", st ->capacity, st ->data[st -> capacity]);
    fprintf(log_txt, "************************************************************************************\n\n");

    fclose(log_txt);
}