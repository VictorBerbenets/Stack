#include "stack.h"

int main(){

    stack st;

    Data arr[100];

    const int size = 51;
    
    StackCtor(&st);


    for (int i = 0; i < size; i++)
        StackPush(&st, i + 1.443245);

    _StackDump(&st);

    for (int i = 0; i < size; i++)
        arr[i] = StackPop(&st);

    StackPush(&st, 54.23);
    StackPush(&st, 54.543);

    _StackDump(&st);

    StackDtor(&st);

    return 0;
}