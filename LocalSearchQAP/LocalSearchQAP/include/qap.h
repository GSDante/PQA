#ifndef _QAP_H_
#define _QAP_H_

#include <iostream>
#include <vector>
#include "Solution.h"

using namespace std;
class QAP
{
private:
	int n;

	int** flow;
	int** dist;

	int* solution;

	Solution best_solution;

public:
	QAP(int n, int** d_mat, int** f_mat);
	QAP(int n, int** d_mat, int** f_mat,Solution best_solution);

	QAP();

	int get_number_of_facilities();

	int** get_matrix_of_flows();

	int** get_matrix_of_distances();

	vector<int> get_best_solution();

	void set_best_solution(Solution new_best_solution);

	int get_best_cost();

	void print_solution();


	
};

#endif