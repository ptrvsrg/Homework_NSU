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

TStack CreateStack()
{
    return NULL;
}

bool IsEmptyStack(TStack stack)
{
    return stack == NULL;
}

void PushStack(TValue value, TStack* stack)
{
    TStack new = malloc(sizeof(*new));
    assert(!IsEmptyStack(new));

    new->Value = value;
    new->Next = *stack;
    *stack = new;
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

TStack ReverseStack(TStack stack)
{
    TStack result = NULL;

    while(stack)
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
    queue.Begin = CreateStack();
    queue.End = CreateStack();

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

void ScanQueue(size_t size, TQueue* queue)
{
    for(size_t i = 0; i < size; ++i)
    {
        int value;
        assert(scanf("%d", &value) == 1);
        PushQueue(value, queue);
    }
}

void PrintQueue(TQueue queue)
{
    PrintStack(queue.End);
    PrintStack(ReverseStack(queue.Begin));
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
    TQueue queue = CreateQueue();

    ScanQueue(3, &queue);

    PrintQueue(queue);
    printf("\n");

    PushQueue(PopQueue(&queue), &queue);

    PrintQueue(queue);
    printf("\n");
    
    FreeQueue(&queue);
}