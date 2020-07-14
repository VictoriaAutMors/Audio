#include <iostream>
#include <math.h>
#include <vector>
#include <cstdlib>
using namespace std;

class Complex {
public:
    double Re, Im;
    Complex();
    Complex(double R);
    Complex(double R, double I);
    Complex operator +(const Complex &operand2) const;
    Complex operator *(double operand2) const;    
    Complex operator -(const Complex &operand2) const;
    Complex operator /(const double operand2) const;
    Complex operator ^(const double degree) const;
    friend std::ostream &operator<<(std::ostream &cout_object, const Complex operand);
};

Complex::Complex() {
    Re = 0;
    Im = 0;
}

Complex::Complex(double Re) {
    Complex::Re = Re;
    Im = 0;
}

Complex::Complex(double Re, double Im) {
    Complex::Re = Re;
    Complex::Im = Im;
}

Complex Complex::operator +(const Complex &operand2) const {
    return Complex(Re + operand2.Re, Im + operand2.Im);
}

Complex Complex::operator -(const Complex &operand2) const {
    return Complex(Re - operand2.Re, Im - operand2.Im);
}


Complex Complex::operator /(double operand2) const {
    return Complex(Re / operand2, Im / operand2);
}

Complex Complex::operator *(double operand2) const {
    return Complex(Re * operand2, Im * operand2);
}

Complex Complex::operator ^(double degree) const {
    return Complex(Re * cos(degree ) - Im * sin(degree), Im * cos(degree ) + Re * sin(degree));
}

std::ostream &operator << (std::ostream &cout_object, const Complex operand) {
    cout_object << operand.Re;
    if (operand.Im < 0) {
        cout_object << operand.Im;
    } else {
        cout_object << "+" << operand.Im;
    }
    cout_object << "i" << endl;
    return cout_object;
}


std::vector<Complex> f2s(const std::vector<Complex> &f) {
    std::vector<Complex> c;
    int n = f.size();
    c.resize(n);
    for (int k = 0; k < n; ++k) {
        for (int j = 0; j < n; ++j) {
            c[k] = c[k] + (f[j] ^ (((-2) * M_PI * k * j) / n));
        }
        c[k] = c[k] / n;
    }
    return c;
}


void fft_rec(std::vector<Complex> &f) {
    int n = f.size();
    if (n == 1) {
        return;
    }
    std::vector<Complex> even, odd;
    even.resize(n / 2);
    odd.resize(n / 2);
    for (int i = 0; i < n / 2; i++) {
        even[i] = f[i * 2];
        odd[i] = f[(i * 2) + 1];
    }
    fft_rec(even);
    fft_rec(odd);
    for (int i = 0; i < n / 2; i++) {
        f[i] = even[i] + (odd[i] ^ (-2 * i * M_PI / n));
        f[i + n / 2] = even[i] - (odd[i] ^ (-2 * M_PI * i / n));
    }
}

void fft(std::vector<Complex> &f) {
    int size = f.size();
    int n = 1;
    while (size > n) {
        n *= 2;
    }
    f.resize(n);
    for (int i = size; i < n; i++) {
        f[i] = 0;
    }
    fft_rec(f);
}

void fft_rec_i(std::vector<Complex> &f) {
    int n = f.size();
    if (n == 1) {
        return;
    }
    std::vector<Complex> even, odd;
    even.resize(n / 2);
    odd.resize(n / 2);
    for (int i = 0; i < n / 2; i++) {
        even[i] = f[i * 2];
        odd[i] = f[(i * 2) + 1];
    }
    fft_rec_i(even);
    fft_rec_i(odd);
    for (int i = 0; i <  n / 2; i++) {
        f[i] = even[i] + (odd[i] ^ (2 * M_PI * i / n));
        f[i + n / 2] = even[i] - (odd[i] ^ (2 * M_PI * i / n));
    }
}

void fft_i(std::vector<Complex> &f) {
    int size = f.size(), n = 1;
    while (size > n) {
        n *= 2;
    }
    f.resize(n);
    for (int i = size; i < n; i++) {
        f[i] = 0;
    }
    fft_rec_i(f);
}

std::vector <Complex> s2f(const std::vector<Complex> &c) {
    std::vector<Complex> f;
    int n = c.size();
    f.resize(n);
    for ( int j = 0; j < n; j++) {
        for(int k = 0; k < n; k++) {
            f[j] = f[j] + (c[k] ^ ((2 * M_PI * k * j) / n));
        }
    }
    return f;
}

int main() {
	Complex number;
	std::vector<Complex> f = {1 , 6 , 2 , 5 , 3 , 4}, Spectr, check;
    cout << "Start F:" << endl;
	for (int i = 0; i < f.size(); i++) {
		cout << f[i] << endl;
	}
	Spectr = f2s(f);
	check = s2f(Spectr);
    cout << "SPECTR of F with DFT:" << endl;
	for (int i = 0; i < Spectr.size(); i++) {

		cout << Spectr[i] << endl;;
	}
    cout << "F with DFT:" << endl;
	for (int i = 0; i < check.size(); i++) {
		cout << check[i] << endl;
	}
	cout << "SPECTR with FFT :\n";
    int f_size = f.size();
	fft(f);
	for (int i = 0; i < f.size(); i++) {
		cout << f[i] << endl;
	}
	fft_i(f);
    cout << "F with FFT" << endl;
    int n = f.size();
    while(n & (n - 1) != 0) {
        n++;
    }
	for (int i = 0; i < f_size; i++) {
		cout << f[i] / n << endl;
	}
	return 0;
}
