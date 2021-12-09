#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tstack 
{
    float Value;
    struct Tstack* Next;
};

typedef struct Tstack* TStack;

bool IsEmptyStack(TStack list)
{
    return list == NULL;
}

TStack CreateItem(float value)
{
    TStack new = malloc(sizeof(*new));
    assert(!IsEmptyStack(new));

    new->Value = value;
    new->Next = NULL;
    
    return new;
}

TStack Push(float value, TStack* list)
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

float Pop(TStack* stack)
{
    assert(!IsEmptyStack(*stack));

    float value = (*stack)->Value;

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

float Fabs(float num)
{
    return (num >= 0) ? num : -num;
}

bool IsDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

float SymbolToDigit(char symbol)
{
    return symbol - '0';
}

float GetExpressionValue(char operator, float first, float second)
{
    switch(operator)
    {
        case '+': return first + second;
        case '-': return first - second;
        case '*': return first * second;
        case '/':
            assert(Fabs(second) > 1E-6);
            return first / second;
        default: assert(false);
    }
}

float CalcPostfix(TStack postfix)
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
            float a = Pop(&numberStack);
            float b = Pop(&numberStack);
            Push(GetExpressionValue(postfix->Value, b, a), &numberStack);
        }

        postfix = GetNext(postfix);
    }

    float answer = Pop(&numberStack);

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
