//
// Created by Vlad Vrublevsky on 04.03.2020.
//

#include "DT.h"

#define DEBUG

void debug_print(std::string debug_text)
{
#ifdef DEBUG
    std::cout << debug_text << std::endl;
#endif
}

std::string DateTime::parseInt(int value, int length) {
    std::string _value = std::to_string(value);
    if (axiom)
    {
        return _value;
    }
    while (_value.length() < length)
    {
        _value = "0" + _value;
    }
    return  _value;
}

int DateTime::addDateTime(int type, int count) {
    int year = 0;
    int mon = 0;
    int day = 0;
    int hour = 0;
    int min = 0;
    int sec = 0;

    switch (type) {
        case AT_YEAR:
            year = count;
            break;
        case AT_MON:
            mon = count;
            break;
        case AT_DAY:
            day = count;
            break;
        case AT_HOUR:
            hour = count;
            break;
        case AT_MIN:
            min = count;
            break;
        case AT_SEC:
            sec = count;
            break;
    }

    return addDateTime(year, mon, day, hour, min, sec);
}

int DateTime::addDateTime(int year, int mon, int day, int hour, int min, int sec) {
    if (checkDate(year, mon, day, true)  ) {
        int _sec = dt_sec + sec;
        while (_sec > 59) {
            min++;
            _sec -= 60;
        }
        dt_sec = _sec;
        debug_print("sec ok");

        int _min = dt_min + min;
        while (_min > 59) {
            hour++;
            _min -= 60;
        }
        dt_min = _min;
        debug_print("min ok");

        int _hour = dt_hour + hour;
        while (_hour > 23) {
            day++;
            _hour -= 24;
        }
        dt_hour = _hour;
        debug_print("hour ok");

        int _mon = dt_mon + mon;
        while (_mon > 12) {
            year++;
            _mon -= 12;
        }
        dt_mon = _mon;
        debug_print ("mon ok");

        dt_year += year;

        int _day = dt_day + day;
        int dayInMonth;
        do {
            switch (dt_mon) {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    dayInMonth = 31;
                    break;
                case 2:
                    if (dt_year % 4 == 0 && (dt_year % 100 != 0 || dt_year % 400 == 0))
                        dayInMonth = 29;
                    else
                        dayInMonth = 28;
                    break;
                    // апрель, июнь, сентябрь и ноябрь
                case 4:
                case 6:
                case 9:
                case 11:
                    dayInMonth = 30;
                    break;
            }
            if (_day > dayInMonth)
            {
                _day -= dayInMonth;
                dt_mon++;
            }
            debug_print("repeating");
        } while (_day > dayInMonth);
        debug_print("day ok");

        dt_day = _day;
        while (dt_mon > 12) {
            dt_year++;
            dt_mon -= 12;
        }
        debug_print("mon ok");
    }
    return 0;
}

bool DateTime::checkDate(int year, int mon, int day, bool isAddingDate) {
    switch (mon)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return checkRange(day, 1, 31);
        case 2:
            if ( year % 4 == 0 && (year % 100 != 0 || year % 400 ==0) )
                return checkRange(day, 1, 29);
            else
                return checkRange(day, 1, 28);
            // апрель, июнь, сентябрь и ноябрь
        case 4:
        case 6:
        case 9:
        case 11:
            return checkRange(day, 1, 30);

        default:
            if (isAddingDate && mon == 0)
                return true;
            return false;
    }
}

bool DateTime::checkRange(int value, int min, int max) {
    if (value < min)
        return false;
    if (value > max)
        return false;
    return true;
}

std::string DateTime::getDateTime()
{
    Date date(dt_day, dt_mon, dt_year);
    std::string weekDay = "";
    if (!axiom)
    {
        weekDay = " (" + date.getDayResult() +  ") ";
    }
    std::string dt_string = parseInt(dt_year, 4) + "-" + parseInt(dt_mon) + "-" + parseInt(dt_day) + weekDay + " " + parseInt(dt_hour) + ":" +
                            parseInt(dt_min) + ":" + parseInt(dt_sec);
    return dt_string;
}

DateTime DateTime::subtractDateTime(int year, int mon, int day, int hour, int min, int sec)
{
    int t_year = dt_year; int t_mon = dt_mon; int t_day = dt_day;
    int t_hour = dt_hour; int t_min = dt_min; int t_sec = dt_sec;

    t_sec -= sec;
    while (t_sec < 0)
    {
        min++;
        t_sec = 60 + t_sec;
    }

    t_min -= min;
    while (t_min < 0)
    {
        hour++;
        t_min = 60 + t_min;
    }

    t_hour -= hour;
    while (t_hour < 0)
    {
        day++;
        t_hour = 24 + t_hour;
    }

    t_mon -= mon;
    while(t_mon < 1)
    {
        year++;
        t_mon = 12 + t_mon;
    }

    t_year -= year;

    t_day -= day;
    int dayInMonth;
    while (t_day < 0) {
        t_mon--;
        switch (t_mon) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                dayInMonth = 31;
                break;
            case 2:
                if (t_year % 4 == 0 && (t_year % 100 != 0 || t_year % 400 == 0))
                    dayInMonth = 29;
                else
                    dayInMonth = 28;
                break;
                // апрель, июнь, сентябрь и ноябрь
            case 4:
            case 6:
            case 9:
            case 11:
                dayInMonth = 30;
                break;
        }
            t_day = dayInMonth - t_day;
        debug_print("repeating");
    }
    debug_print("day ok");

    while (t_mon < 1) {
        t_year--;
        t_mon = 12 + t_mon;
    }
    debug_print("mon ok");

    DateTime dt_new(t_year, t_mon, t_day, t_hour, t_min, t_sec, true);
    return dt_new;
}

