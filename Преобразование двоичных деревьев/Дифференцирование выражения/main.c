#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////  VALUE  ////////////////////////////////

typedef struct TValue
{
    char Operator;
    char Variable;
    int Number;
} TValue;

TValue CreateValue(char operator, char variable, int number)
{
    TValue new;
    new.Operator = operator;
    new.Variable = variable;
    new.Number = number;
    return new;
}

////////////////////////////////  STACK  ////////////////////////////////

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

TValue GetTopStack(TStack stack)
{
    assert(!IsEmptyStack(stack));
    return stack->Value;
}

TValue PopStack(TStack* stack)
{
    assert(!IsEmptyStack(*stack));

    TValue top = GetTopStack(*stack);
    TStack removeStack = *stack;
    *stack = (*stack)->Next;
    free(removeStack);
    return top;
}

void PushStack(TValue value, TStack* stack)
{
    TStack new = malloc(sizeof(*new));
    assert(!IsEmptyStack(new));

    new->Value = value;
    new->Next = *stack;
    *stack = new;
}

void DestroyStack(TStack* stack) 
{
    while (!IsEmptyStack(*stack)) 
    {
        PopStack(stack);
    }
}

////////////////////////////////  BINARY TREE  ////////////////////////////////

struct Ttree
{
    TValue Value;
    struct Ttree* Left;
    struct Ttree* Right;
};

typedef struct Ttree* TTree;

bool IsEmptyTree(TTree tree)
{
    return tree == NULL;
}

TTree CreateTree(TValue value, TTree left, TTree right)
{
    TTree tree = malloc(sizeof(*tree));
    assert(!IsEmptyTree(tree));

    tree->Value = value;
    tree->Left = left;
    tree->Right = right;

    return tree;
}

void RemoveBranch(bool isLeft, TTree* tree)
{
    TTree delete = *tree;
    free((isLeft) ? (*tree)->Left : (*tree)->Right);
    *tree = (isLeft) ? (*tree)->Right : (*tree)->Left;
    free(delete);
}

void DestroyTree(TTree* tree)
{
    if(!IsEmptyTree(*tree))
    {
        DestroyTree(&(*tree)->Left);
        DestroyTree(&(*tree)->Right);
        free(*tree);
    }
}

////////////////////////////////  INPUT  ////////////////////////////////

bool IsDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

bool IsVariable(char symbol)
{
    return symbol >= 'a' && symbol <= 'z';
}

