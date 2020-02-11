#include "../include/LocalSearch.h"
#include <cstdio>
#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: qap Instance Solution [outputFile] [timeLimit]" << std::endl;
		return 1;
	}

	const char* instanceFile = argv[1];
	const char* solutionFile = argv[2];

	run_experiments(instanceFile,solutionFile);
	criar_tabelas_latex();

	return 0;
}