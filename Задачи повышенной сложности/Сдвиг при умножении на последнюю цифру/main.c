#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Tstack* TStack;

struct Tstack 
{
    int Value;
    TStack Next;
};

TStack CreateStack(void)
{
    return NULL;
}

bool IsEmptyStack(TStack stack)
{
    return stack == NULL;
}

TStack CreateItem(int value)
{
    TStack new = malloc(sizeof(*new));
    assert(!IsEmptyStack(new));

    new->Value = value;
    new->Next = NULL;
    
    return new;
}

void PushStack(int value, TStack* stack)
{
    TStack new = CreateItem(value);
    new->Next = *stack;
    (*stack) = new;
}

int GetTopStack(TStack stack)
{
    assert(!IsEmptyStack(stack));
    return stack->Value;
}

int PopStack(TStack* stack)
{
    assert(!IsEmptyStack(*stack));

    int value = GetTopStack(*stack);

    TStack removeElem = *stack;
    *stack = (*stack)->Next;

    free(removeElem);

    return value;
}

void PrintStack(TStack stack)
{
    if(!IsEmptyStack(stack))
    {
        printf("%d", stack->Value);
        PrintStack(stack->Next);
    }
}

void DestroyStack(TStack* stack) 
{
    while (!IsEmptyStack(*stack))
    {
        PopStack(stack);
    }
}

TStack GenerateNumber(int lastDigit)
{
    TStack stack = CreateStack();
    int additionalDigit = 0;
    int digit = lastDigit;
    
    do
    {
        PushStack(digit, &stack);
        int stackDigit = GetTopStack(stack);
        digit = (stackDigit * lastDigit + additionalDigit) % 10;
        additionalDigit = (stackDigit * lastDigit + additionalDigit) / 10;
    } while (digit != lastDigit || additionalDigit != 0);
    
    return stack;
}

int main(void)
{
    for (int i = 0; i < 10; ++i)
    {
        TStack number = GenerateNumber(i);
        printf("%d) ", i);
        PrintStack(number);
        printf("\n");
        DestroyStack(&number);
    }
    
    return EXIT_SUCCESS;
}