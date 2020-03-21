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

class DateTime
{
private:
    int dt_sec  = 0;
    int dt_min  = 0;
    int dt_hour = 0;
    int dt_day  = 0;
    int dt_mon  = 0;
    int dt_year = 0;
    bool axiom = false;
    bool checkRange(int value, int min, int max);
    std::string parseInt(int value, int length = 2);

public:
    DateTime(int year, int mon, int day, int hour, int min, int sec, bool isAxiom = false);
    DateTime();
    std::string getDateTime();
    bool checkDate(int year, int mon, int day, bool isAddingDate = false);
    bool checkDateTime(int year, int mon, int day, int hour, int min, int sec);
    int addDateTime(int year, int mon, int day, int hour, int min, int sec);
    int addDateTime(int type, int count);
    DateTime subtractDateTime(int year, int mon, int day, int hour, int min, int sec);
};

#endif