#include <iostream>

using namespace std;

#define DEBUG

#include "OOP/DT.h"

int OOP()
{
    int year; int mon; int day; int hour; int min; int sec;
#ifdef DEBUG
    DateTime dt(2020, 02, 26, 0, 00, 00);
#endif
#ifndef DEBUG
    cout << "Введите год, месяц, день, час, минуту и секунду" <<endl;
    cin >> year >> mon >> day >> hour >> min >> sec;
    DateTime dt(year, mon, day, hour, min, sec);
#endif
    cout << dt.getDateTime() << endl;
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
                dt.subtractDateTime(year, mon, day, hour, min, sec);
                cout << dt.getDateTime() << endl;
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

// Collab with Karina Romanova

int main() {

#ifdef DEBUG
    DateTime dt(2020, 03, 24, 0, 0, 0);
    DateTime dt1(  10, 04, 5, 5, 1, 0);
    DateTime dt2(2020, 03, 24, 0, 0, 0);

    DateTime dt3 = dt - dt1;
    dt3 -= dt1;
   // DateTime dt3 = dt + dt1;
    //cout << int(dt3) << endl;

    //dt += dt1;
    cout << dt3 << endl;

    if (dt >= dt2)
    {
        cout << "dt >= dt2 - true" << endl;
    }

    cout << dt1[AT_DAY] << endl;
#endif
#ifndef DEBUG
    OOP();
#endif
    return 0;
}
