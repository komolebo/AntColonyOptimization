#include "Solution.h"


Solution::Solution(double x_min, double x_max, int dim, func f)
{
	for (int i = 0; i < dim; i++)
		S.push_back(x_min + (x_max - x_min) * ((double)rand() / RAND_MAX));

	F = f(S);
}

Solution::Solution(const vector<double> _S, func f)
{
	S = _S;
	F = f(S);
}

double Solution::count_omega(int l, int k, double q) const
{
	return pow(M_E, -sqr(l) / (2 * q * q * k * k)) / (q * k * sqrt(2 * M_PI));
}

ostream & operator<<(ostream & os, const Solution & s)
{
	os << "[";

	for (double x : s.S)
		os << x << " ";
	os << "]" << endl;

	return os;
}
