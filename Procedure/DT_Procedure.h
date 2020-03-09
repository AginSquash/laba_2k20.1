//
// Created by Vlad Vrublevsky on 09.03.2020.
//

#ifndef LABA8_DT_PROCEDURE_H
#define LABA8_DT_PROCEDURE_H


#include <string>

//DateTime(int year, int mon, int day, int hour, int min, int sec, bool isIntegrated = false);
//DateTime();
std::string getDateTime();
bool checkDate(int year, int mon, int day, bool isAddingDate = false);
int addDateTime(int year, int mon, int day, int hour, int min, int sec);
std::string subtractDateTime(int year, int mon, int day, int hour, int min, int sec);


#endif //LABA8_DT_PROCEDURE_H
