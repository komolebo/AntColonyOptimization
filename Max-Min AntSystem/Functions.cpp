#include "Functions.h"
#include <fstream>		// ifstream
#include <sstream>      // std::istringstream
#include <string>

using namespace std;


void read_file(Matrix *matrix)
{
	ifstream f(Setting::FILENAME);
	string line, tmp;
	int points = -1, line_index = 0, distance;

	while (getline(f, line))
	{
		istringstream iss(line);

		switch (line.front())
		{
		case 'p':
			iss >> tmp;		// read 'p' symbol
			iss >> points;	// read_file size

			// Fill matrix
			for (int i = 0; i < points; i++) 
				matrix->push_back(vector<Edge>());

			break;

		case 'i':
			if (points == -1) {
				perror("File has no nodes count\n");
				exit(-1);
			}

			// read 'i' symbol
			iss >> tmp;
			
			for (int i = 0; i < points; i++) {
				iss >> distance;
				(*matrix)[line_index].push_back({distance, Setting::INIT_PHEROMONES});
			};

			line_index++;

			break;

		case 'c':	// skip comments
		default:
			break;
		}
	}
}

double count_probability(Matrix *matrix, Ant *ant, int i, int j)
{
	if ((*matrix)[i][j].dist == 0) return 0;

	double sigma = 0.0;

	// sigma is summary of tau*teta of all edges to neighbour nodes
	for (unsigned k = 0; k < matrix->size(); k++) {
		auto &edge_to = (*matrix)[i][k];

		// check only neighbour nodes, throw nodes where ant has been to
		if (edge_to.dist && find(ant->way.begin(), ant->way.end(), k) == ant->way.end())
			sigma += pow(edge_to.pheromone, Setting::ALPHA) / pow(edge_to.dist, Setting::BETA);
	}

	return  pow((*matrix)[i][j].pheromone, Setting::ALPHA) / pow((*matrix)[i][j].dist, Setting::BETA) / sigma;
}

double count_cost(Matrix *matrix, Solution *way)
{
	if (way == NULL || way->size() == 0) return 0.0;

	// Get length of best way
	double sum_dist = 0;
	for (unsigned node = 0; node < way->size() - 1; node++)
		sum_dist += (*matrix)[(*way)[node]][(*way)[node+1]].dist;

	return 1. / sum_dist;
}

int random_roulette_ind(deque<double> *roulette)
{
	const double rand_val = (double)rand() / (RAND_MAX + 1);
	
	int index = 0;
	while (roulette->front() < rand_val) {
		roulette->pop_front();
		index++;
	}

	return index;
}

void update_pheromones(Matrix *matrix, Solution *best_solution)
{
	double cost = count_cost(matrix, best_solution);

	// Update pheromone by F = 1 / dist
	for (unsigned node = 0; node < best_solution->size(); node++) {
		(*matrix)[node][node + 1].pheromone += cost;

		// MMAS modification
		if ((*matrix)[node][node + 1].pheromone > Setting::TAU_MAX)
			(*matrix)[node][node + 1].pheromone = Setting::TAU_MAX;
	}
}

void evaporate_pheromones(Matrix *matrix)
{
	for (auto &row : *matrix)
		for (Edge &edge : row)
			if (edge.dist > 0) {
				edge.pheromone *= (1 - Setting::EVAPORATION_RATE);

				// MMAS modification
				if (edge.pheromone < Setting::TAU_MIN)
					edge.pheromone = Setting::TAU_MIN;
			}
}
