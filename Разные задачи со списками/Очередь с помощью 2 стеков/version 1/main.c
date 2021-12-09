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

void PushStack(TValue value, TStack* stack)
{
    TStack new = CreateItem(value);
    new->Next = *stack;
    (*stack) = new;
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

void PrintStack(TStack stack)
{
    if(!IsEmptyStack(stack))
    {
        printf("%d ", stack->Value);
        PrintStack(stack->Next);
    }
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

bool IsEmptyQueue(TQueue queue)
{
    return queue.Begin == NULL && queue.End == NULL;
}

void PushQueue(TValue value, TQueue* queue)
{
    PushStack(value, &queue->Begin);
}

void MoveBeginToEnd(TQueue* queue)
{
    while(!IsEmptyStack(queue->Begin))
    {
        PushStack(PopStack(&queue->Begin), &queue->End);
    }
}

TValue PopQueue(TQueue* queue)
{
    if(IsEmptyStack(queue->End))
    {
        MoveBeginToEnd(queue);
    }

    return PopStack(&queue->End);
}

TQueue ConvertArrayToQueue(size_t arraySize, TValue* array)
{
    TQueue queue = CreateQueue();
    queue.Begin = ConvertArrayToStack(arraySize, array);
    return queue;
}

void PrintQueue(TQueue* queue)
{
    TQueue buffer = CreateQueue();

    while(!IsEmptyQueue(*queue))
    {
        TValue value = PopQueue(queue);
        printf("%d ", value);
        PushQueue(value, &buffer);
    }

    *queue = buffer;
}

void FreeQueue(TQueue* queue)
{
    while(!IsEmptyQueue(*queue))
    {
        PopQueue(queue);
    }
}

int main(void)
{
    TValue array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    TQueue queue = ConvertArrayToQueue(sizeof(array) / sizeof(*array), array);

    PrintQueue(&queue);
    printf("\n");

    PushQueue(PopQueue(&queue), &queue);

    PrintQueue(&queue);
    printf("\n");
    
    FreeQueue(&queue);
}