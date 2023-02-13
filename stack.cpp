#include "stack.h"
#include <stdarg.h>

int main() {

    const int size = 700;

    stack st = {};
    
    StackCtor(&st);
    _StackDump(&st);

    for (int i = 0; i < size; i++)
        StackPush(&st, i + 1.5);

    _StackDump(&st);

    for (int i = 0; i < size; i++)
        StackPop(&st);
        
    StackPush(&st, 1);
    StackPush(&st, 2);
    StackPush(&st, 3);
    StackPush(&st, 4);

    _StackDump(&st);
    _StackCheck(&st);
    StackDtor(&st);
    _StackDump(&st);

    return 0;
}