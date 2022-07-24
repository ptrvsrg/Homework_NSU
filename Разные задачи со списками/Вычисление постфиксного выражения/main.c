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

TStack GetNext(TStack stack)
{
    assert(!IsEmptyStack(stack));
    return stack->Next;
}

char Pop(TStack* stack)
{
    assert(!IsEmptyStack(*stack));

    char value = (*stack)->Value;

    TStack removeElem = *stack;
    *stack = GetNext(*stack);

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

int CalcPostfix(TStack postfix)
{
    TStack numberStack = NULL;

    while(postfix)
    {
        if(IsDigit(postfix->Value))
        {
            Push((char)SymbolToDigit(postfix->Value), &numberStack);
        }
        else
        {
            int a = (int)Pop(&numberStack);
            int b = (int)Pop(&numberStack);
            Push((char)GetExpressionValue(postfix->Value, b, a), &numberStack);
        }

        postfix = GetNext(postfix);
    }

    int answer = (int)Pop(&numberStack);

    assert(IsEmptyStack(numberStack));

    return answer;
}

int main(void)
{
    char* postfix1 = "43-12+/";
    char* postfix2 = "/";

    TStack stack1 = ConvertArrayToStack(strlen(postfix1), postfix1);
    TStack stack2 = ConvertArrayToStack(strlen(postfix2), postfix2);

    printf("%s = %d\n", postfix1, CalcPostfix(stack1));
    printf("%s = %d\n", postfix2, CalcPostfix(stack2));

    return 0;
}
