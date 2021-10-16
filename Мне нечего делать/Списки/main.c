#include "list.h"

int main()
{
    TList list1 = CreateList();
    TList list2 = CreateList();
    ScanList(3, &list1);
    ScanList(3, &list2);
    PrintList(list1);
    printf("\t");
    PrintList(list2);
    printf("\n");
    SwapLists(&list1, &list2);
    PrintList(list1);
    printf("\t");
    PrintList(list2);
    printf("\n");
    FreeList(&list1);
    FreeList(&list2);

    return 0;
}