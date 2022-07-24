#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tstack 
{
    int Value;
    struct Tstack* Next;
};

typedef struct Tstack* TStack;

bool IsEmptyStack(TStack list)
{
    return list == NULL;
}

TStack CreateItem(int value)
{
    TStack new = malloc(sizeof(*new));
    assert(!IsEmptyStack(new));

    new->Value = value;
    new->Next = NULL;
    
    return new;
}

TStack Push(int value, TStack* list)
{
    TStack new = CreateItem(value);
    new->Next = *list;
    (*list) = new;

    return *list;
}

TStack GetNext(TStack stack)
{
    assert(!IsEmptyStack(stack));
    return stack->Next;
}

int Pop(TStack* stack)
{
    assert(!IsEmptyStack(*stack));

    int value = (*stack)->Value;

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

int Fabs(int num)
{
    return (num >= 0) ? num : -num;
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
        default: assert(false);
    }
}

int CalcPostfix(TStack postfix)
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
            int a = Pop(&numberStack);
            int b = Pop(&numberStack);
            Push(GetExpressionValue(postfix->Value, b, a), &numberStack);
        }

        postfix = GetNext(postfix);
    }

    int answer = Pop(&numberStack);

    assert(IsEmptyStack(numberStack));

    return answer;
}

int main(void)
{
    char* postfix1 = "43-12+/";
    char* postfix2 = "/";

    TStack stack1 = ConvertArrayToStack(strlen(postfix1), postfix1);
    TStack stack2 = ConvertArrayToStack(strlen(postfix2), postfix2);

    printf("%s = %f\n", postfix1, CalcPostfix(stack1));
    printf("%s = %f\n", postfix2, CalcPostfix(stack2));

    return 0;
}
