#ifndef Stack_defense
#define Stack_defense

const double Canary_Value = -0XDEDFEED69;
const double Canary_left  =  0xDEADBEEF1;
const double Canary_right =  0xDEADBEEF9;

enum canary_errors {

    STACK_CANARY_LEFT    = (1 << 5),
    STACK_CANARY_RIGHT   = (1 << 6),
    DATA_CANARY_LEFT     = (1 << 7),
    DATA_CANARY_RIGHT    = (1 << 8),
    HASH_DATA_ERROR      = (1 << 9), 
    HASH_STACK_ERROR     = (1 << 10), 
} ;

#endif 