#include <iostream>

using namespace std;

#define DEBUG

#include "OOP/DT.h"

int OOP()
{
    int year; int mon; int day; int hour; int min; int sec;
#ifdef DEBUG
    DateTime dt(2020, 03, 18, 0, 00, 00);
#endif
#ifndef DEBUG
    cout << "Введите год, месяц, день, час, минуту и секунду" <<endl;
    cin >> year >> mon >> day >> hour >> min >> sec;
    DateTime dt(year, mon, day, hour, min, sec);
#endif
    cout << dt.getDateTime() << endl;

    int date = 2020;
    while (date > 1)
    {
        date -= 1;
    }

    bool cont = true;
    while (cont)
    {
        cout << "Что вы хотите сделать?\n 1 - добавить дату\n 2 - вычесть дату\n 3 - проверить дату\n 4 - добавить N лет/дней/месяец/etc\n 5 - выйти" << endl;
        int chose;
        cin >> chose;
        switch (chose) {
            case 1:
                cout << "Введите год, месяц, день, час, минуту и секунду" <<endl;
                cin >> year >> mon >> day >> hour >> min >> sec;
                dt.addDateTime(year, mon, day, hour, min, sec);
                cout << dt.getDateTime() << endl;
                break;
            case 2: {
                cout << "Введите год, месяц, день, час, минуту и секунду" << endl;
                cin >> year >> mon >> day >> hour >> min >> sec;
                DateTime dt_sub = dt.subtractDateTime(year, mon, day, hour, min, sec);
                cout << dt_sub.getDateTime() << endl;
                break;
            }
            case 3:
                cout << "Введите год, месяц, день, час, минуту и секунду" <<endl;
                cin >> year >> mon >> day >> hour >> min >> sec;
                if (dt.checkDateTime(year, mon, day, hour, min, sec) ) {
                    cout << "Дата верна" <<endl;
                } else {
                    cout << "Дата не верна" << endl;
                }
                break;
            case 4:
                cout << "Что вы хотите добавить\n 1 - год\n 2 - месяц\n 3 - день\n 4 - час\n 5 - минуты\n 6 - секунды" << endl;
                int type;
                cin >> type;
                cout << "сколько вы хотите добавить?" << endl;
                int addingValue;
                cin >> addingValue;
                dt.addDateTime(type, addingValue);
                cout <<  dt.getDateTime() << endl;
                break;

            case 5:
                exit(0);
                break;

        }
    }
}

// Collab by Karina Romanova

int dayInM(int month, bool isLeapers)
{
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


int main() {
    //OOP();
    DateTime dt;
    dt.parseDateTime(2016, 12, 31, 0,0,0);
    //cout << dt.getTime();


    for (int year = 4; year < 6; year++)
    {
        for (int mon = 1; mon <= 12; mon++)
        {
            for (int day = 1; day <= 31; day++)
            {
                bool isLeapers = false;
                if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
                {
                    isLeapers = true;
                }
                if (dayInM(mon, isLeapers) < day)
                {
                    break;
                }

                DateTime dt;
                unsigned long long days = dt.parseDateTime(year, mon, day, 0,0,0);
                std::string dt_string = std::to_string(year) + "-" + std::to_string(mon) + "-" + std::to_string(day);
                std::string getTime = dt.getTime();
                if (dt_string != getTime)
                {
                    cout << dt_string << " ===== " << getTime << " (" << days << ")"<< endl;
                } else { cout << dt_string << " OK!"  << " (" << days << ")" << endl; }
            }
        }
    }

    return 0;
}
