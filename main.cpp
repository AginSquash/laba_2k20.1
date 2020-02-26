#include <iostream>

#define DEBUG
using namespace std;

void debug_print(string debug_text)
{
#ifdef DEBUG
    cout << debug_text << endl;
#endif
}

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
        bool checkDate(int year, int mon, int day, bool isAddingDate = false);
        string parseInt(int value, int length = 2);

    public:
        DateTime(int year, int mon, int day, int hour, int min, int sec)
        {
            if (checkDate(year, mon, day))
            {
                dt_year = year;
                dt_mon = mon;
                dt_day = day;
                cout << "Date - OK" << endl;
                if ((checkRange(hour, 0, 23)) && checkRange(min, 0, 59) &&  (checkRange(sec, 0, 59)))
                {
                    dt_hour = hour;
                    dt_min = min;
                    dt_sec = sec;
                    cout << "Time - OK" << endl;
                } else {
                    cout << "Time is incorrect" << endl;
                    exit(1);
                }
            }
            else {
                cout << "Data is incorrect" << endl;
                exit(1);
            }
        }

        string getDateTime()
        {
            string dt_string = parseInt(dt_year, 4) + "-" + parseInt(dt_mon) + "-" + parseInt(dt_day) + " " + parseInt(dt_hour) + ":" +
                    parseInt(dt_min) + ":" + parseInt(dt_sec);
            return dt_string;
        }

        int addDateTime(int year, int mon, int day, int hour, int min, int sec);

        int addDateTime(DT_addingType type, int count);
};

string DateTime::parseInt(int value, int length) {
    string _value = to_string(value);
    while (_value.length() < length)
    {
        _value = "0" + _value;
    }
    return  _value;
}

int DateTime::addDateTime(DT_addingType type, int count) {
    int year = 0;
    int mon = 0;
    int day = 0;
    int hour = 0;
    int min = 0;
    int sec = 0;

    switch (type) {
        case AT_YEAR:
            year = count;
            break;
        case AT_MON:
            mon = count;
            break;
        case AT_DAY:
            day = count;
            break;
        case AT_HOUR:
            hour = count;
            break;
        case AT_MIN:
            min = count;
            break;
        case AT_SEC:
            sec = count;
            break;
    }

    return addDateTime(year, mon, day, hour, min, sec);
}

int DateTime::addDateTime(int year, int mon, int day, int hour, int min, int sec) {
    if (checkDate(year, mon, day, true) && (checkRange(hour, 0, 23)) && checkRange(min, 0, 59) && (checkRange(sec, 0, 59)) ) {
        int _sec = dt_sec + sec;
        while (_sec > 59) {
            min++;
            _sec -= 60;
        }
        dt_sec = _sec;
        debug_print("sec ok");

        int _min = dt_min + min;
        while (_min > 59) {
            hour++;
            _min -= 60;
        }
        dt_min = _min;
        debug_print("min ok");

        int _hour = dt_hour + hour;
        while (_hour > 23) {
            day++;
            _hour -= 24;
        }
        dt_hour = _hour; //TODO check this
        debug_print("hour ok");

        int _mon = dt_mon + mon;
        while (_mon > 12) {
            year++;
            _mon -= 12;
        }
        dt_mon = _mon;
        debug_print ("mon ok");

        dt_year += year;

        int _day = dt_day + day;
        int dayInMonth;
        do {
            switch (dt_mon) {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    dayInMonth = 31;
                    break;
                case 2:
                    if (dt_year % 4 == 0 && (dt_year % 100 != 0 || dt_year % 400 == 0))
                        dayInMonth = 29;
                    else
                        dayInMonth = 28;
                    break;
                    // апрель, июнь, сентябрь и ноябрь
                case 4:
                case 6:
                case 9:
                case 11:
                    dayInMonth = 30;
                    break;
            }
            if (_day > dayInMonth)
            {
                _day -= dayInMonth;
                dt_mon++;
            }
            debug_print("repeating");
        } while (_day > dayInMonth);
        debug_print("day ok");

        dt_day = _day;
        while (dt_mon > 12) {
            dt_year++;
            dt_mon -= 12;
        }
        debug_print("mon ok");
    }
    return 0;
}

bool DateTime::checkDate(int year, int mon, int day, bool isAddingDate) {
    switch (mon)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return checkRange(day, 1, 31);
        case 2:
            if ( year % 4 == 0 && (year % 100 != 0 || year % 400 ==0) )
                return checkRange(day, 1, 29);
            else
                return checkRange(day, 1, 28);
        // апрель, июнь, сентябрь и ноябрь
        case 4:
        case 6:
        case 9:
        case 11:
            return checkRange(day, 1, 30);

        default:
            if (isAddingDate && mon == 0)
                return true;
            cout << "Month is incorrect" << endl;
            return false;
    }
}

bool DateTime::checkRange(int value, int min, int max) {
    if (value < min)
        return false;
    if (value > max)
        return false;
    return true;
}


int main() {
    DateTime dt(2020, 02, 24, 13, 10, 10);
    //dt.addDateTime(0, 7, 25, 23, 56, 58);
    dt.addDateTime(AT_DAY, 5);
    cout << dt.getDateTime();
    return 0;
}
