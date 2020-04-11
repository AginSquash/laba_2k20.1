//
// Created by Vlad Vrublevsky on 04.03.2020.
//

#include "DT.h"

//#define DEBUG

void debug_print(std::string debug_text)
{
#ifdef DEBUG
    std::cout << "!" << debug_text << std::endl;
#endif
}

void debug_print(std::string debug_text, int value)
{
#ifdef DEBUG
    std::cout << "!" << debug_text << " " << value << std::endl;
#endif
}

DateTime DateTime::addDateTime(int type, int count) {
    int year = 0;
    int mon = 0;
    int day = 1;
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

DateTime DateTime::addDateTime(int year, int mon, int day, int hour, int min, int sec) {
    if (checkDate(year, mon, day, true)) {
        int time2add = hms2ord(hour, min, sec);
        debug_print("time2add", time2add);
        year++;
        long long date2add = ymd2ord(year, mon, day);
        debug_print("date2add", date2add);
        return addDaysSeconds(date2add, time2add);
    }
    return DateTime(0, 0, true);
}

DateTime DateTime::addDaysSeconds(long long days, int seconds) {
    long long daysReturn  = dt_days + days + ((dt_seconds + seconds) / _SI24H);
    int secondsReturn = (dt_seconds + seconds) % _SI24H;
    return DateTime(daysReturn, secondsReturn, true);
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

std::string DateTime::parseDT(int value, int length){
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



std::string DateTime::getDateTime()
{
    DT_YearMonthDay ymd = ord2ymd(dt_days);
    DT_HourMinSec hms = ord2hms(dt_seconds);

    Date date(ymd.day, ymd.month, ymd.year);
    std::string weekday = " (" + date.getDayResult() + ") ";

    std::string output = parseDT(ymd.year, 4) + "-" + parseDT(ymd.month) + "-" + parseDT(ymd.day) + (isRange ? " " : weekday)
            + " " + parseDT(hms.hour) + ":" + parseDT(hms.min) + ":" + parseDT(hms.sec) + (isRange ? " ( DAYS: " + std::to_string(dt_days) +  " / SECONDS: " + std::to_string(dt_seconds) + " )" : "");

    return output;
}

int DateTime::abs(int value){
    if (value < 0)
        return value * (-1);
    return value;
}

DateTime DateTime::subtractDateTime(int year, int mon, int day, int hour, int min, int sec)
{
    if (checkDate(year, mon, day, true)) {
        int time2sub = hms2ord(hour, min, sec);
        debug_print("time2sub", time2sub);
        long long date2sub = ymd2ord(year, mon, day);
        debug_print("date2sub", date2sub);

        return subtractDaysSeconds(date2sub, time2sub);
    }
    return DateTime(0,0, true);
}

DateTime DateTime::subtractDaysSeconds(long long days, int seconds) {
    long long daysReturn = dt_days - days + (abs((dt_seconds - seconds)) / _SI24H);
    int secondsReturn  = abs((dt_seconds - seconds)) % _SI24H;
    return DateTime(daysReturn, secondsReturn, true);
}

DateTime::DateTime() { }

DateTime::DateTime(int year, int mon, int day, int hour, int min, int sec)
{
    if (checkDate(year, mon, day))
    {
        year++;
        dt_days = ymd2ord(year, mon, day);
        if ((checkRange(hour, 0, 23)) && checkRange(min, 0, 59) &&  (checkRange(sec, 0, 59)))
        {
            dt_seconds = hms2ord(hour, min, sec);
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

DateTime::DateTime(long long days, int seconds, bool isRange) : dt_days(days), dt_seconds(seconds), isRange(isRange) {

}

bool DateTime::checkDateTime(int year, int mon, int day, int hour, int min, int sec) {
    if (checkDate(year, mon, day) && (checkRange(hour, 0, 23)) && checkRange(min, 0, 59) && (checkRange(sec, 0, 59)) )
    {
        return true;
    } else {
        return false;
    }
}

bool DateTime::_is_leap(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

long long DateTime::days_before_year(int year) {
    year -= 1;
    return year * 365 + year/4 - year/100 + year/400;
}

int DateTime::days_in_month(int year, int month) {
    if (month == 2 && _is_leap(year))
        return 29;
    return _DAYS_IN_MONTH[month];
}

int DateTime::days_before_month(int year, int month) {
    return _DAYS_BEFORE_MONTH[month] + (month > 2 and _is_leap(year));
}

long long DateTime::ymd2ord(int year, short month, short day) {
    return (days_before_year(year) +
            days_before_month(year, month) +
            day);
}

DT_YearMonthDay DateTime::ord2ymd(long long n) {

    short factor = 1;
    if (n < 0)
    {
        n *= (-1);
        factor = (-1);
    }
    n -= 1;
    int n400 = n / _DI400Y; // count of 400 years in N
    n %= _DI400Y;
    int year = n400 * 400;  // This line mb need '+ 1' for next upgardes
    int n100 = n / _DI100Y; // count of 100 years in N
    n %= _DI100Y;
    int n4 = n/ _DI4Y;
    n %= _DI4Y;
    int n1 = n / 365;
    n %= 365;

    year += n100 * 100 + n4 * 4 + n1;

    // Default symptoms for XXXX/12/31
    if (n1 == 4 or n100 == 4) {
        return DT_YearMonthDay(year - 1, 12, 31);
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
    return  DT_YearMonthDay( (factor) * year, month, n + 1);
}

int DateTime::hms2ord(int hour, int min, int sec) {
    int seconds = hour * _SI1H + min * _SI1M + sec;
    return seconds;
}

DT_HourMinSec DateTime::ord2hms(int n) {
    int hours = n / _SI1H;
    n %= _SI1H;
    int min = n / _SI1M;
    n %= _SI1M;
    int sec = n;

    return DT_HourMinSec(hours, min, sec);
}

DateTime& DateTime::operator=(const DateTime &dt) {
        dt_days = dt.dt_days;
        dt_seconds = dt.dt_seconds;
        return *this;
}

std::ostream& operator<<(std::ostream &out, DateTime &dt) {
    return out << dt.getDateTime();
}

int DateTime::operator[](const DT_timeType dtType) {
    switch (dtType) {
        case AT_YEAR:
            return ord2ymd(dt_days).year;
        case AT_MON:
            return ord2ymd(dt_days).month;
        case AT_DAY:
            return ord2ymd(dt_days).day;
        case AT_HOUR:
            return ord2hms(dt_seconds).hour;
        case AT_MIN:
            return ord2hms(dt_seconds).min;
        case AT_SEC:
            return ord2hms(dt_seconds).sec;
    }
}

DateTime& DateTime::operator+= (DateTime &dt) {
    *this = addDaysSeconds(dt.dt_days, dt.dt_seconds);

    return *this;
}

DateTime DateTime::operator+ (DateTime dt) {
    DateTime newDt = addDaysSeconds(dt.dt_days, dt.dt_seconds);
    return newDt;
}

DateTime& DateTime::operator-= (DateTime &dt) {
    *this = subtractDaysSeconds(dt.dt_days, dt.dt_seconds);

    return *this;
}

DateTime DateTime::operator- (DateTime dt) {
    DateTime newDt = subtractDaysSeconds(dt.dt_days, dt.dt_seconds);
    return newDt;
}

bool operator== (const DateTime &dt1, const DateTime &dt2)
{
    return (dt1.dt_days == dt2.dt_days &&
            dt1.dt_seconds== dt2.dt_seconds);
}

bool operator!= (const DateTime &dt1, const DateTime &dt2)
{
    return !(dt1 == dt2);
}

bool operator> (const DateTime &dt1, const DateTime &dt2) {
    if (dt1.dt_days > dt2.dt_days)
        return true;
    if (dt1.dt_days < dt2.dt_days)
        return false;
    if (dt1.dt_seconds > dt2.dt_seconds) {
        return true;
    } else {
        return false;
    }
}

bool operator>= (const DateTime &dt1, const DateTime &dt2) {
    if (dt1 == dt2) {
        return true;
    }
    return dt1>dt2;
}

bool operator< (const DateTime &dt1, const DateTime &dt2) {
    if (dt1.dt_days < dt2.dt_days)
        return true;
    if (dt1.dt_days > dt2.dt_days)
        return false;
    if (dt1.dt_seconds < dt2.dt_seconds) {
        return true;
    } else {
        return false;
    }
}

bool operator<= (const DateTime &dt1, const DateTime &dt2) {
    if (dt1 == dt2) {
        return true;
    }
    return dt1<dt2;
}

DateTime::operator int() {
    return dt_days;
}