#define _USE_MATH_DEFINES	// For pi

#include "Functions.h"
#include <iostream>
#include <vector>
#include <cmath>			// For constants

using namespace std;

#pragma once
class Solution
{
	vector<double> S;	// Solution vector of arguments
	double F, Omega;	

public:
	Solution(double x_min, double x_max, int dim, func f);	// First assignment
	Solution(const vector<double> _S, func f);				// New pheromone
	~Solution() {};

	double get_value(int index) const { return S[index]; };		// x[i], where i - dimension
	double get_f() const { return F; }							// function value on this points
	double count_omega(int l, int k, double q = .6e-1) const;	// for counting Gaussian function

	bool operator < (const Solution & other) { return F < other.F; }	// for sort
	friend ostream & operator<<(ostream & os, const Solution & s);		// for output
};

