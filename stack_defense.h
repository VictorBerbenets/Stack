#ifndef Stack_defense
#define Stack_defense

const double Canary_Value = -0XDEDFEED69;

enum canary_errors {

    STACK_CANARY_ONE_ERR = (1 << 5),
    STACK_CANARY_TWO_ERR = (1 << 6),
    DATA_CANARY_ONE_ERR  = (1 << 7),
    DATA_CANARY_TWO_ERR  = (1 << 8),
    HASH_DATA_ERROR      = (1 << 9), 
    HASH_STACK_ERROR     = (1 << 10), 
} ;

#endif 