#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

void PushStack(TValue value, TStack* stack)
{
    TStack new = CreateItem(value);
    new->Next = *stack;
    (*stack) = new;
}

TValue PopStack(TStack* stack)
{
    assert(!IsEmptyStack(*stack));

    TValue value = (*stack)->Value;

    TStack removeElem = *stack;
    *stack = (*stack)->Next;

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

TStack ConvertArrayToStack(size_t arraySize, TValue* array)
{
    if (arraySize == 0)
    {
        return NULL;
    }

    TStack stack = CreateItem(*array);
    stack->Next = ConvertArrayToStack(arraySize - 1, array + 1);

    return stack;
}

void PrintStack(TStack stack)
{
    if(!IsEmptyStack(stack))
    {
        printf("%d ", stack->Value);
        PrintStack(stack->Next);
    }
}

TStack ReverseStack(TStack stack)
{
    TStack result = NULL;

    while(!IsEmptyStack(stack))
    {
        PushStack(stack->Value, &result);
        stack = stack->Next;
    }

    return result;
}

typedef struct TQueue
{
    TStack Begin;
    TStack End;
} TQueue;

TQueue CreateQueue()
{
    TQueue queue;
    queue.Begin = NULL;
    queue.End = NULL;

    return queue;
}

TQueue ConvertArrayToQueue(size_t arraySize, TValue* array)
{
    TQueue queue = CreateQueue();
    queue.Begin = ConvertArrayToStack(arraySize, array);
    return queue;
}

bool IsEmptyQueue(TQueue queue)
{
    return IsEmptyStack(queue.Begin) && IsEmptyStack(queue.End);
}

void PushQueue(TValue value, TQueue* queue)
{
    PushStack(value, &queue->Begin);
}

void MoveBeginToEnd(TQueue* queue)
{
    FreeStack(&queue->End);
    queue->End = ReverseStack(queue->Begin);
    FreeStack(&queue->Begin);
}

TValue PopQueue(TQueue* queue)
{
    if(IsEmptyStack(queue->End))
    {
        MoveBeginToEnd(queue);
    }

    return PopStack(&queue->End);
}

void PrintQueue(TQueue queue)
{
    PrintStack(queue.End);
    PrintStack(ReverseStack(queue.Begin));
}

void FreeQueue(TQueue* queue)
{
    FreeStack(&queue->Begin);
    FreeStack(&queue->End);
}

int main(void)
{
    TValue array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    TQueue queue = ConvertArrayToQueue(sizeof(array) / sizeof(*array), array);

    PrintQueue(queue);
    printf("\n");

    PushQueue(PopQueue(&queue), &queue);

    PrintQueue(queue);
    printf("\n");
    
    FreeQueue(&queue);
}