/*
 * by Karina Romanova
 * https://github.com/KarinaRomanova/1Lab
 */

#include "Date.h"

Date::Date(int date_day, int date_month, int date_year)
{
    day = date_day;
    month = date_month;
    year = date_year;

    int a;
    int yearcalc;
    int monthcalc;
    a = (14 - month) / 12;
    yearcalc = year - a;
    monthcalc = month + (12 * a) - 2;
    dayResult = (day + (31 * monthcalc) / 12 + yearcalc + yearcalc / 4 - yearcalc / 100 + yearcalc / 400) % 7;
}

std::string Date::getDayResult()
{
    string dayString;
    switch (dayResult) {
        case 0:
            dayString = "Sunday";
            break;
        case 1:
            dayString = "Monday";
            break;
        case 2:
            dayString = "Tuesday";
            break;
        case 3:
            dayString = "Wednesday";
            break;
        case 4:
            dayString = "Thursday";
            break;
        case 5:
            dayString = "Friday";
            break;
        case 6:
            dayString = "Saturday";
        default:
            //cout << "Error in DATE.cpp" << endl;
            break;
    }
    return dayString;
}
void Date::getWeekend()
{
    if (dayResult == 5 || dayResult == 6)
    {
        cout << "Weekend\n";
    }
    if (day == 31 && month == 12)
    {
        cout << "Weekend\n";
    }
    if (day == 8 && month == 3)
    {
        cout << "Weekend\n";
    }
    if (day == 23 && month == 2) {
        cout << "Weekend\n";
    }
    if (day == 9 && month == 5) {
        cout << "Weekend\n";
    }
    if (day == 1 && month == 5) {
        cout << "Weekend\n";
    }
}
