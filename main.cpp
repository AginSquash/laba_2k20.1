#include <iostream>
#include "DT.h"

using namespace std;

int main() {
    DateTime dt(2020, 02, 24, 0, 0, 0);
    //dt.addDateTime(0, 02, 25, 23, 56, 58);
    cout << dt.subtractDateTime(0,5, 10, 0,0,0) << endl;
    //dt.addDateTime(AT_DAY, 5);
    //cout << dt.getDateTime();
    return 0;
}
