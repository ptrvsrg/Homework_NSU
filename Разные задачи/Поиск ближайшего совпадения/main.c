#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;
typedef struct Tlist* TList;
typedef struct Ttree* TTree;

int Min(TValue a, TValue b)
{
    return (a <= b) ? a : b;
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

//////////////////// LIST TYPE ////////////////////

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

TTree GetTopList(TList list)
{
    assert(!IsEmptyList(list));
    return list->Tree;
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

//////////////////// SEARCH SHORTEST PATH TO THE VALUE ////////////////////

int SearchValueTree(TValue searchedValue, TTree tree); //DFS
int SearchValueList(TValue searchedValue, TList list);

int SearchValueTree(TValue searchedValue, TTree tree)
{
    if(IsEmptyTree(tree))
    {
        return INT_MAX;
    }

    if(searchedValue == tree->Value)
    {
        return 0;
    }

    int depth = SearchValueList(searchedValue, tree->Children);
    return (depth == INT_MAX) ? depth : depth + 1;
}

int SearchValueList(TValue searchedValue, TList list)
{
    if(IsEmptyList(list))
    {
        return INT_MAX;
    }

    return Min(SearchValueTree(searchedValue, list->Tree), SearchValueList(searchedValue, list->Next));
}

/*int SearchValueTree(TValue searchedValue, TTree tree) //BFS
{
    TQueue queue = CreateQueue();
    PushQueue(tree, &queue);
    int subtreeCount = 1;
    int depth = 0;

    while (!IsEmptyQueue(queue))
    {
        TTree tree = PopQueue(&queue);
        --subtreeCount;

        if(IsEmptyTree(tree))
        {
            continue;
        }

        if (tree->Value == searchedValue)
        {
            return depth;
        }
        
        PushListQueue(tree->Children, &queue);

        if(subtreeCount == 0)
        {
            ++depth;
            subtreeCount = SizeQueue(queue);
        }
    }

    return INT_MAX;
}*/

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

    printf("Shortest depth to %d id %d\n", 5, SearchValueTree(5, tree));
    printf("Shortest depth to %d id %d\n", 11, SearchValueTree(11, tree));

    DestroyTree(&tree);

    return EXIT_SUCCESS;
}