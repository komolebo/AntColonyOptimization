#include "Solution.h"
#include <vector>
#include <queue>		// For roulette imitation

#pragma once
class T_Solutions
{
	func f;
	double x_min, x_max;
	vector<Solution> solutions;

	const double EVAPORATION_RATE = 5.0;
	const unsigned K, DIM;

public:
	T_Solutions(unsigned _k, unsigned _dim, double _x_min, double _x_max, func _f); 
	~T_Solutions() {};

	void update();
	void add(Solution s);

	const double count_sigma(int i, int l);

	unsigned choose_gaussian_func();

	vector<Solution> & get_solutions() { return solutions; }
};

