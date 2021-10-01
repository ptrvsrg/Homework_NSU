#include <stdio.h>

enum
{
    SUCCESS = 0,
    SIZE = 60,
    SIZE2 = 3600
};

typedef struct TTime
{
    int Hour;
    int Minute;
    int Second;
} TTime;

void CreateTime(TTime* time)
{
    time->Hour = 0;
    time->Minute = 0;
    time->Second = 0;
}

void PrintTime(TTime time)
{
    printf("%.2d : %.2d : %.2d\n", time.Hour, time.Minute, time.Second);
}

int TimeToSecond(TTime time)
{
    return time.Hour * SIZE2 + time.Minute * SIZE + time.Second;
}

void SecondToTime(int second, TTime* time)
{
    time->Hour = second / SIZE2;
    second %= SIZE2;
    time->Minute = second / SIZE;
    second %= SIZE;
    time->Second = second;
}

void AdvanceTime(int addSecond, TTime* time)
{
    addSecond += TimeToSecond(*time);
    SecondToTime(addSecond, time);
}

int main(void)
{
    TTime time;
    CreateTime(&time);
    PrintTime(time);
    AdvanceTime(56464, &time);
    PrintTime(time);
    AdvanceTime(-10178, &time);
    PrintTime(time);
    return SUCCESS;
}