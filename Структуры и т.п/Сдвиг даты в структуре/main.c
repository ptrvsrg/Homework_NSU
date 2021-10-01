#include <stdio.h>
#define YEAR_SIZE_IN_DAYS  365.25

enum
{
    January = 31,
    February = 28,
    March = 31,
    April = 30,
    May = 31,
    June = 30,
    July = 31,
    August = 31,
    September = 30,
    October = 31,
    November = 30,
    December = 31,

    FAILURE = -1,
    SUCCESS = 0,
    YEAR_SIZE_IN_MONTH = 12
};

const int monthCount[] = {
    0,
    January,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December,
};

typedef struct TDate
{
    int Day;
    int Month;
    int Year;
} TDate;

void PrintDate(TDate date)
{
    printf("%.2d.%.2d.%.4d\n", date.Day, date.Month, date.Year);
}

int DateToDay(TDate date)
{
    int day = date.Year * YEAR_SIZE_IN_DAYS + date.Day;

    for(int i = 0; i < date.Month; i++)
    {
        if(date.Year % 4 == 0 && i == 2)
        {
            ++day;
        }

        day += monthCount[i];
    }

    return day;
}

void DayToDate(int day, TDate *date)
{
    date->Year = day / YEAR_SIZE_IN_DAYS;
    day -= date->Year * YEAR_SIZE_IN_DAYS;

    for(int i = 0; i <= YEAR_SIZE_IN_MONTH; i++)
    {
        int monthDays = monthCount[i];

        if(date->Year % 4 == 0 && i == 2)
        {
            ++monthDays;
        }

        if(monthDays >= day)
        {
            date->Month = i;
            date->Day = day;
            break;
        }

        day -= monthDays;
    }
}

void AdvanceDate(int addYear, TDate *date)
{
    addYear += DateToDay(*date);
    DayToDate(addYear, date);
}

int main(void)
{
    TDate date = {1, 1, 0};
    
    PrintDate(date);
    AdvanceDate(2, &date);
    PrintDate(date);
    return SUCCESS;
}