#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex {
	double _re , _im;
public:
	Complex();
	Complex(double, double);
	Complex(const Complex &);
	~Complex() {};
	double re() const;
	double im() const;
	double amp() const;
	double phase() const;
	Complex operator+(Complex) const;
	Complex operator-(Complex) const;
	Complex operator*(double) const;
	Complex operator/(double) const;
	Complex operator^(double) const;
	Complex operator*(const Complex &) const;
	Complex& operator=(const Complex &);
	Complex& operator+=(const Complex &);
	Complex& operator*=(const Complex &);
	Complex& operator/=(double);
	friend std::istream& operator>>(std::istream &, Complex &);
	friend std::ostream& operator<< (std::ostream &, const Complex &);
};

#endif