#pragma once
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

class Node {
public:
    Node() : next(nullptr), coeff(0.0), power(0) {}
    Node(double _coeff, int _power) : next(nullptr), coeff(_coeff), power(_power) {}
    Node *next;
    double coeff;
    int power;
};

class Polynomial {
public:
    // Constructors
    Polynomial() : head(nullptr) {}
    Polynomial(const string s) : head(nullptr) { parse(s); }
    Polynomial(const char *s) : head(nullptr) { parse(s); }
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
    // Evaluation
    double operator()(double x) const;
    int getDegree(void) const;
    double getLeadingCoeff(void) const;
    // Print
    friend ostream &operator<<(ostream &os, const Polynomial &p);
private:
    Node *head;
    void parse(string s);
    void insert(double c, int p);
};