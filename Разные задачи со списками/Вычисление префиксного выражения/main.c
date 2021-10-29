#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char TValue;

struct Tstack 
{
    TValue Value;
    struct Tstack* Next;
};

typedef struct Tstack* TStack;

void Push(TValue value, TStack* stack)
{
    TStack new = malloc(sizeof(*new));
    assert(new != NULL);

    new->Value = value;
    new->Next = *stack;
    *stack = new;
}

TStack GetNext(TStack stack)
{
    assert(stack);
    return stack->Next;
}

TValue Pop(TStack* stack)
{
    assert(*stack);

    TValue value = (*stack)->Value;

    TStack removeElem = *stack;
    *stack = GetNext(*stack);

    free(removeElem);

    return value;
}

void FreeStack(TStack* stack) 
{
    while (*stack)
    {
        Pop(stack);
    }
}

void ArrayToList(size_t arraySize, TValue* array, TStack* stack)
{
    for(size_t i = 0; i < arraySize; ++i)
    {
        Push(array[arraySize - 1 - i], stack);
    }
}

bool IsDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

float SymbolToDigit(char symbol)
{
    return symbol - '0';
}

float GetExpressionValue(char operator, float first, float second)
{
    switch(operator)
    {
        case '+': return first + second;
        case '-': return first - second;
        case '*': return first * second;
        case '/':
            assert(second > 1E-6);
            return first / second;
        default: assert(false);
    }
}

float CalcPrefix(TStack* prefix)
{
    assert(!IsDigit((*prefix)->Value));

    char operator = Pop(prefix);
    float first;
    float second;

    assert(*prefix);
    if(IsDigit((*prefix)->Value))
    {
        first = SymbolToDigit(Pop(prefix));
    }
    else
    {
        first = CalcPrefix(prefix);
    }

    assert(*prefix);
    if(IsDigit((*prefix)->Value))
    {
        second = SymbolToDigit(Pop(prefix));
    }
    else
    {
        second = CalcPrefix(prefix);
    }

    return GetExpressionValue(operator, first, second);
}

int main(void)
{
    char* prefix1 = "/*32-51";
    char* prefix2 = "/";
    TStack stack1 = NULL;
    TStack stack2 = NULL;

    ArrayToList(strlen(prefix1), prefix1, &stack1);
    ArrayToList(strlen(prefix2), prefix2, &stack2);
    
    printf("%s = %f\n", prefix1, CalcPrefix(&stack1));
    printf("%s = %f\n", prefix2, CalcPrefix(&stack2));

    return 0;
}