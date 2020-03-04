#include <iostream>
#include "DT.h"

using namespace std;

int main() {
    DateTime dt(2020, 02, 24, 13, 10, 10);
    //dt.addDateTime(0, 7, 25, 23, 56, 58);
    dt.addDateTime(AT_DAY, 5);
    cout << dt.getDateTime();
    return 0;
}
