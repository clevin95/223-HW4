#include <stdbool.h>


typedef struct stack *Stack;

int createS (Stack *stk);

int isEmptyS (Stack *stk);

int pushS (Stack *stk, char *s);

int popS (Stack *stk, char **s);

int topS (Stack *stk, char **s);

int destroyS (Stack *stk);

