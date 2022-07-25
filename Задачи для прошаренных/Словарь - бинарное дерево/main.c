#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

/* Errors */

#define EMEM 1
#define EREAD 2
#define EOPF 3

void PrintError(int errorNum)
{
    switch (errorNum)
    {
    case EMEM:
        fprintf(stderr, "Memory allocation error");
        break;
    case EREAD:
        fprintf(stderr, "Read error");
        break;
    case EOPF:
        fprintf(stderr, "File open error");
        break;
    default:
        break;
    }
}

/* Translation type */

typedef struct TTranslation
{
    char Word[MAX_WORD_LENGTH];
    char Translation[MAX_WORD_LENGTH];
} TTranslation;

TTranslation CreateTranslation(const char* word, const char* translation)
{
    TTranslation value;
    strncpy(value.Word, word, MAX_WORD_LENGTH);
    strncpy(value.Translation, translation, MAX_WORD_LENGTH);
    return value;
}

int CompareTranslation(TTranslation value1, TTranslation value2)
{
    return strcmp(value1.Word, value2.Word);
}

int ScanTranslation(FILE* inFile, TTranslation* value)
{
    char string[MAX_WORD_LENGTH] = { 0 };
    if (fgets(string, MAX_WORD_LENGTH, inFile) == NULL)
    {
        if (feof(inFile)) 
        {
            return EOF;
        }

        PrintError(EREAD);
        exit(EXIT_FAILURE);
    }

    char* newline = strchr(string, '\n');
    if (newline != NULL)
    {
        *newline = '\0';
    }

    char* separator = strchr(string, ':');
    *separator = '\0';

    char* word = string;
    char* translation = separator + 1;

    *value = CreateTranslation(word, translation);

    return 1;
}

void PrintTranslation(TTranslation value)
{
    printf("%s - %s", value.Word, value.Translation);
}

/* Tree type */

typedef struct Ttree
{
    TTranslation Value;
    struct Ttree* Left;
    struct Ttree* Right;
} *TTree, *TSubTree;

TTree CreateTree(void)
{
    return NULL;
}

bool IsEmptyTree(TTree tree)
{
    return tree == NULL;
}

void PushTree(TTranslation value, TTree* tree)
{
    if (IsEmptyTree(*tree))
    {
        *tree = malloc(sizeof(struct Ttree));
        if (*tree == NULL)
        {
            PrintError(EMEM);
            exit(EXIT_FAILURE);
        }

        (*tree)->Value = value;
        (*tree)->Left = NULL;
        (*tree)->Right = NULL;

        return;
    }

    int cmpResult = CompareTranslation((*tree)->Value, value);
    if (cmpResult > 0)
    {
        PushTree(value, &(*tree)->Left);
    }
    else if (cmpResult < 0)
    {
        PushTree(value, &(*tree)->Right);
    }
    else
    {
        PrintError(EMEM);
        exit(EXIT_FAILURE);
    }
}

TSubTree FindTree(char* word, TTree tree)
{
    if (IsEmptyTree(tree))
    {
        return NULL;
    }

    int cmpResult = strcmp(tree->Value.Word, word);
    if (cmpResult > 0)
    {
        return FindTree(word, tree->Left);
    }
    else if (cmpResult < 0)
    {
        return FindTree(word, tree->Right);
    }
    else
    {
        return tree;
    }
}

TTree ScanTree(FILE* inFile)
{
    TTree tree = CreateTree();

    TTranslation value;
    while (ScanTranslation(inFile, &value) != EOF)
    {
        PushTree(value, &tree);
    }

    return tree;
}

void PrintTree(TTree tree)
{
    if (IsEmptyTree(tree))
    {
        return;
    }

    PrintTree(tree->Left);
    PrintTranslation(tree->Value);
    printf("\n");
    PrintTree(tree->Right);
}

void DestroyTree(TTree* tree)
{
    if (!IsEmptyTree(*tree))
    {
        DestroyTree(&(*tree)->Left);
        DestroyTree(&(*tree)->Right);
        free(*tree);
        *tree = NULL;
    }
}

/* main function */

int main(void)
{
    setlocale(LC_ALL, "rus");
    FILE* inFile = fopen("in.txt", "r");
    if (inFile == NULL)
    {
        PrintError(EOPF);
        exit(EXIT_FAILURE);
    }

    TTree tree = ScanTree(inFile);

    PrintTree(tree);

    printf("\n"); 

    TSubTree subTree = FindTree("make", tree);
    PrintTranslation(subTree->Value);

    DestroyTree(&tree);

    return EXIT_SUCCESS;
}