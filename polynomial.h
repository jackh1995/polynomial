#pragma once

#include <iostream>
using namespace std;

class Polynomial;

class Node {
friend class Polynomial;
friend ostream &operator<<(ostream &os, const Polynomial &p);
public:
    Node() : next(nullptr), coeff(0.0), power(0) {}
    Node(double _coeff, int _power) : next(nullptr), coeff(_coeff), power(_power) {}
private:
    Node *next;
    double coeff;
    int power;
};

class Polynomial {
public:
    // Constructors
    Polynomial();
    Polynomial(const char* s);
    // Rule of three
    Polynomial(const Polynomial &other);
    ~Polynomial();
    Polynomial &operator=(const Polynomial &other);
    // Addition
    Polynomial operator+(const Polynomial &p) const;
    Polynomial &operator+=(const Polynomial &p);
    // Substraction
    Polynomial operator-(const Polynomial &p) const;
    Polynomial &operator-=(const Polynomial &p);
    // Scaling
    Polynomial operator*(double scalar) const;
    // Multiplication
    Polynomial operator*(const Polynomial &p) const;
    Polynomial &operator*=(const Polynomial &p);
    // Power
    Polynomial operator^(int power) const;
    Polynomial &operator^=(int power);
    // Evaluation
    double operator()(double x) const;
    int getDegree(void) const;
    double getLeadingCoeff(void) const;
    // Print
    friend ostream &operator<<(ostream &os, const Polynomial &p);
private:
    Node *head;
    void parse(const char* s);
    void insert(double c, int p);
};

Polynomial operator*(double scalar, const Polynomial &p);