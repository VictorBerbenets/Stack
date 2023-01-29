#include "stack.h"

int main(){

    stack st;

    Data arr[100];
    const int size = 100;
    
    StackCtor(&st);

    _StackDump(&st);

    for (int i = 0; i < size; i++)
        StackPush(&st, i + 1.5);

    _StackDump(&st);

    for (int i = 0; i < size; i++)
        printf("[%d] = %lg\n", i, StackPop(&st));
        
    StackPush(&st, 54.23);
    StackPush(&st, 54.543);
    
    // st.hash_data = 32;
    // st.hash_stk  = -354.5243;
    // st.canary_1  = -5235.52;
    // st.canary_2  = -325235.523;

    _StackDump(&st);


    StackDtor(&st);

    // _StackDump(&st);


    return 0;
}