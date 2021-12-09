#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Tstack 
{
    char Value;
    struct Tstack* Next;
};

typedef struct Tstack* TStack;

bool IsEmptyStack(TStack list)
{
    return list == NULL;
}

TStack CreateItem(char value)
{
    TStack new = malloc(sizeof(*new));
    assert(!IsEmptyStack(new));

    new->Value = value;
    new->Next = NULL;
    
    return new;
}

TStack Push(char value, TStack* list)
{
    TStack new = CreateItem(value);
    new->Next = *list;
    (*list) = new;

    return *list;
}

char Pop(TStack* stack)
{
    assert(!IsEmptyStack(*stack));

    char value = (*stack)->Value;

    TStack removeElem = *stack;
    *stack = (*stack)->Next;

    free(removeElem);

    return value;
}

void FreeStack(TStack* stack) 
{
    while (!IsEmptyStack(*stack))
    {
        Pop(stack);
    }
}

bool IsStartBrackets(char symbol)
{
    return symbol == '(' || symbol == '[' || symbol == '{';
}

bool IsEndBrackets(char symbol)
{
    return symbol == ')' || symbol == ']' || symbol == '}';
}

bool IsMatch(char symbol1, char symbol2)
{
    switch(symbol1)
    {
        case '(': return symbol2 == ')';
        case '{': return symbol2 == '}';
        case '[': return symbol2 == ']';
        default: return false;
    }
}

void CheckBrackets(const char* line)
{
    TStack stack = NULL;

    while(*line)
    {
        if(IsEndBrackets(*line))
        {
            if(!stack || !IsMatch(Pop(&stack), *line))
            {
                printf("not OK\n");
                return;
            }
        }
        else if(IsStartBrackets(*line))
        {
            Push(*line, &stack);
        }
        
        ++line;
    }

    if(!IsEmptyStack(stack))
    {
        printf("not OK\n");
        FreeStack(&stack);
        return;
    }

    printf("OK\n");
}

int main(void)
{
    char* line1 = "[[[[[ыcccccccccccc]]]]]";
    char* line2 = "{";
    char* line3 = "[{])";

    CheckBrackets(line1);
    CheckBrackets(line2);
    CheckBrackets(line3);

    return 0;
}