DateTime::DateTime() {}

DateTime::DateTime(int year, int mon, int day, int hour, int min, int sec, bool isAxiom)
{
    axiom = isAxiom;
    if (checkDate(year, mon, day) || isAxiom)
    {
        dt_year = year;
        dt_mon = mon;
        dt_day = day;
        if (!isAxiom)
            std::cout << "Date - OK" << std::endl;
        if ((checkRange(hour, 0, 23)) && checkRange(min, 0, 59) &&  (checkRange(sec, 0, 59)))
        {
            dt_hour = hour;
            dt_min = min;
            dt_sec = sec;
            if (!isAxiom)
                std::cout << "Time - OK" << std::endl;
        } else {
            std::cout << "Time is incorrect" << std::endl;
            exit(1);
        }
    }
    else {
        std::cout << "Date is incorrect" << std::endl;
        exit(1);
    }
}

bool DateTime::checkDateTime(int year, int mon, int day, int hour, int min, int sec) {
    if (checkDate(year, mon, day) && (checkRange(hour, 0, 23)) && checkRange(min, 0, 59) && (checkRange(sec, 0, 59)) )
    {
        return true;
    } else {
        return false;
    }
}

int DateTime::dayInMonth(int month, bool isLeapers) {
    switch (month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 2:
            if (isLeapers)
                return 29;
            else
                return 28;
            // апрель, июнь, сентябрь и ноябрь
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
    }
}

unsigned long long DateTime::parseDateTime(int year, int mon, int day, int hour, int min, int sec) {
    bool isLeapers = false;
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    {
        isLeapers = true;
    }
    unsigned long long days = 0;

    /*
    while (year != 0)
    {
        days += 365;
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            days += 1;

            cout << "days + 1" << endl;
        }
        year--;
    }
     */
    year -= 1;
    days = year * 365 + year/4 - year/100 + year/400;
    //int days_DEBUG = 0;
    for (int month = 1; month != mon; month++ )
    {
        //days_DEBUG += dayInMonth(month, isLeapers);
        days += dayInMonth(month, isLeapers);
    }
    days += day;
    //days_DEBUG += day;
    dt_days = days;

    return days;
}

std::string DateTime::getTime() {
    bool isLeapers = false;
    long long days = dt_days;
    int year = 1; int mon = 1; int day = 1;

    /*
    year = days / 365;
    days -= year * 365;
    days -= year / 4;
    */

    while (days > 365 && !((days == 366) && isLeapers))
    {
        year++;
        days -= 365;
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        {
            days -= 1;
        }

        //if ((year+1) % 4 == 0 && ((year+1) % 100 != 0 || (year+1) % 400 == 0)) {
        if ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0)) {
            isLeapers = true;
        } else {
            isLeapers = false;
        }
    }

    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    {
        isLeapers = true;
    } else {
        isLeapers = false;
    }

    bool cont = true;
    while (cont) {
        if (days > dayInMonth(mon, isLeapers))
        {
            days -= dayInMonth(mon, isLeapers);
            mon++;
        } else { cont = false; break; }
    }

    day = days;

    //9-11-29 ===== 9-11-28
    //9-11-30 ===== 9-11-29

    //9-11-0 ===== 9-10-31
    //9-11-1 ===== 9-10-32

    std::string dt_string = std::to_string(year) + "-" + std::to_string(mon) + "-" + std::to_string(day);
    return dt_string;


    cout << year << endl;
    cout << mon << endl;
    cout << day << endl;
    /*
    while (days > 365 || ((days > 366) && isLeapers))
    {
        year++;
        days -= 365;
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        {
            days -= 1;
        }
        if ((year+1) % 4 == 0 && ((year+1) % 100 != 0 || (year+1) % 400 == 0)) {
            isLeapers = true;
        } else {
            isLeapers = false;
        }
    }

    while (days < )
     */
}

bool DateTime::_is_leap(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

long long DateTime::_days_before_year(int year) {
    year -= 1;
    return year * 365 + year/4 - year/100 + year/400;
}

int DateTime::_days_in_month(int year, int month) {
    if (month == 2 && _is_leap(year))
        return 29;
    return _DAYS_IN_MONTH[month];
}

int DateTime::_days_before_month(int year, int month) {
    return _DAYS_BEFORE_MONTH[month] + (month > 2 and _is_leap(year));
}

long long DateTime::ymd2ord(int year, short month, short day) {
    return (_days_before_year(year) +
            _days_before_month(year, month) +
            day);
}

DT_returnType DateTime::ord2ymd(long long n) {

    n -= 1;
    int n400 = n / _DI400Y; // count of 400 years in N
    n %= _DI400Y;
    int year = n400 * 400 + 1;
    int n100 = n / _DI100Y; // count of 100 years in N
    n %= _DI100Y;
    int n4 = n/ _DI4Y;
    n %= _DI4Y;
    int n1 = n / 365;
    n %= 365;

    year += n100 * 100 + n4 * 4 + n1;

    // Default symptoms for XXXX/12/31
    if (n1 == 4 or n100 == 4) {
        return DT_returnType(year - 1, 12, 31);
    }

    /*
    * Now the year is correct, and n is the offset from January 1.
    * Find the month via an estimate that either exact or one too large
    */
    bool leapYear = (n1 == 3 and (n4 != 24 or n100 == 3));
    int month = (n + 50) >> 5; // add 110010 and parsing it via offset
    int preceding = _DAYS_BEFORE_MONTH[month] + (month > 2 and leapYear);

    if (preceding > n) {  // estimate is too large
        month -= 1;
        preceding -= _DAYS_IN_MONTH[month] + (month == 2 and leapYear);
    }
    n -= preceding;
    return  DT_returnType(year, month, n + 1);
}









