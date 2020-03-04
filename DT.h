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
    DateTime(int year, int mon, int day, int hour, int min, int sec, bool isIntegrated = false)
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
            std::cout << "Data is incorrect" << std::endl;
            exit(1);
        }
    }
    std::string getDateTime()
    {
        std::string dt_string = parseInt(dt_year, 4) + "-" + parseInt(dt_mon) + "-" + parseInt(dt_day) + " " + parseInt(dt_hour) + ":" +
                           parseInt(dt_min) + ":" + parseInt(dt_sec);
        return dt_string;
    }
    bool checkDate(int year, int mon, int day, bool isAddingDate = false);
    int addDateTime(int year, int mon, int day, int hour, int min, int sec);
    int addDateTime(DT_addingType type, int count);
    int subtractDateTime(int year, int mon, int day, int hour, int min, int sec);
};

#endif //LABA8_DT_H
