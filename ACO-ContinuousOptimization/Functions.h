#define _USE_MATH_DEFINES

#include <vector>

using namespace std;


typedef double(*func)(vector<double> & x);

double gaussian_random(double mue, double sigma);
double sqr(double x);

double Sphere_function(vector<double> & S);
double Ackley_function(vector<double> & S);
double Griewank_function(vector<double> & S);
double Rastrigin_function(vector<double> & S);
double Rosenbrock_function(vector<double> & S);