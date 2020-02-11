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

Solution iterative_local_search();
	
void run_experiments(std::string instance,std::string solution);
#endif
