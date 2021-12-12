#include <iostream>
#include "polynomial.h"
using namespace std;

class Polynomial;

int main() {
    const char* p1 = "1x^1 + 1x^0";
    Polynomial poly1(p1);
    Polynomial poly2(poly1);
    Polynomial poly3 = poly1;
    cout << poly2 << endl;
    cout << poly3 << endl;
    Polynomial poly4;
    poly4 = (poly1 + poly1)^2;
    cout << poly4 << endl;
    return 0;
}
