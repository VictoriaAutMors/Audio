#include "complex.hpp"
#include <vector>
#include <cmath>
#include <iostream>

std::vector<Complex> f2s(std::vector<Complex> f) {
	int n = f.size();
	std::vector<Complex> s;
	s.resize(n);
	for (int counter = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			s[i] += f[j] ^ (-2 * M_PI * j * i / n);
		}
		s[i] = s[i] / n;
	}
	return s;
}

std::vector<Complex> s2f(std::vector<Complex> s) {
	int n = s.size();
	std::vector<Complex> f;
	f.resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			f[i] += s[j] ^ (2 * M_PI * j * i / n);
		}
	}
	return f;
}

void fft(std::vector<Complex> & a) {
	int n = a.size();
	if (n == 1)
		return;
	std::vector<Complex> a0(n/2),  a1(n/2);
	for (int i = 0, j = 0; i < n; i += 2, j++) {
		a0[j] = a[i];
		a1[j] = a[i + 1];
	}
	fft(a0);
	fft(a1);
	double ang = -2 * M_PI/n;
	Complex w(1),  wn(cos(ang), sin(ang));
	for (int i = 0; i < n/2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		w *= wn;
	}
}

void rev_fft(std::vector<Complex> & a) {
	int n = a.size();
	if (n == 1)
		return;
	std::vector<Complex> a0(n/2),  a1(n/2);
	for (int i = 0, j = 0; i < n; i += 2, j++) {
		a0[j] = a[i];
		a1[j] = a[i + 1];
	}
	rev_fft(a0);
	rev_fft(a1);
	double ang = 2 * M_PI/n;
	Complex w(1),  wn(cos(ang), sin(ang));
	for (int i = 0; i < n/2; i++) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		a[i] /= 2;
		a[i + n / 2] /= 2;
		w *= wn;
	}
}

void prepare_fft(std::vector <Complex> & a) {
	int n_old = a.size(), n_new = 1;
	while(n_old > n_new)
		n_new *= 2;
	a.resize(n_new);
	for (int i = n_old; i < n_new; i++)
		a[i] = 0;
}

int main() {
	Complex number, tmp;
    std::vector<Complex> f, s, check;
    int length;
    std::cout << "Enter length:" << std::endl;
    std::cin >> length;
    for (int i = 0; i < length; i++) {
        std::cin >> tmp;
        f.push_back(tmp);
    }
	int counter = 0;
	for (auto &num: f) {
		std::cout << "f[" << counter << "] = " << num;
        counter++;
	}
	s = f2s(f);
	check = s2f(s);
	std::cout << std::endl;
	counter = 0;
	for (auto & num: s) {
		std::cout << "s[" << counter << "] = " << num;
		std::cout << "|s[" << counter << "]| = " << num.amp() << std::endl;
        counter++;
	}
    std::cout << std::endl;
	counter = 0;
	for (auto & num: check) {
		std::cout << "f[" << counter << "] = " << num;
        counter++;
	}
	std::cout << "FFT:" << std::endl;
    prepare_fft(f);
	fft(f);
	counter = 0;
	for (auto & num: f) {
		std::cout << "FFT[" << counter << "] = " << num;
        counter++;
	}
	rev_fft(f);
    std::cout << std::endl;
	counter = 0;
	for (auto & num: f) {
		std::cout << "REVERSE FFT[" << counter << "] = " << num;
        counter++;
	}
	return 0;
}
