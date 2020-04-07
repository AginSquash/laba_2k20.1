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

// Collab by Karina Romanova

int main() {
    //OOP();
    //DateTime dt();
    //long long n =  dt.ymd2ord(2018, 9, 23);
    //cout << dt.ord2ymd(n);
    //int n = dt.hms2ord(23, 43, 24);
    //dt.ord2hms(n);


#ifdef DEBUG
    DateTime dt(2020, 03, 24, 0, 0, 0);
    DateTime dt0(2020, 03, 24, 0, 0, 0);
    DateTime dt1(3, 03, 24, 5, 1, 0);

    DateTime dt3 = dt+dt1;

#endif

    //cout << dt.getDateTime();
    //dt.addDateTime(1,2,3,4,5,6);
    //dt.subtractDateTime(2019, 9, 22, 0, 0, 0);
    cout << (dt0 < dt) << endl;
    cout << (dt <= dt1) << endl;
    cout << (dt >= dt1) << endl;
    cout << dt3;
    cout << dt1;
    return 0;
}
