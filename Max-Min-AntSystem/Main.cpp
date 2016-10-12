#include "Functions.h"
#include <ctime>			// for randomize

using namespace std;

void process(int from, int to);		// forward declaration

string Setting::FILENAME;		// variable declaration from Funcions.h


int main() {
	srand((int)time(0));		// randomize

	Setting::FILENAME = "data/yuzSHP55.aco";
	process(1, 31);
	getchar();
	
	Setting::FILENAME = "data/yuzSHP95.aco";
	process(0, 94);
	getchar();
	
	Setting::FILENAME = "data/yuzSHP155.aco";
	process(0, 154);
	getchar();

	return 0;
}

void output_best(Matrix *matrix, Solution *solution) {
	cout << "F(x)=" << count_cost(matrix, solution) << " :: ";
	for (int node : *solution)
		cout << node << " ";
	cout << endl;
}

void process(int from, int to)
{
	Matrix *matrix;
	vector<Ant> *ants;
	Solution *solution = NULL;

	// Create ants
	ants = new vector<Ant>(Setting::ANTS_NUM, { from, vector<int>(1, from)});
	
	// Complete graph of edges
	matrix = new Matrix;
	read_file(matrix);
	
	// Init pheromones level
	for (auto &row : *matrix)
		for (auto &node : row)
			node.pheromone = Setting::INIT_PHEROMONES;

	for (unsigned step = 0; step < Setting::STEPS; step++) {
		// Move ants
		for (auto &ant : *ants) {
			// Get neighbours
			vector<int> neighbours;
			for (unsigned node_to = 0; node_to < matrix->size(); node_to++) {
				// Check if ant hasn't visited the node
				if (find(ant.way.begin(), ant.way.end(), node_to) != ant.way.end())
					continue;

				if ((*matrix)[ant.position][node_to].dist > 0)
					neighbours.push_back(node_to);
			}

			if (!neighbours.size()) continue;

			// Build roulette vector for random choosing
			deque<double> roulette;
			double cummulator = 0;
			for (int neighbour : neighbours) {
				cummulator += count_probability(matrix, &ant, ant.position, neighbour);
				roulette.push_back(cummulator);
			}

			// Play roulette and see what neighbour is choosen
			int next_node = neighbours[random_roulette_ind(&roulette)];

			// Move ant
			ant.way.push_back(next_node);
			ant.position = next_node;
		}


		// check if new solution found
		for (Ant &ant : *ants) {
			// Mark ant that found way to
			if (ant.way.back() == to) {
				if (solution == NULL) {					// if first solution
					solution = new Solution(ant.way);
					output_best(matrix, solution);
				}
				else {							// compare with existing solution
					if (count_cost(matrix, &ant.way) > count_cost(matrix, solution)) {
						*solution = ant.way;
						output_best(matrix, solution);
					}
				}

				// Replace completed ant
				ant = { from, vector<int>(1, from) };
			}
		}

		// If solution found then update pheromones
		if (solution)
			update_pheromones(matrix, solution);

		evaporate_pheromones(matrix);
	}

	output_best(matrix, solution);
	cout << "Processing finished..." << endl;

	delete matrix;
	delete ants;
	delete solution;
}
