#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

TStack GetNext(TStack stack)
{
    assert(stack->Next);
    return stack->Next;
}

float Pop(TStack* stack)
{
    assert(*stack);

    float value = (*stack)->Value;

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

void ArrayToList(size_t length, const char* line, TStack* stack)
{
    for(size_t i = 0; i < length; ++i)
    {
        Push(line[length - i - 1], stack);
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

float CalcPostfix(TStack postfix)
{
    TStack numberStack = NULL;

    while(postfix)
    {
        if(IsDigit(postfix->Value))
        {
            Push(SymbolToDigit(postfix->Value), &numberStack);
        }
        else
        {
            float a = Pop(&numberStack);
            float b = Pop(&numberStack);
            Push(GetExpressionValue(postfix->Value, b, a), &numberStack);
        }

        postfix = GetNext(postfix);
    }

    float answer = Pop(&numberStack);

    assert(!numberStack);

    return answer;
}

int main(void)
{
    char* postfix1 = "43-12+/";
    char* postfix2 = "/";

    TStack stack1 = NULL;
    TStack stack2 = NULL;

    ArrayToList(strlen(postfix1), postfix1, &stack1);
    ArrayToList(strlen(postfix2), postfix2, &stack2);

    printf("%s = %f\n", postfix1, CalcPostfix(stack1));
    printf("%s = %f\n", postfix2, CalcPostfix(stack2));

    return 0;
}