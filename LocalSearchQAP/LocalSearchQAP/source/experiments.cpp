#include "../include/experiments.h"
#include <cmath>

using namespace std;

double calcVariancia ( std::vector<double> valores, double media )
{
	double var = 0;
	for (unsigned int i=0; i < valores.size(); i++)
		var += pow((valores[i]-media),2);
	return var/(valores.size()-1);
}

double calcDistanciamento ( double valor, double referencia )
{
	return ( (fabs(valor-referencia)*100)/referencia );
}

void calcEstatisticas ( Dados dados )
{
	std::sort(dados.custos.begin(), dados.custos.end());
	int size_cost = dados.custos.size();
	std::vector<double> distanciamentos;
	
	double mediana = 0;
	int solucoes_otimas_encontrada = 0;

	for (unsigned int i=0; i < dados.custos.size(); i++)
		if (dados.custos[i] == dados.optimal_cost) 
			solucoes_otimas_encontrada+=1;

	for(unsigned int i = 0; i < dados.custos.size(); i++){
		distanciamentos.push_back(calcDistanciamento(dados.custos[i],dados.optimal_cost));
		std::cout << distanciamentos[i] << "\n";
	}

	double min_distanciamento = 0;
	double max_distanciamento = 0;
	double media_distanciamento = 0;


	for(unsigned int i = 0; i < distanciamentos.size();i++){
		if(min_distanciamento >= distanciamentos[i]){
			min_distanciamento = distanciamentos[i];
		}

		if(max_distanciamento <= distanciamentos[i]){
			max_distanciamento = distanciamentos[i];
		}

		media_distanciamento += distanciamentos[i];
	}

	media_distanciamento = media_distanciamento/distanciamentos.size();

	double percentual_optimal_solutions_found = (solucoes_otimas_encontrada*100.00)/dados.custos.size(); 
	if ( size_cost%2 != 0)
	{
		mediana = distanciamentos[(distanciamentos.size()/2) - 1] + distanciamentos[distanciamentos.size()/2];
		mediana /= 2;
	} else mediana = distanciamentos[distanciamentos.size()/2];

	double media_tempo = calcMedia<double>(dados.tempos);
	double dp_custo = sqrt(calcVariancia(distanciamentos, media_distanciamento));

	std::ofstream out("archives/resultExecution.txt", std::ofstream::app);
	if (!out.is_open()) std::cout << "\nNão abriu o arquivo!\n";

	std::ofstream latex("archives/in_latex.dat", std::ofstream::app);
	if (!latex.is_open()) std::cout << "\nNão abriu o arquivo!\n";


	out << dados.instance << "\n";
	out << "REPORT\n--------------------------------------------------\n";
	out << "Average elapsed time: " << media_tempo << " ms" << std::endl;
	out << "Percentual of optimal solutions found: " << percentual_optimal_solutions_found << "%" << std::endl;
	out << "Min found cost: " << min_distanciamento << "%" << std::endl;
	out << "Max found cost: " << max_distanciamento << "%" << std::endl;
	out << "Average found cost: " << media_distanciamento << "%" << std::endl; 
	out << "Median: " << calcDistanciamento(mediana, dados.optimal_cost) << "%" << std::endl;
	out << "Standard deviation of cost: " << dp_custo << std::endl;
	out << "Median :" << mediana << std::endl;
	out << "Best Cost Known :" << mediana << std::endl;

	out << "--------------------------------------------------\n";
	out.close();

	latex << "\n" << dados.instance << "\n";
	latex << media_tempo << std::endl;
	latex << std::fixed << std::setprecision(2) << percentual_optimal_solutions_found << std::endl;
	latex << std::setprecision(2) << min_distanciamento << std::endl;
	latex << std::setprecision(2) << max_distanciamento << std::endl;
	latex << std::setprecision(2) << media_distanciamento << std::endl; 
	latex << std::setprecision(2) << dp_custo << std::endl;
	latex << mediana << std::endl;
	latex << dados.optimal_cost;
	latex.close();

}