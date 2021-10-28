#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Tstack 
{
    float Value;
    struct Tstack* Next;
};

typedef struct Tstack* TStack;

void Push(float value, TStack* stack)
{
    TStack new = malloc(sizeof(*new));
    assert(new != NULL);

    new->Value = value;
    new->Next = *stack;
    *stack = new;
}

float Pop(TStack* stack)
{
    assert(*stack);

    float value = (*stack)->Value;

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

float CalcPostfix(const char* postfixNotation)
{
    TStack numberStack = NULL;

    while(*postfixNotation)
    {
        if(IsDigit(*postfixNotation))
        {
            Push(SymbolToDigit(*postfixNotation), &numberStack);
        }
        else
        {
            float a = Pop(&numberStack);
            float b = Pop(&numberStack);
            Push(GetExpressionValue(*postfixNotation, b, a), &numberStack);
        }

        ++postfixNotation;
    }

    float answer = Pop(&numberStack);

    assert(!numberStack);

    return answer;
}

int main(void)
{
    char* postfixNotation1 = "43-12+/";
    char* postfixNotation2 = "/";
    
    printf("%s = %f\n", postfixNotation1, CalcPostfix(postfixNotation1));
    printf("%s = %f\n", postfixNotation2, CalcPostfix(postfixNotation2));

    return 0;
}