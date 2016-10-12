#include <iostream>
#include <vector>
#include <deque>		// roulette

using namespace std;

namespace Setting {
	extern string FILENAME;						// Set in Main.cpp
	const int ANTS_NUM = 100;
	const int STEPS = 500;
	const double INIT_PHEROMONES = 1.0;	
	const double ALPHA = 1.0, BETA = 2.0;		// Alpha- depend on pheromone, Beta- on dist
	const double EVAPORATION_RATE = 0.005;		// 1 - forget fast;  0 - remember all
	const double TAU_MIN = 1.0, TAU_MAX = 5.0;	// MMAS modification
}


struct Edge
{
	int dist;
	double pheromone;
};

struct Ant
{
	int position;
	vector<int> way;
};

typedef vector<int> Solution;
typedef vector<vector<Edge>> Matrix;



void read_file(Matrix *matrix);

/* counts probability of transfering from i to j node */
double count_probability(Matrix *matrix, Ant *ant, int i, int j);

/* counts value F(s_best) where s_best is best solution */
double count_cost(Matrix *matrix, Solution *way);

/* roulette random choosing from vector of elements: 0..1 */
int random_roulette_ind(deque<double> *roulette);

/* update nodes from best_solution way */
void update_pheromones(Matrix *matrix, Solution *best_solution);

/* Each iteration pheromones evaporate */
void evaporate_pheromones(Matrix *matrix);