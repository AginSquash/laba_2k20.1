//
// Created by Vlad Vrublevsky on 04.03.2020.
//

#include "DT.h"

void debug_print(std::string debug_text)
{
#ifdef DEBUG
    std::cout << debug_text << std::endl;
#endif
}

std::string DateTime::parseInt(int value, int length) {
    std::string _value = std::to_string(value);
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
            //std::cout << "Month is incorrect" << std::endl;
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
    std::string dt_string = parseInt(dt_year, 4) + "-" + parseInt(dt_mon) + "-" + parseInt(dt_day) +  " (" + date.getDayResult() +  ") " + " " + parseInt(dt_hour) + ":" +
                            parseInt(dt_min) + ":" + parseInt(dt_sec);
    return dt_string;
}

std::string DateTime::subtractDateTime(int year, int mon, int day, int hour, int min, int sec)
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

    Date date(dt_day, dt_mon, dt_year);
    std::string dt_string = parseInt(dt_year, 4) + "-" + parseInt(dt_mon) + "-" + parseInt(dt_day) +  " (" + date.getDayResult() +  ") " + " " + parseInt(dt_hour) + ":" +
                            parseInt(dt_min) + ":" + parseInt(dt_sec);
    return dt_string;
}

DateTime::DateTime() {}

DateTime::DateTime(int year, int mon, int day, int hour, int min, int sec, bool isIntegrated)
{
    if (checkDate(year, mon, day))
    {
        dt_year = year;
        dt_mon = mon;
        dt_day = day;
        if (!isIntegrated)
            std::cout << "Date - OK" << std::endl;
        if ((checkRange(hour, 0, 23)) && checkRange(min, 0, 59) &&  (checkRange(sec, 0, 59)))
        {
            dt_hour = hour;
            dt_min = min;
            dt_sec = sec;
            if (!isIntegrated)
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
