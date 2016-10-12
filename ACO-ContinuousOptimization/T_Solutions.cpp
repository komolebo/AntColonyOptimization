#include "T_Solutions.h"


T_Solutions::T_Solutions(unsigned _k, unsigned  _dim, double _x_min, double _x_max, func _f) :
	K(_k), DIM(_dim), x_min(_x_min), x_max(_x_max), f(_f)
{
	for (unsigned i = 0; i < K; i++)
		solutions.push_back(Solution(x_min, x_max, DIM, f));
}

void T_Solutions::update()
{
	while (solutions.size() > K)
		solutions.pop_back();
}

void T_Solutions::add(Solution s)
{
	solutions.push_back(s);
}

const double T_Solutions::count_sigma(int i, int l)
{
	double sigma = 0;

	for (unsigned e = 0; e < K; e++)
		sigma += solutions[e].get_value(i) - solutions[l].get_value(i);

	return EVAPORATION_RATE * sigma / (K - 1);
}

unsigned T_Solutions::choose_gaussian_func()
{
	double omega_sum = 0;
	for (unsigned l = 0; l < solutions.size(); l++)
		omega_sum += solutions[l].count_omega(l, K);

	// Build roulette vector
	queue<double> roulette;
	double cumulative_p = 0;
	for (unsigned l = 0; l < solutions.size(); l++) {
		cumulative_p += solutions[l].count_omega(l, K) / omega_sum;
		roulette.push(cumulative_p);
	}

	// Choose roulette
	double rand_p = (double)rand() / (RAND_MAX + 1);
	
	unsigned gaussian_func_index = 0;
	while (roulette.front() < rand_p) {
		roulette.pop();
		gaussian_func_index++;
	}

	return gaussian_func_index;
}
