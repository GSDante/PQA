#include "../include/qap.h"


QAP::QAP(int n, int** dist, int** flow)
{
	this->n = n;
	this->dist = dist;
	this->flow = flow;
}

QAP::QAP(int n, int** dist, int** flow, Solution solution)
{
	this->n = n;
	this->dist = dist;
	this->flow = flow;
	this->best_solution = solution;
}


int QAP::get_number_of_facilities()
{
	return this->n;
}

int** QAP::get_matrix_of_flows()
{
	return this->flow;
}

int** QAP::get_matrix_of_distances()
{
	return this->dist;
}

vector<int> QAP::get_best_solution()
{
	return this->best_solution.get_solution();
}

void QAP::set_best_solution(Solution new_best_solution)
{
	this->best_solution = new_best_solution;
}

int QAP::get_best_cost()
{
	return this->best_solution.get_cost();
}

void QAP::print_solution(){
	this->best_solution.print_solution();
}



