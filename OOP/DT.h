//
// Created by Vlad Vrublevsky on 04.03.2020.
//

#ifndef LABA8_DT_H
#define LABA8_DT_H

#include <iostream>
#include <string> //fix for windows
#include "../collab/Date.h"

enum DT_addingType
{
    AT_YEAR = 1,
    AT_MON  = 2,
    AT_DAY  = 3,
    AT_HOUR = 4,
    AT_MIN  = 5,
    AT_SEC  = 6
};

struct DT_returnType
{
    int year;
    int month;
    int day;

    DT_returnType(int year, int month, int day) {
        this->year = year;
        this->month = month;
        this->day = day;
    }

    friend std::ostream& operator << (std::ostream &out, const DT_returnType &dtReturnType)
    {
        return out << dtReturnType.year << "-" << dtReturnType.month << "-" << dtReturnType.day << endl;
    }
};

class DateTime
{
/*
 * Precomputed values for performance
 */
#define _DI400Y 146097 //number of days in 400 years
#define _DI100Y 36524  //                  100
#define _DI4Y 1461     //                    4

#define _SI1H 3600
#define _SI1M  60

private:
    short _DAYS_IN_MONTH[13] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    short _DAYS_BEFORE_MONTH[13] = { -1, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

    int dt_sec  = 0;
    int dt_min  = 0;
    int dt_hour = 0;
    int dt_day  = 0;
    int dt_mon  = 0;
    int dt_year = 0;

    long long dt_days;
    long long dt_seconds;

    bool axiom = false;
    bool checkRange(int value, int min, int max);
    std::string parseInt(int value, int length = 2);
    int dayInMonth(int month, bool isLeapers);

    bool _is_leap(int year);
    long long _days_before_year(int year);
    int _days_in_month(int year, int month);
    int _days_before_month(int year, int month);

public:
    unsigned long long parseDateTime(int year, int mon, int day, int hour, int min, int sec);
    std::string getTime();

    long long ymd2ord(int year, short month, short day);
    DT_returnType ord2ymd(long long n);
    int hms2ord(int hour, int min, int sec);
    void ord2hms(int n);

    DateTime(int year, int mon, int day, int hour, int min, int sec, bool isAxiom = false);
    DateTime();
    std::string getDateTime();
    bool checkDate(int year, int mon, int day, bool isAddingDate = false);
    bool checkDateTime(int year, int mon, int day, int hour, int min, int sec);
    int addDateTime(int year, int mon, int day, int hour, int min, int sec);
    int addDateTime(int type, int count);
    DateTime subtractDateTime(int year, int mon, int day, int hour, int min, int sec);
};

#endif LABA8_DT_H
