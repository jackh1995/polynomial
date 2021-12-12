#include <cmath>
#include "polynomial.h"

Polynomial::Polynomial(const Polynomial &other) : head(nullptr) {
    Node *other_current = other.head;
    while (other_current) {
        insert(other_current->coeff, other_current->power);
        other_current = other_current->next;
    }
}

Polynomial::~Polynomial() {
    Node *current(nullptr);
    while (head) {
        current = head;
        head = head->next;
        delete current;
    }
}

Polynomial& Polynomial::operator=(const Polynomial &other) {
    if (this != &other) {
        Node *current(nullptr);
        while (head) {
            current = head;
            head = head->next;
            delete current;
        }

        Node *other_current = other.head;
        while (other_current) {
            insert(other_current->coeff, other_current->power);
            other_current = other_current->next;
        }
    }
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial &p) const {
    Polynomial result;
    Node *current = p.head;
    while (current) {
        result.insert(current->coeff, current->power);
        current = current->next;
    }
    return result;
}

Polynomial& Polynomial::operator+=(const Polynomial &p) {
    *this = *this + p;
    return *this;
}

Polynomial Polynomial::operator-(const Polynomial &p) const {
    Polynomial result = *this;
    Node *current = p.head;
    while (current) {
        result.insert(-current->coeff, current->power);
        current = current->next;
    }
    return result;
}

Polynomial &Polynomial::operator-=(const Polynomial &p) {
    *this = *this - p;
    return *this;
}

Polynomial Polynomial::operator*(double scalar) const {
    Polynomial result;
    Node *current = head;
    while (current) {
        result.insert(current->coeff * scalar, current->power);
        current = current->next;
    }
    return result;
}

Polynomial Polynomial::operator*(const Polynomial &p) const {
    Polynomial result;
    Node *this_current = head;
    Node *other_current = p.head;
    while (other_current) {
        while (this_current) {
            result.insert(this_current->coeff * other_current->coeff, this_current->power + other_current->power);
            this_current = this_current->next;
        }
        this_current = head;
        other_current = other_current->next;
    }
    return result;
}

Polynomial &Polynomial::operator*=(const Polynomial &p) {
    *this = *this * p;
    return *this;
}

Polynomial Polynomial::operator^(int power) const {
    Polynomial result;
    result.insert(1.0, 0);
    for (int idx = 0; idx < power; ++idx) {
        result = result * (*this);
    }
    return result;
}

double Polynomial::operator()(double x) const {
    double result(0.0);
    Node *current = head;
    while (current) {
        result += (current->coeff * pow(x, current->power));
        current = current->next;
    }
    return result;
}

int Polynomial::getDegree(void) const {
    if (head)
        return head->power;
    else
        return 0;
}

double Polynomial::getLeadingCoeff(void) const {
    if (head)
        return head->coeff;
    else
        return 0;
}

void Polynomial::parse(const char* s) {
    string coeff;
    string power;
    bool isCoeff = true;
    bool isPower = false;
    bool isnegative = false;
    for (const char* iter = s; *iter != '\0'; iter++) {
        char c = *iter;
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
            } else if (c == '^') {
                isCoeff = false;
                isPower = true;
            } else if (c == '+') {
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

void Polynomial::insert(double c, int p) {
    Node *tmp = new Node(c, p);
    if (!head) {
        head = tmp;
        return;
    }
    if (head->power < p) {
        tmp->next = head;
        head = tmp;
        return;
    }
    Node *current = head;
    Node *pre(nullptr);
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

Polynomial operator*(double scalar, const Polynomial &p) {
    return p * scalar;
}

ostream &operator<<(ostream &os, const Polynomial &p) {
    if (!p.head)
        os << 0;
    else {
        Node *current = p.head;
        while (current) {
            os << current->coeff << "x^" << current->power;
            current = current->next;
            if (current)
                os << " + ";
        }
    }
    return os;
}