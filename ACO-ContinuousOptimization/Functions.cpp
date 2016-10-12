#include "Functions.h"

#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

typedef double(*func)(vector<double> & x);

double gaussian_random(double mue, double sigma) {
	double x1, x2, w, y;

	do {
		x1 = 2.0 * rand() / (RAND_MAX + 1) - 1.0;
		x2 = 2.0 * rand() / (RAND_MAX + 1) - 1.0;
		w = x1 * x1 + x2 * x2;
	} while (w >= 1.0);

	double llog = log(w);
	w = sqrt((-2.0 * llog) / w);
	y = x1 * w;

	return mue + sigma * y;
}


double sqr(double x) {
	return x*x;
}

double Sphere_function(vector<double> & S) {
	double res = .0;

	for (double v : S)
		res += v * v;

	return res;
}

double Ackley_function(vector<double> & S) {
	double a = 20, b = .2, c = 2 * M_PI, d = 20;

	double sigma1 = 0, sigma2 = 0; 

	for (double x : S) {
		sigma1 += x * x;
		sigma2 += cos(c*x);
	}

	return -a * pow(M_E, -b * sqrt(sigma1 / d)) - pow(M_E, sigma2 / d) + a + M_E;
}

double Griewank_function(vector<double> & S) {
	double sigma = 0, pi = 1.0;

	for (unsigned i = 0; i < S.size(); i++) {
		sigma += S[i] * S[i] / 4000;
		pi *= cos(S[i] / sqrt(i + 1));
	}

	return sigma - pi + 1;
}

double Rastrigin_function(vector<double> & S) {
	double sigma = 0;

	for (double x : S)
		sigma += x * x - 10 * cos(2 * M_PI);

	return 10 * S.size() + sigma;
}

double Rosenbrock_function(vector<double> & S) {
	double sigma = 0;

	for (unsigned i = 0; i < S.size() - 1; i++)
		sigma += 100 * sqr(S[i + 1] - sqr(S[i])) + sqr(S[i] - 1);

	return sigma;
}