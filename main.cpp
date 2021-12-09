#include <iostream>
#include "polynomial.cpp"
using namespace std;

int main() {
    Polynomial p("2x^3 + -3x^2 + 4x^1 + 5x^0");
    cout << (p^5) << endl;
    return 0;
}
