#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int TValue;

struct Tstack 
{
    TValue Value;
    struct Tstack* Next;
};

typedef struct Tstack* TStack;

TStack CreateStack()
{
    return NULL;
}

bool IsEmpty(TStack stack)
{
    return stack == NULL;
}

TStack GetNextStack(TStack stack)
{
    return stack->Next;
}

TValue GetValueStack(TStack stack)
{
    return stack->Value;
}

void PushStack(TValue value, TStack* stack)
{
    if(!IsEmpty(*stack))
    {
        assert(value < GetValueStack(*stack));
    }

    TStack new = malloc(sizeof(*new));
    assert(!IsEmpty(new));

    new->Value = value;
    new->Next = *stack;
    *stack = new;
}

TValue PopStack(TStack* stack)
{
    assert(!IsEmpty(*stack));

    TValue value = GetValueStack(*stack);

    TStack removeElem = *stack;
    *stack = GetNextStack(*stack);

    free(removeElem);

    return value;
}

void FreeStack(TStack* stack) 
{
    while (!IsEmpty(*stack))
    {
        PopStack(stack);
    }
}

void PrintStack(TStack stack)
{
    if(!IsEmpty(stack))
    {
        printf("%d ", stack->Value);
        PrintStack(stack->Next);
    }
}

size_t GetSizeStack(TStack stack)
{
    if(IsEmpty(stack))
    {
        return 0;
    }
    else
    {
        return 1 + GetSizeStack(stack->Next);
    }
}

void ArrayToStack(size_t arraySize, TValue array[], TStack* stack)
{
    for(size_t i = 0; i < arraySize; ++i)
    {
        PushStack(array[arraySize - 1 - i], stack);
    }
}

void HanoiTowers(size_t size, TStack* stack1, TStack* buffer, TStack* stack2)
{
    if(size == 0)
    {
        return;
    }
    else
    {
        HanoisTower(size-1, stack1, stack2, buffer);
        PushStack(GetValueStack(*stack1), stack2);
        *stack1 = GetNextStack(*stack1);
        HanoisTower(size-1, buffer, stack1, stack2);
    }
}

void CopyStack(TStack stack1, TStack* stack2)
{
    TStack buffer = CreateStack();
    FreeStack(stack2);
    *stack2 = CreateStack();
    HanoiTowers(GetSizeStack(stack1), &stack1, &buffer, stack2);
}

int main(void)
{
    int array1[] = { 1, 2, 3 };
    int array2[] = { 0 };
    TStack stack1 = CreateStack();
    TStack stack2 = CreateStack();

    ArrayToStack(sizeof(array1)/sizeof(*array1), array1, &stack1);
    ArrayToStack(sizeof(array2)/sizeof(*array2), array2, &stack2);

    PrintStack(stack1);
    printf("\n");
    PrintStack(stack2);
    printf("\n");

    CopyStack(stack1, &stack2);

    PrintStack(stack1);
    printf("\n");
    PrintStack(stack2);
    printf("\n");

    FreeStack(&stack1);
    FreeStack(&stack2);

    return 0;
}