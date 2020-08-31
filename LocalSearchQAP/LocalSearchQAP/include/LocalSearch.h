#ifndef LocalSearch_H_
#define LocalSearch_H_

#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random> 
#include <string>
#include <algorithm>
#include <cstdlib>
#include <bits/stdc++.h>  //clock ,clock_t, CLOCKS_PER_SEC
#include "qap.h"
#include "Solution.h"
#include "experiments.h"
#include "latex.h"

void read_instance(std::string instance,std::string solution );

//int* first_solution(int* cur_solution);

void best_neighbor(Solution &cur_solution);

Solution local_search();

Solution local_search_aux( Solution start_solution[] );

// double* pertubation(double cur_solution[],double k);
Solution path_relinking();

Solution iterative_local_search();
Solution ils_path_relinking();
Solution ils_path_relinking_forward();
Solution ils_path_relinking_backward();
Solution ils_path_relinking_forward(int);
Solution ils_path_relinking_backward(int);
Solution ils_path_relinking_forward(Solution,Solution, int x);
Solution ils_path_relinking_backward(Solution,Solution,int x );
Solution ils_path_relinking_back_and_forward();

std::vector<int> hamming_distance(Solution ini , Solution guide);
void move(Solution& ini, Solution& guide, std::vector<int>& Moves);


	
void run_experiments(std::string instance,std::string solution);
#endif
