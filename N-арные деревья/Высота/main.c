#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;
typedef struct Tlist* TList;
typedef struct Ttree* TTree;

TValue Max(TValue value1, TValue value2)
{
    return value1 >= value2 ? value1 : value2;
}

//////////////////// TREE TYPE ////////////////////

struct Ttree
{
    TValue Value;
    TList Children;
};

bool IsEmptyTree(TTree tree)
{
    return tree == NULL;
}

TTree CreateTree(TValue value, TList list)
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
    TTree Child;
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

    list->Child = tree;
    list->Next = NULL;

    return list;
}

void PushList(TTree tree, TList* list)
{
    TList new = CreateItem(tree);
    new->Next = *list;
    (*list) = new;
}

TTree GetTopList(TList list)
{
    assert(!IsEmptyList(list));
    return list->Child;
}

TTree PopList(TList* list)
{
    TTree value = GetTopList(*list);

    TList removeElem = *list;
    *list = (*list)->Next;

    free(removeElem);

    return value;
}

int SizeList(TList list)
{
    if(IsEmptyList(list))
    {
        return 0;
    }

    return 1 + SizeList(list->Next);
}

TList ConvertArrayToLeafList(int arraySize, TValue array[])
{
    if(arraySize <= 0)
    {
        return NULL;
    }

    TList list = CreateItem(CreateTree(*array, NULL));
    list->Next = ConvertArrayToLeafList(arraySize - 1, array + 1);

    return list;
}

TList ConvertArrayToTreeList(int arraySize, TTree array[])
{
    if(arraySize <= 0)
    {
        return NULL;
    }

    TList list = CreateItem(*array);
    list->Next = ConvertArrayToTreeList(arraySize - 1, array + 1);

    return list;
}

//////////////////// QUEUE TYPE ////////////////////

typedef struct TQueue
{
    TList Begin;
    TList End;
} TQueue;

TQueue CreateQueue()
{
    TQueue queue;
    queue.Begin = NULL;
    queue.End = NULL;

    return queue;
}

bool IsEmptyQueue(TQueue queue)
{
    return IsEmptyList(queue.Begin) && IsEmptyList(queue.End);
}

void PushQueue(TTree value, TQueue* queue)
{
    PushList(value, &queue->Begin);
}

void PushListQueue(TList list, TQueue* queue)
{
    if(!IsEmptyList(list))
    {        
        PushList(GetTopList(list), &queue->Begin);
        PushListQueue(list->Next, queue);
    }
}

void MoveBeginToEnd(TQueue* queue)
{
    while(!IsEmptyList(queue->Begin))
    {
        PushList(PopList(&queue->Begin), &queue->End);
    }
}

TTree PopQueue(TQueue* queue)
{
    if(IsEmptyList(queue->End))
    {
        MoveBeginToEnd(queue);
    }

    return PopList(&queue->End);
}

int SizeQueue(TQueue queue)
{
    return SizeList(queue.Begin) + SizeList(queue.End);
}

//////////////////// DEPTH ////////////////////

int DepthList(TList list);
int DepthTree(TTree tree);

int DepthList(TList list)
{
    if(IsEmptyList(list))
    {
        return 0;
    }

    return Max(DepthTree(list->Child), DepthList(list->Next));
}

int DepthTree(TTree tree)
{
    if(IsEmptyTree(tree))
    {
        return 0;
    }

    return 1 + DepthList(tree->Children);
}

//////////////////// MAX VALUE ////////////////////

TValue MaxList(TList list);
TValue MaxTree(TTree tree);

TValue MaxList(TList list)
{
    if(IsEmptyList(list))
    {
        return INT_MIN;
    }

    return Max(MaxTree(list->Child), MaxList(list->Next));
}

TValue MaxTree(TTree tree)
{
    if(IsEmptyTree(tree))
    {
        return INT_MIN;
    }

    return Max(tree->Value, MaxList(tree->Children));
}

//////////////////// DESTROY ////////////////////

void DestroyList(TList* list);
void DestroyTree(TTree* tree);

void DestroyList(TList* list) 
{
    if(!IsEmptyList(*list))
    {
        DestroyList(&(*list)->Next);
        DestroyTree(&(*list)->Child);
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

//////////////////// PRINT ////////////////////

void PrintTree(TTree tree)
{
    TQueue queue = CreateQueue();
    PushQueue(tree, &queue);
    int subtreeCount = 1;

    while (!IsEmptyQueue(queue))
    {
        TTree tree = PopQueue(&queue);
        --subtreeCount;

        if(IsEmptyTree(tree))
        {
            continue;
        }

        PushListQueue(tree->Children, &queue);
        printf("%d ", tree->Value);

        if(subtreeCount == 0)
        {
            printf("\n");
            subtreeCount = SizeQueue(queue);
        }
    }
}

//////////////////// MAIN ////////////////////

int main(void)
{
    TValue array1[] = { 4, 5, 6 };
    TValue array2[] = { 7, 8 };
    
    TList list1 = ConvertArrayToLeafList(sizeof(array1) / sizeof(*array1), array1);
    TList list2 = ConvertArrayToLeafList(sizeof(array2) / sizeof(*array2), array2);

    TTree treeArray[] = {
        CreateTree(2, list1),
        CreateTree(3, list2)
    };

    TList list3 = ConvertArrayToTreeList(sizeof(treeArray) / sizeof(*treeArray), treeArray);

    TTree tree = CreateTree(1, list3);

    printf("Depth is %d\n", DepthTree(tree));
    printf("Max value is %d\n", MaxTree(tree));
    PrintTree(tree);

    DestroyTree(&tree);

    return EXIT_SUCCESS;
}