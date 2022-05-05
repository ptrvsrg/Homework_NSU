#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int ReleaseCount;
    int JoinCount;
} TBarrier;

void WaitBarrier(TBarrier* barrier)
{
   int threadId = omp_get_thread_num();
   int threadCount = omp_get_num_threads();

   if (threadId == 0)
   {
#pragma omp atomic
        ++barrier->JoinCount;
        while (barrier->JoinCount != threadCount)
        {}
        ++barrier->ReleaseCount;
#pragma omp atomic
        barrier->JoinCount *= 0;
   }
   else
   {
       int releaseCount = barrier->ReleaseCount;
#pragma omp atomic
       ++barrier->JoinCount;
       while (barrier->ReleaseCount == releaseCount)
       {}
   }
   
}

int main(void)
{
    int i;
    TBarrier barrier = {0, 0};
    int threadCount = 4;
#pragma omp parallel for num_threads(threadCount)
    for (i = 0; i < threadCount * 1000; ++i)
    {
        printf("thread %d\n", omp_get_thread_num());
        WaitBarrier(&barrier);
        printf("thread %d\n", omp_get_thread_num());
        WaitBarrier(&barrier);
    }
    return EXIT_SUCCESS;
}