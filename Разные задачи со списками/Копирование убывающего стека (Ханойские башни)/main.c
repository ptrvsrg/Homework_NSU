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

bool IsEmptyStack(TStack stack)
{
    return stack == NULL;
}

TStack CreateItem(TValue value)
{
    TStack new = malloc(sizeof(*new));
    assert(!IsEmptyStack(new));

    new->Value = value;
    new->Next = NULL;
    
    return new;
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
    if(!IsEmptyStack(*stack))
    {
        assert(value < GetValueStack(*stack));
    }

    TStack new = CreateItem(value);
    new->Next = *stack;
    *stack = new;
}

TValue PopStack(TStack* stack)
{
    assert(!IsEmptyStack(*stack));

    TValue value = GetValueStack(*stack);

    TStack removeElem = *stack;
    *stack = GetNextStack(*stack);

    free(removeElem);

    return value;
}

void FreeStack(TStack* stack) 
{
    while (!IsEmptyStack(*stack))
    {
        PopStack(stack);
    }
}

void PrintStack(TStack stack)
{
    if(!IsEmptyStack(stack))
    {
        printf("%d ", stack->Value);
        PrintStack(stack->Next);
    }
}

size_t GetSizeStack(TStack stack)
{
    if(IsEmptyStack(stack))
    {
        return 0;
    }
    else
    {
        return 1 + GetSizeStack(stack->Next);
    }
}

TStack ConvertArrayToStack(size_t arraySize, TValue* array)
{
    if (arraySize == 0)
    {
        return NULL;
    }

    TStack list = CreateItem(*array);
    list->Next = ConvertArrayToStack(arraySize - 1, array + 1);

    return list;
}

void HanoiTowers(size_t size, TStack* stack1, TStack* buffer, TStack* stack2)
{
    if(size == 0)
    {
        return;
    }
    else
    {
        HanoiTowers(size-1, stack1, stack2, buffer);
        PushStack(GetValueStack(*stack1), stack2);
        *stack1 = GetNextStack(*stack1);
        HanoiTowers(size-1, buffer, stack1, stack2);
    }
}

void CopyStack(TStack stack1, TStack* stack2)
{
    TStack buffer = NULL;
    FreeStack(stack2);
    *stack2 = NULL;
    HanoiTowers(GetSizeStack(stack1), &stack1, &buffer, stack2);
}

int main(void)
{
    int array1[] = { 1, 2, 3 };
    int array2[] = { 0 };

    TStack stack1 = ConvertArrayToStack(sizeof(array1)/sizeof(*array1), array1);
    TStack stack2 = ConvertArrayToStack(sizeof(array2)/sizeof(*array2), array2);

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