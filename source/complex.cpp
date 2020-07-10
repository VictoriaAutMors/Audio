#include "complex.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>

Complex::Complex() {
	Re = 0;
	Im = 0;
};

Complex::Complex(double re = 0, double im = 0) {
	Re = re;
	Im = im;
};

Complex::Complex(const Complex &tmp) {
	Re = tmp.Re;
	Im = tmp.Im;
};

double Complex::re() const {
	return Re;
}

double Complex::amp() const {
	return sqrt(Re * Re + Im * Im);
}

double Complex::phase() const {
	if (Re == 0) {
		return M_PI/2;
	}
	return atan(Im/Re);
}

Complex Complex::operator+(Complex right) const {
	Complex tmp(Re + right.Re, Im + right.Im);
	return tmp;
}

Complex Complex::operator-(Complex right) const {
	Complex tmp(Re - right.Re, Im - right.Im);
	return tmp;
}

Complex Complex::operator*(double right) const {
	Complex tmp(Re * right, Im * right);
	return tmp;
}

Complex Complex::operator/(double right) const {
	Complex tmp(Re / right, Im / right);
	return tmp;
}

Complex Complex::operator^(double alpha) const {
	Complex obj(Re, Im);
	obj.Re = this -> amp() * cos(this -> phase() + alpha);
	obj.Im = this -> amp() * sin(this -> phase() + alpha);
	return obj;
}

Complex Complex::operator* (const Complex & right) const {
	Complex tmp(Re * right.re() - Im * right.im(),
				Re * right.im() + Im * right.re());
	return tmp;
}

Complex& Complex::operator=(const Complex & right) {
	Re = right.Re;
	Im = right.Im;
	return *this;
}

Complex& Complex::operator+=(const Complex & right) {
	(*this) = (*this) + right;
	return *this;
}

Complex& Complex::operator*=(const Complex & right) {
	(*this) = (*this) * right;
	return *this;
}


std::ostream& operator<<(std::ostream & output, const Complex & tmp) {
	if (tmp.Im < 0) {
		output << std::setprecision(3) << std::fixed << tmp.Re << " - " << -1 * tmp.Im << "i\n";
	} else {
		output << std::setprecision(3) << std::fixed << tmp.Re << " + " << tmp.Im << "i\n";
	}
	return output;
}

std::istream& operator>>(std::istream & input, Complex & tmp) {
	input >> tmp.Re;
	input >> tmp.Im;
	return input;
}