#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TList* TList;
typedef struct TTree* TTree;

//////////////////// TREE TYPE ////////////////////

struct TTree
{
    int Value;
    TList Children;
};

bool IsEmptyTree(TTree tree)
{
    return tree == NULL;
}

TTree CreateTree(int value, TList list)
{
    TTree tree = malloc(sizeof(*tree));
    assert(!IsEmptyTree(tree));

    tree->Value = value;
    tree->Children = list;

    return tree;
}

//////////////////// LIST TYPE ////////////////////

struct TList
{
    TTree Tree;
    TList Next;
};

bool IsEmptyList(TList list)
{
    return list == NULL;
}

TList CreateItem(TTree tree)
{
    TList list = malloc(sizeof(*list));
    assert(!IsEmptyList(list));

    list->Tree= tree;
    list->Next = NULL;

    return list;
}

TList ConvertTreeArrayToList(int arraySize, TTree* array)
{
    if(arraySize <= 0)
    {
        return NULL;
    }

    TList list = CreateItem(*array);
    list->Next = ConvertTreeArrayToList(arraySize - 1, array + 1);

    return list;
}

void ConvertTreeToArray(TTree tree, int* array)
{
    if(IsEmptyTree(tree))
    {
        return;
    }

    TList children = tree->Children;
    while(!IsEmptyList(children))
    {
        ConvertTreeToArray(children->Tree, array);
        children = children->Next;
    }
    
    static int index = 0;
    array[index] = tree->Value;
    ++index;
}

int SizeTree(TTree tree)
{
    if(IsEmptyTree(tree))
    {
        return 0;
    }

    int sum = 1;
    TList list = tree->Children;
    while(!IsEmptyList(list))
    {
        sum += SizeTree(list->Tree);
        list = list->Next;
    }

    return sum;
}

void PrintArray(int arraySize, int* array)
{
    for(int i = 0; i < arraySize; ++i)
    {
        printf("%d ", array[i]);
    }
}

//////////////////// DESTROY ////////////////////

void DestroyList(TList* list);
void DestroyTree(TTree* tree);

void DestroyList(TList* list) 
{
    if(!IsEmptyList(*list))
    {
        DestroyList(&(*list)->Next);
        DestroyTree(&(*list)->Tree);
        free(*list);
    }
}

void DestroyTree(TTree* tree) 
{
    if(!IsEmptyTree(*tree))
    {
        DestroyList(&(*tree)->Children);
        free(*tree);
    }
}

//////////////////// MAIN ////////////////////

int main(void)
{
    TTree array1[] = {
        CreateTree(1, NULL), 
        CreateTree(2, NULL), 
        CreateTree(3, NULL)
    };
    
    TList list1 = ConvertTreeArrayToList(3, array1);

    TTree array2[] = {
        CreateTree(4, NULL), 
        CreateTree(5, NULL)
    };
    
    TList list2 = ConvertTreeArrayToList(2, array2);

    TTree array3[] = {
        CreateTree(6, list1),
        CreateTree(7, list2)
    };

    TList list3 = ConvertTreeArrayToList(2, array3);

    TTree tree = CreateTree(8, list3);

    int arraySize = SizeTree(tree);
    int* array = calloc(arraySize, sizeof(*array));
    assert(array != NULL);

    ConvertTreeToArray(tree, array);
    PrintArray(arraySize, array);

    DestroyTree(&tree);
    free(array);

    return EXIT_SUCCESS;
}