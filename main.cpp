#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;

#define pi 3.14159

class Node {
public:
    Node() : next(nullptr), coeff(0.0), power(0) {}
    Node(double _coeff, int _power) : next(nullptr), coeff(_coeff), power(_power) {}
    Node* next;
    double coeff;
    int power;
};

class Polynomial {
public:
    // Constructors
    Polynomial() : head(nullptr) {
    }
    Polynomial(const string s) : head(nullptr) {
        parse(s);
    }
    Polynomial(const char* s) : head(nullptr) {
        parse(s);
    }
    Polynomial(const Polynomial& other) : head(nullptr) {
        Node* other_current = other.head;
        while (other_current) {
            insert(other_current->coeff, other_current->power);
            other_current = other_current->next;
        }
    }
    ~Polynomial() {
        Node* current(nullptr);
        while (head) {
            current = head;
            head = head->next;
            delete current;
        }
    }
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            Node* current(nullptr);
            while (head) {
                current = head;
                head = head->next;
                delete current;
            }
            
            Node* other_current = other.head;
            while (other_current) {
                insert(other_current->coeff, other_current->power);
                other_current = other_current->next;
            }
        }
        return *this;
    }
    // Addition
    Polynomial operator+(const Polynomial& p) const {
        Polynomial result;
        Node* current = p.head;
        while (current) {
            result.insert(current->coeff, current->power);
            current = current->next;
        }
        return result;
    }
    Polynomial& operator+=(const Polynomial& p) {
        *this = *this + p;
        return *this;
    }
    // Substraction
    Polynomial operator-(const Polynomial& p) const {
        Polynomial result = *this;
        Node* current = p.head;
        while (current) {
            result.insert(-current->coeff, current->power);
            current = current->next;
        }
        return result;
    }
    Polynomial& operator-=(const Polynomial& p) {
        *this = *this - p;
        return *this;
    }
    // Scaling
    Polynomial operator*(double scalar) const {
        Polynomial result;
        Node* current = head;
        while (current) {
            result.insert(current->coeff * scalar, current->power);
            current = current->next;
        }
        return result;
    }
    // Multiplication
    Polynomial operator*(const Polynomial& p) const {
        Polynomial result;
        Node* this_current = head;
        Node* other_current = p.head;
        while (other_current) {
            while (this_current) {
                result.insert(this_current->coeff * other_current->coeff, this_current->power + other_current->power);
                this_current = this_current -> next;
            }
            this_current = head;
            other_current = other_current->next;
        }
        return result;
    }
    Polynomial& operator*=(const Polynomial& p) {
        *this = *this * p;
        return *this;
    }
    // Power
    Polynomial operator^(int power) const {
        Polynomial result;
        result.insert(1.0, 0);
        for (int idx=0; idx<power; ++idx) {
            result = result * (*this);
        }
        return result;
    }
    // Evaluation
    double operator()(double x) {
        double result(0.0);
        Node* current = head;
        while (current) {
            result += (current->coeff * pow(x, current->power));
            current = current->next;
        }
        return result;
    }

    int getDegree(void) const {
        if (head)
            return head->power;
        else
            return 0;
    }

    double getLeadingCoeff(void) const {
        if (head)
            return head->coeff;
        else
            return 0;
    }
    friend ostream& operator<<(ostream& os, const Polynomial& p);
private:
    Node* head;
    void parse(string s) {
        string coeff;
        string power;
        bool isCoeff = true;
        bool isPower = false;
        bool isnegative = false;
        for (size_t idx=0; idx!=s.length(); ++idx) {
            char c = s[idx];
            if (!isspace(c)) {
                if (c == '-') {
                    isnegative = true;
                    continue;
                }
                if (isdigit(c)) {
                    if (isCoeff) {
                        coeff += c;
                    }
                    if (isPower) {
                        power += c;
                    }
                }
                else if (c == '^') {
                    isCoeff = false;
                    isPower = true;
                }
                else if (c == '+') {
                    if (isnegative) {
                        insert(-stod(coeff), atoi(power.c_str()));
                    } else {
                        insert(stod(coeff), atoi(power.c_str()));
                    }
                    isCoeff = true;
                    isPower = false;
                    coeff.clear();
                    power.clear();
                    isnegative = false;
                } else {
                    continue;
                }
            }
        }
        if (isnegative) 
            insert(-stod(coeff), atoi(power.c_str()));
        else
            insert(stod(coeff), atoi(power.c_str()));
        return;
    }
    void insert(double c, int p) {
        Node* tmp = new Node(c, p);
        if (!head) {
            head = tmp;
            return;
        }
        if (head->power < p) {
            tmp->next = head;
            head = tmp;
            return;
        }
        Node* current = head;
        Node* pre(nullptr);
        while (current->power > p && current->next) {
            pre = current;
            current = current->next;
        }
        if (current->power <= p && current->next) {
            if (current->power == p) {
                current->coeff += c;
                if (!current->coeff) {
                    if (pre) {
                        pre->next = current->next;
                        delete current;
                    } else {
                        head = current->next;
                        delete current;
                    }
                }
            } else {
                tmp->next = current->next;
                current->next = tmp;
            }
        } else if (current->power > p && !current->next) {
            current->next = tmp;
        } else { // current->power <= p && !current->next
            current->coeff += c;
            if (!current->coeff) {
                if (pre) {
                    pre->next = current->next;
                    delete current;
                } else {
                    head = current->next;
                    delete current;
                }
            }
        }
    }
};
Polynomial operator*(double scalar, const Polynomial& p) {
    return p * scalar;
}
// Cout
ostream& operator<<(ostream& os, const Polynomial& p) {
    if (!p.head)
        os << 0;
    else {
        Node* current = p.head;
        while (current) {
            os << current->coeff << "x^" << current->power;
            current = current->next;
            if (current)
                os << " + ";
        }
    }
    return os;
}

int main() {
    Polynomial p("2x^3 + -3x^2 + 4x^1 + 5x^0");
    cout << (p^5) << endl;
    return 0;
}
