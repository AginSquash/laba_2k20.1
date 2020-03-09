#ifndef LABA8_DATE_H
#define LABA8_DATE_H

#include<string>
#include<iostream>


/*
 * by Karina Romanova
 * https://github.com/KarinaRomanova/1Lab
 */

using namespace std;

class Date {
private:
    int day;
    int month;
    int year;
    int dayResult;
public:
    Date(int date_day, int date_month, int date_year); //установка даты
    void setDayResult();									  //номер дня в неделе
    std::string getDayResult();										  //название дня
    void getWeekend();										  //выходные
};



#endif //LABA8_DATE_H
