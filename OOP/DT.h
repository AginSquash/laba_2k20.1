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
    int year  = 0;
    int month = 0;
    int day   = 0;

    int hour  = 0;
    int min   = 0;
    int sec   = 0;

    std::string weekday = "";

    DT_returnType(int year, int month, int day) {
        this->year = year;
        this->month = month;
        this->day = day;
    }

    DT_returnType(int hour, int min, int sec, bool isSeconds) {
        this->hour = hour;
        this->min = min;
        this->sec = sec;
    }

    DT_returnType(int year, int month, int day, int hour, int min, int sec) {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->min = min;
        this->sec = sec;
    }

    void setWeekday()
    {
        Date date(day, month, year);
        this->weekday =  " (" + date.getDayResult() +  ") ";
    }

    static std::string parseDT(int value, int length = 2) {
        std::string _value = std::to_string(value);
        while (_value.length() < length)
        {
            _value = "0" + _value;
        }
        return  _value;
    }

    friend std::ostream& operator << (std::ostream &out, const DT_returnType &dtReturnType)
    {
        return out << parseDT(dtReturnType.year, 4) << "-" << parseDT(dtReturnType.month) << "-" << parseDT(dtReturnType.day) << dtReturnType.weekday
        << " " << parseDT(dtReturnType.hour) << ":" << parseDT(dtReturnType.min) + ":" + parseDT(dtReturnType.sec) << endl;
    }

    friend DT_returnType operator + (DT_returnType drt1, DT_returnType drt2)
    {
        return DT_returnType(
                drt1.year + drt2.year, drt1.month + drt2.month,
                drt1.day + drt2.day,drt1.hour + drt2.hour,
                drt1.min + drt2.min, drt1.sec + drt2.sec);
    }
};

class DateTime
{
/*
 * Precomputed values for performance
 */

#define _DI400Y     146097 //number of days in 400 years
#define _DI100Y     36524  //                  100
#define _DI4Y       1461   //                    4

#define _SI24H      86400  //seconds in H/M
#define _SI1H       3600
#define _SI1M       60

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
    int dt_seconds;

    bool resultOfCompute = false;
    bool checkRange(int value, int min, int max);
    std::string parseInt(int value, int length = 2);
    int dayInMonth(int month, bool isLeapers);

    bool _is_leap(int year);
    long long _days_before_year(int year);
    int _days_in_month(int year, int month);
    int _days_before_month(int year, int month);

public:

    long long ymd2ord(int year, short month, short day);
    DT_returnType ord2ymd(long long n);

    int hms2ord(int hour, int min, int sec);
    DT_returnType ord2hms(int n);

    DateTime(int year, int mon, int day, int hour, int min, int sec, bool isResultOfCompute = false);
    DateTime();
    DT_returnType getDateTime();
    bool checkDate(int year, int mon, int day, bool isAddingDate = false);
    bool checkDateTime(int year, int mon, int day, int hour, int min, int sec);
    int addDateTime(int year, int mon, int day, int hour, int min, int sec);
    int addDateTime(int type, int count);
    DateTime subtractDateTime(int year, int mon, int day, int hour, int min, int sec);
};

#endif LABA8_DT_H
