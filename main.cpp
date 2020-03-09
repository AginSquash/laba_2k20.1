#include <iostream>
#include "DT.h"

using namespace std;

int main() {
    DateTime dt(2020, 02, 24, 10, 5, 43);
    //dt.addDateTime(0, 02, 25, 23, 56, 58);
    cout << dt.subtractDateTime(2,5, 10, 6,7,13) << endl;
    //dt.addDateTime(AT_DAY, 5);
    //cout << dt.getDateTime();
    return 0;
}