bool IsOperator(char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

bool IsStartBracket(char symbol)
{
    return symbol == '(';
}

bool IsEndBracket(char symbol)
{
    return symbol == ')';
}

void CheckBrackets(const char* line)
{
    TStack stack = CreateStack();
    int index = 0;

    while(line[index] != '\0')
    {
        if(IsStartBracket(line[index]))
        {
            if(!stack || index - PopStack(&stack).Number == 1)
            {
                DestroyStack(&stack);
                assert(false);
            }
        }
        else if(IsEndBracket(line[index]))
        {
            PushStack(CreateValue(line[index], '\0', index), &stack);
        }
        
        ++index;
    }

    if(!IsEmptyStack(stack))
    {
        DestroyStack(&stack);
        assert(false);
    }
}

void CheckSymbols(const char* line)
{
    while(*line)
    {
        assert(IsOperator(*line) || IsDigit(*line) || IsVariable(*line) || IsStartBracket(*line) || IsEndBracket(*line));
        ++line;
    }
}

void CheckSequence(const char* line)
{
    while(*line)
    {
        if(IsDigit(*line))
        {
            assert(!IsVariable(*(line + 1)));
        }
        else if(IsVariable(*line))
        {
            assert(!IsVariable(*(line + 1)) || !IsDigit(*(line + 1)));
        }
        else
        {
            assert(!IsOperator(*(line + 1)));
        }

        ++line;
    }
}

void CheckInfix(const char* infix)
{
    assert(*infix != '\0');

    CheckSymbols(infix);
    CheckSequence(infix);
    CheckBrackets(infix);
}

////////////////////////////////  INFIX -> PREFIX STACK -> BINARY TREE  ////////////////////////////////

int OperatorPriority(char value)
{
    switch(value)
    {
        case '(': return 0;
        case '-': return 1;
        case '+': return 1; 
        case '*': return 2;     
        case '/': return 2;
    }

    assert(false);
}

TStack InfixToPrefixStack(const char* infix) 
{
    TStack operatorStack = CreateStack();
    TStack prefixStack = CreateStack();

    while(*infix != '\0')
    {
        if(IsDigit(*infix))
        {
            int number = atoi(infix);
            PushStack(CreateValue('\0', '\0', number), &prefixStack);

            do
            {
                ++infix;
            } while (IsDigit(*infix));
        }
        else
        {
            if (IsVariable(*infix))
            {
                PushStack(CreateValue('\0', *infix, INT_MIN), &prefixStack);
            }
            else if(IsStartBracket(*infix))
            {
                PushStack(CreateValue(*infix, '\0', INT_MIN), &operatorStack);
            }
            else if(IsEndBracket(*infix))
            {
                while(GetTopStack(operatorStack).Operator != '(')
                {
                    PushStack(PopStack(&operatorStack), &prefixStack);
                }

                PopStack(&operatorStack);
            }
            else
            {
                while(!IsEmptyStack(operatorStack) && OperatorPriority(GetTopStack(operatorStack).Operator) >= OperatorPriority(*infix))
                {
                    PushStack(PopStack(&operatorStack), &prefixStack);
                }

                PushStack(CreateValue(*infix, '\0', INT_MIN), &operatorStack);
            }

            ++infix;
        }
    }

    while(!IsEmptyStack(operatorStack))
    {
        PushStack(PopStack(&operatorStack), &prefixStack);
    }

    DestroyStack(&operatorStack);

    return prefixStack;
}

TTree PrefixStackToTree(TStack* prefix)
{
    if(IsEmptyStack(*prefix))
    {
        return NULL;
    }

    if(IsOperator(GetTopStack(*prefix).Operator))
    {
        assert(!IsEmptyStack((*prefix)->Next) && !IsEmptyStack((*prefix)->Next->Next));

        TTree tree = CreateTree(PopStack(prefix), NULL, NULL);
        tree->Right = PrefixStackToTree(prefix);
        tree->Left = PrefixStackToTree(prefix);

        return tree;
    }
    else
    {
        return CreateTree(PopStack(prefix), NULL, NULL);
    }
}

////////////////////////////////  TRANSFORMATION BINARY TREE  ////////////////////////////////

void SimplifyExpression(TTree* tree)
{
    if(IsEmptyTree(*tree))
    {
        return;
    }
    if(IsOperator((*tree)->Value.Operator))
    {
        SimplifyExpression(&(*tree)->Left);
        SimplifyExpression(&(*tree)->Right);

        TValue left = (*tree)->Left->Value;
        TValue right = (*tree)->Right->Value;

        switch((*tree)->Value.Operator)
        {
            case '+':
                if(left.Number == 0 || right.Number == 0)
                {
                    RemoveBranch(left.Number == 0, tree);
                }
                break;
            case '-':
                if(right.Number == 0)
                {
                    RemoveBranch(false, tree);
                }
                break;
            case '*':
                if(left.Number == 1 || right.Number == 1)
                {
                    RemoveBranch(left.Number == 1, tree);
                }
                else if(left.Number == 0 || right.Number == 0)
                {
                    DestroyTree(tree);
                    *tree = CreateTree(CreateValue('\0', '\0', 0), NULL, NULL);
                }
                break;
            case '/':
                assert(right.Number != 0);

                if(right.Number == 1)
                {
                    RemoveBranch(false, tree);
                }
                else if(left.Number == 0)
                {
                    DestroyTree(tree);
                    *tree = CreateTree(CreateValue('\0', '\0', 0), NULL, NULL);
                }
        }
    }
    else
    {
        assert(IsEmptyTree((*tree)->Left) && IsEmptyTree((*tree)->Right));
    }
}

TTree CopyTree(TTree tree)
{
    if(!tree)
    {
        return NULL;
    }

    return CreateTree(tree->Value, CopyTree(tree->Left), CopyTree(tree->Right));
}

TTree BuildDerivative(TTree tree, char var)
{
    if(tree->Value.Operator == '+')
    {
        TTree derivative = CreateTree(CreateValue('+', '\0', INT_MIN), BuildDerivative(tree->Left, var), BuildDerivative(tree->Right, var));
        return  derivative;
    }
    if(tree->Value.Operator == '-')
    {
        TTree derivative = CreateTree(CreateValue('-', '\0', INT_MIN), BuildDerivative(tree->Left, var), BuildDerivative(tree->Right, var));
        return  derivative;
    }
    else if (tree->Value.Operator == '*')
    {
        TTree derivative1 = CreateTree(CreateValue('*', '\0', INT_MIN), BuildDerivative(tree->Left, var), CopyTree(tree->Right));
        TTree derivative2 = CreateTree(CreateValue('*', '\0', INT_MIN), CopyTree(tree->Left), BuildDerivative(tree->Right, var));
        TTree result = CreateTree(CreateValue('+', '\0', INT_MIN), derivative1, derivative2);
        return result;
    }
    else if (tree->Value.Operator == '/')
    {
        TTree derivative1 = CreateTree(CreateValue('*', '\0', INT_MIN), BuildDerivative(tree->Left, var), CopyTree(tree->Right));
        TTree derivative2 = CreateTree(CreateValue('*', '\0', INT_MIN), CopyTree(tree->Left), BuildDerivative(tree->Right, var));
        TTree denominator = CreateTree(CreateValue('*', '\0', INT_MIN), CopyTree(tree->Right), CopyTree(tree->Right));
        TTree numerator = CreateTree(CreateValue('-', '\0', INT_MIN), derivative1, derivative2);
        TTree result = CreateTree(CreateValue('/', '\0', INT_MIN), numerator, denominator);
        return result;
    }
    else if(tree->Value.Variable == var)
    {
        return CreateTree(CreateValue('\0', '\0', 1), NULL, NULL);
    }
    else
    {
        return CreateTree(CreateValue('\0', '\0', 0), NULL, NULL);
    }
}

int main()
{
    char infix[] = "x*x/y-4*x";

    CheckInfix(infix);

    TStack prefix = InfixToPrefixStack(infix);
    TTree tree = PrefixStackToTree(&prefix);
    SimplifyExpression(&tree);

    TTree result = BuildDerivative(tree, 'x');
    SimplifyExpression(&result);

    DestroyTree(&tree);
    DestroyTree(&result);

    return EXIT_SUCCESS;
}