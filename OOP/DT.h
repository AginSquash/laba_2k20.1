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

typedef std::tuple<int, int, int, int, int, int> TimeTuple;

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

    long long dt_days = 0;
    int dt_seconds = 0;

    int abs(int value);
    bool checkRange(int value, int min, int max);
    int dayInMonth(int month, bool isLeapers);

    bool _is_leap(int year);
    long long days_before_year(int year);
    int days_in_month(int year, int month);
    int days_before_month(int year, int month);
    std::string parseDT(int value, int length = 2);

public:
    long long ymd2ord(int year, short month, short day);
    std::tuple<int, int, int> ord2ymd(long long n);

    int hms2ord(int hour, int min, int sec);
    std::tuple<int, int, int> ord2hms(int n);

    DateTime(int year, int mon, int day, int hour, int min, int sec);
    DateTime(long long days, int seconds);
    DateTime();

    friend std::ostream& operator<<(std::ostream &out, DateTime &dt);
    DateTime& operator= (const DateTime &dt);
    int operator[] (const DT_timeType dtType);
    DateTime& operator+= (DateTime &dt);
    DateTime operator+ (DateTime dt);
    DateTime& operator-= (DateTime &dt);
    DateTime operator- (DateTime dt);

    friend bool operator== (const DateTime &dt1, const DateTime &dt2);
    friend bool operator!= (const DateTime &dt1, const DateTime &dt2);
    friend bool operator> (const DateTime &dt1, const DateTime &dt2);
    friend bool operator>= (const DateTime &dt1, const DateTime &dt2);
    friend bool operator< (const DateTime &dt1, const DateTime &dt2);
    friend bool operator<= (const DateTime &dt1, const DateTime &dt2);

    operator int();

    TimeTuple getDateTime();
    std::string dateTimeToString();
    bool checkDate(int year, int mon, int day, bool isAddingDate = false);
    bool checkDateTime(int year, int mon, int day, int hour, int min, int sec);
    int addDateTime(int year, int mon, int day, int hour, int min, int sec);
    int addDateTime(int type, int count);
    int subtractDateTime(int year, int mon, int day, int hour, int min, int sec);
};

#endif