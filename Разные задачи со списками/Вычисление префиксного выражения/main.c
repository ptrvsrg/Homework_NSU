#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void Push(char value, TStack* list)
{
    TStack new = CreateItem(value);
    new->Next = *list;
    (*list) = new;
}

TStack ConvertArrayToStack(size_t arraySize, char* array)
{
    if (arraySize == 0)
    {
        return NULL;
    }

    TStack list = CreateItem(*array);
    list->Next = ConvertArrayToStack(arraySize - 1, array + 1);

    return list;
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

bool IsDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

int SymbolToDigit(char symbol)
{
    return symbol - '0';
}

int GetExpressionValue(char operator, int first, int second)
{
    switch(operator)
    {
        case '+': return first + second;
        case '-': return first - second;
        case '*': return first * second;
        case '/':
            assert(second != 0);
            return first / second;
    }

    assert(false);
    return -1;
}

int CalcPrefix(TStack* prefix)
{
    char symbol = Pop(prefix);

    if(IsDigit(symbol))
    {
        return SymbolToDigit(symbol);
    }
    else
    {
        int first = CalcPrefix(prefix);
        int second = CalcPrefix(prefix);
        return GetExpressionValue(symbol, first, second);
    }
}

int main(void)
{
    char* prefix1 = "/*432";
    char* prefix2 = "2";

    TStack stack1 = ConvertArrayToStack(strlen(prefix1), prefix1);
    TStack stack2 = ConvertArrayToStack(strlen(prefix2), prefix2);
    
    printf("%s = %d\n", prefix1, CalcPrefix(&stack1));
    printf("%s = %d\n", prefix2, CalcPrefix(&stack2));

    return 0;
}