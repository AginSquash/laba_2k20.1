/*
 * by Karina Romanova
 * https://github.com/KarinaRomanova/1Lab
 */

#ifndef LABA8_DATE_H
#define LABA8_DATE_H

#include<string>
#include<iostream>

using namespace std;

class Date {
private:
    int day;
    int month;
    int year;
    int dayResult;
public:
    Date(int date_day, int date_month, int date_year); //установка даты
    std::string getDayResult();										  //название дня
    void getWeekend();										  //выходные
};



#endif //LABA8_DATE_H
