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

TValue Pop(TStack* stack)
{
    assert(*stack);

    TValue value = (*stack)->Value;

    TStack removeElem = *stack;
    *stack = (*stack)->Next;

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

float Fabs(float num)
{
    return (num >= 0) ? num : -num;
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
            assert(Fabs(second) > 1E-6);
            return first / second;
        default: assert(false);
    }
}

float CalcPrefix(TStack* prefix)
{
    char symbol = Pop(prefix);

    if(IsDigit(symbol))
    {
        return SymbolToDigit(symbol);
    }
    else
    {
        float first = CalcPrefix(prefix);
        float second = CalcPrefix(prefix);
        return GetExpressionValue(symbol, first, second);
    }
}

int main(void)
{
    char* prefix1 = "/*432";
    char* prefix2 = "2";
    TStack stack1 = NULL;
    TStack stack2 = NULL;

    ArrayToList(strlen(prefix1), prefix1, &stack1);
    ArrayToList(strlen(prefix2), prefix2, &stack2);
    
    printf("%s = %f\n", prefix1, CalcPrefix(&stack1));
    printf("%s = %f\n", prefix2, CalcPrefix(&stack2));

    return 0;
}