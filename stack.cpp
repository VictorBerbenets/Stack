#include "stack.h"

int main(){

    stack st;

    Data arr[100];
    const int size = 50;
    
    StackCtor(&st);

    _StackDump(&st);

    for (int i = 0; i < size; i++)
        StackPush(&st, i + 1.5);

    _StackDump(&st);

    for (int i = 0; i < size; i++)
        printf("[%d] = %lg\n", i, StackPop(&st));
        
    StackPush(&st, 54.23);
    StackPush(&st, 54.543);
    
    // st.hash_data = 523;

    _StackDump(&st);


    StackDtor(&st);

    // _StackDump(&st);


    return 0;
}