#ifndef _EXPERIMENTS_H_
#define _EXPERIMENTS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setprecision


struct Dados {
	std::vector<double> custos;
	std::vector<double> tempos;
	std::string instance;
	int tamanho;
	double optimal_cost;
};

double calcVariancia ( std::vector<double> valores, double media);

double calcDistanciamento ( int valor, int referencia );

template <typename T>
T calcMedia ( std::vector<T> valores )
{
	T media = (T) 0;
	for (unsigned int i=0; i < valores.size(); i++)
		media += valores[i];
	return media/valores.size();
}

void calcEstatisticas ( Dados dados );


#endif