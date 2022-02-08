#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Tlist* TList;
typedef struct Ttree* TTree;

//////////////////// TREE TYPE ////////////////////

struct Ttree
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

//////////////////// TREE LIST TYPE ////////////////////

struct Tlist
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

void PushList(TTree tree, TList* list)
{
    TList new = CreateItem(tree);
    new->Next = *list;
    (*list) = new;
}

TList ConvertArrayToList(int arraySize, TTree* array)
{
    if(arraySize <= 0)
    {
        return NULL;
    }

    TList list = CreateItem(*array);
    list->Next = ConvertArrayToList(arraySize - 1, array + 1);

    return list;
}

void ConvertTreeToList(TTree tree, TList* list)
{
    if(IsEmptyTree(tree))
    {
        return;
    }

    PushList(CreateTree(tree->Value, NULL), list);
    TList children = tree->Children;
    while(!IsEmptyList(children))
    {
        ConvertTreeToList(children->Tree, list);
        children = children->Next;
    }
}

void PrintList(TList list)
{
    if(IsEmptyList(list))
    {
        return;
    }

    printf("%d ", list->Tree->Value);
    PrintList(list->Next);
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
    
    TList list1 = ConvertArrayToList(3, array1);

    TTree array2[] = {
        CreateTree(4, NULL), 
        CreateTree(5, NULL)
    };
    
    TList list2 = ConvertArrayToList(2, array2);

    TTree array3[] = {
        CreateTree(6, list1),
        CreateTree(7, list2)      
    };

    TList list3 = ConvertArrayToList(2, array3);

    TTree tree = CreateTree(8, list3);

    TList list = NULL;
    ConvertTreeToList(tree, &list);
    PrintList(list);

    DestroyTree(&tree);
    DestroyList(&list);

    return EXIT_SUCCESS;
}