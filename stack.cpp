#include "stack.h"
#include <stdarg.h>


int main(){

    stack st;

    Data arr[100];
    const int size = 100;
    
    StackCtor(&st);
    _StackDump(&st);

    // _StackDump(&st);

    for (int i = 0; i < size; i++)
        StackPush(&st, i + 1.5);

    _StackDump(&st);
    // printf("cap = %d\n", st.capacity);

    for (int i = 0; i < size; i++)
        printf("[%d] = %lg\n", i, StackPop(&st));
    printf("size = %d\n", st.size);
    printf("cap = %d\n", st.capacity);
    // st.data = nullptr;
    StackPush(&st, 1);
    StackPush(&st, 2);
    StackPush(&st, 3);
    StackPush(&st, 4);
    // st.data[3] = 2;
    // st.data[2] = 3;
    // st.hash_data = 32;
    // st.hash_stk = 534.53;
    // st.canary_left = 52;
    // st.canary_right = -752;
    _StackDump(&st);
    _StackCheck(&st);
    StackDtor(&st);
    _StackDump(&st);



    return 0;
}