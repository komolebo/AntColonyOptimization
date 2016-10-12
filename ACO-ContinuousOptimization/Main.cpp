#include "Solution.h"
#include "T_Solutions.h"
#include "Functions.h"
#include <iostream>
#include <algorithm>	// sort

namespace SETTINGS {
	unsigned STEPS = 5000;
	const unsigned K = 200, ANTS = (unsigned)(K / 2);
	const unsigned D = 3;
}

using namespace std;
using namespace SETTINGS;

void process(T_Solutions *, func);


int main() {
	T_Solutions * table;
	
	table = new T_Solutions(K, D, -100, 100, Sphere_function);
	process(table, Sphere_function);
	cout << "Sphere function: " << table->get_solutions().front();
	delete table;

	table = new T_Solutions(K, D, -32.768, 32.768, Ackley_function);
	process(table, Ackley_function);
	cout << "Ackley function: " << table->get_solutions().front();
	delete table;

	table = new T_Solutions(K, D, -600, 600, Griewank_function);
	process(table, Griewank_function);
	cout << "Grienwank function: " << table->get_solutions().front();
	delete table;

	table = new T_Solutions(K, D, -5.12, 5.12, Rastrigin_function);
	process(table, Rastrigin_function);
	cout << "Rastrigin function: " << table->get_solutions().front();
	delete table;

	table = new T_Solutions(K, D, -5, 10, Rosenbrock_function);
	process(table, Rosenbrock_function);
	cout << "Rosenbrock function: " << table->get_solutions().front();
	delete table;
	
	getchar();
	return 0;
}

void process(T_Solutions *table, func f) {
	auto &solutions = table->get_solutions();

	for (unsigned step = 0; step < STEPS; step++) {
		// Sort by best fit: when f(x) is at min
		sort(solutions.begin(), solutions.end());

		// Remove worst solutions
		table->update();

		for (unsigned ant = 0; ant < ANTS; ant++) {
			// Choose Gaussian function by roulette
			int index_g_func = table->choose_gaussian_func();

			// Count new solution
			vector<double> new_roots;

			for (unsigned dim = 0; dim < D; dim++) {
				double mue = solutions[index_g_func].get_value(dim);
				double sigma = table->count_sigma(dim, index_g_func); //todo

				double x = gaussian_random(mue, sigma);
				new_roots.push_back(x);
			}

			// Add new solution
			solutions.push_back(Solution(new_roots, f));
		}
	}
}