#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>

using namespace std;

class Solution
{
private:
	int n;
	int cost;
	vector<int> solution ;
	int ** flow; 
	int ** dist;

public:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	//Construtor que já tem o cálculo do custo da solução
	Solution(){};
	Solution(int n,int**flow,int**dist);
	Solution(int n,int **flow,int**dist,int *solution);
	Solution(int n, int** flow, int** dist,vector<int> solution);
	~Solution();
	
	//Sobrecarga dos operadores ">" e "<"
	bool operator >(Solution b);
	bool operator <(Solution b);
	void operator= (Solution b);
	int& operator[](int index);
	

	//Getters e Setters
	int get_Size();

	vector<int> get_solution();

	int** get_matrix_of_flows();

	int** get_matrix_of_distances();

	int get_cost();

	void set_cost(int new_cost);

	void set_solution(int* new_solution);

	void swap_solution(int &a, int &b);

	void pertubation(int k);

	void print_solution();

	void first_solution();	


};
#endif
