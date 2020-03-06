//
// Created by Vlad Vrublevsky on 04.03.2020.
//

#ifndef LABA8_DT_H
#define LABA8_DT_H

#include <iostream>

enum DT_addingType
{
    AT_YEAR,
    AT_MON,
    AT_DAY,
    AT_HOUR,
    AT_MIN,
    AT_SEC
};

class DateTime
{
private:
    int dt_sec;
    int dt_min;
    int dt_hour;
    int dt_day;
    int dt_mon;
    int dt_year;
    bool checkRange(int value, int min, int max);
    std::string parseInt(int value, int length = 2);

public:
    DateTime(int year, int mon, int day, int hour, int min, int sec, bool isIntegrated = false);
    DateTime();
    std::string getDateTime();
    bool checkDate(int year, int mon, int day, bool isAddingDate = false);
    int addDateTime(int year, int mon, int day, int hour, int min, int sec);
    int addDateTime(DT_addingType type, int count);
    int subtractDateTime(int year, int mon, int day, int hour, int min, int sec);
};

#endif LABA8_DT_H
