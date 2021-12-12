#include <iostream>
#include "polynomial.h"
using namespace std;

int main() {
    Polynomial p("1x^1 + 1x^0");
    cout << (p^4) << endl;
    return 0;
}
