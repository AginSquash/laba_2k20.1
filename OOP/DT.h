//
// Created by Vlad Vrublevsky on 04.03.2020.
//

#ifndef LABA8_DT_H
#define LABA8_DT_H

#include <iostream>
#include <string> //fix for windows
#include "../collab/Date.h"

enum DT_timeType
{
    AT_YEAR = 1,
    AT_MON  = 2,
    AT_DAY  = 3,
    AT_HOUR = 4,
    AT_MIN  = 5,
    AT_SEC  = 6
};

struct _tuple_three
{
    int value0 = 0;
    int value1 = 0;
    int value2 = 0;
    
    _tuple_three (int value0, int value1, int value2) : value0(value0), value1(value1), value2(value2) {
     // Succefull constructor create
    }
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
        std::string addingValue = "";
        if (value < 0)
        {
            value *= (-1);
            addingValue = "-";
        }
        std::string _value = std::to_string(value);
        while (_value.length() < length)
        {
            _value = "0" + _value;
        }
        return  (addingValue + _value);
    }

    friend std::ostream& operator << (std::ostream &out, const DT_returnType &dtReturnType)
    {
        return out << parseDT(dtReturnType.year, 4) << "-" << parseDT(dtReturnType.month) << "-" << parseDT(dtReturnType.day) << dtReturnType.weekday
        << " " << parseDT(dtReturnType.hour) << ":" << parseDT(dtReturnType.min) + ":" + parseDT(dtReturnType.sec) << endl;
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

    // Legacy
    int dt_sec  = 0;
    int dt_min  = 0;
    int dt_hour = 0;
    int dt_day  = 0;
    int dt_mon  = 0;
    int dt_year = 0;
    // end

    long long dt_days = 0;
    int dt_seconds = 0;

    int abs(int value);
    bool checkRange(int value, int min, int max);
    int dayInMonth(int month, bool isLeapers);

    bool _is_leap(int year);
    long long days_before_year(int year);
    int days_in_month(int year, int month);
    int days_before_month(int year, int month);

public:
    long long ymd2ord(int year, short month, short day);
    _tuple_three ord2ymd(long long n);

    int hms2ord(int hour, int min, int sec);
    _tuple_three ord2hms(int n);

    DateTime(int year, int mon, int day, int hour, int min, int sec);
    DateTime(long long days, int seconds);
    DateTime();

    friend std::ostream& operator<<(std::ostream &out, DateTime &dt);
    DateTime& operator= (const DateTime &dt);
    int operator[] (const DT_timeType dtType);
    DateTime& operator+= (DateTime &dt);
    DateTime operator+ (DateTime dt);

    DT_returnType getDateTime();
    bool checkDate(int year, int mon, int day, bool isAddingDate = false);
    bool checkDateTime(int year, int mon, int day, int hour, int min, int sec);
    int addDateTime(int year, int mon, int day, int hour, int min, int sec);
    int addDateTime(int type, int count);
    int subtractDateTime(int year, int mon, int day, int hour, int min, int sec);
};

#endif