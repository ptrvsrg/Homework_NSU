#include <stdio.h>

enum
{
    SUCCESS = 0,
    SIZE_MINUTE_IN_SECOND = 60,
    SIZE_HOUR_IN_SECOND = 3600
};

typedef enum TTense
{
    PAST,
    PRESENT
} TTense;

typedef struct TTime
{
    TTense Tense;
    int Hour;
    int Minute;
    int Second;
} TTime;

void CreateTime(TTime* time)
{
    time->Tense = PRESENT;
    time->Hour = 0;
    time->Minute = 0;
    time->Second = 0;
}

void PrintTime(TTime time)
{
    if(time.Tense == PAST)
    {
        printf("past: ");
    }
    else
    {
        printf("present: ");
    }
    printf("%.2d : %.2d : %.2d\n", time.Hour, time.Minute, time.Second);
}

int TimeToSecond(TTime time)
{
    int sum = time.Hour * SIZE_HOUR_IN_SECOND + time.Minute * SIZE_MINUTE_IN_SECOND + time.Second;
    return sum * ((time.Tense == PRESENT) ? 1 : -1);
}

int Fabs(int x)
{
    return (x >= 0) ? x : -x;
}

void SecondToTime(int second, TTime* time)
{
    if(Fabs(second) != second)
    {
        second *= -1;
        time->Tense = PAST;
    }

    time->Hour = second / SIZE_HOUR_IN_SECOND;
    second %= SIZE_HOUR_IN_SECOND;
    time->Minute = second / SIZE_MINUTE_IN_SECOND;
    second %= SIZE_MINUTE_IN_SECOND;
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
    AdvanceTime(30, &time);
    PrintTime(time);
    AdvanceTime(-60, &time);
    PrintTime(time);
    return SUCCESS;
}
