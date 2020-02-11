#include "../include/LocalSearch.h"

using namespace std;

int** dist;
int** flow;
int n;
int * opt;


int known_solutions;

//Leitor de instância que alocar em um vetor de fluxo e outro de distancias

void read_instance(std::string instance,std::string solution )
{

	std::ifstream file;
	std::ifstream sol;

	file.open(instance.c_str());

	file >> n;

	dist = new int*[n];
	flow = new int*[n];
	for(int i = 0; i < n; ++i)
	{
		dist[i] = new int[n];
		flow[i] = new int[n];
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			file >> dist[i][j];
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			file >> flow[i][j];
		}
	}

	sol.open(solution.c_str());
	sol >> n;
	sol >> known_solutions;

	opt = new int[n];

	for(int i = 0 ;i < n ; ++i)
	{
		sol >> opt[i];

	}

	

}


// Utilização da estrategia 2swap para permutar os vetores e gerar a vizinhança
void best_neighbor(Solution &cur_solution) //passar solucao por copia eh muito custoso... passar por referencia const; nao usar cur_solution para guardar o retorno da funcao...
{

	//Apenas para repassar o vetor solução pro vizinho
	vector<int> aux = cur_solution.get_solution();

	Solution neighbor(n,flow,dist,aux);
	neighbor.swap_solution(neighbor[0],neighbor[1]);

	
	int best_cost = neighbor.get_cost(); 
	neighbor.swap_solution(neighbor[0],neighbor[1]);	

	for(int i = 0; i < n-1; i++)
	{
		for (int j = i+1; j < n; ++j)
		{
			neighbor.swap_solution(neighbor[i],neighbor[j]);

			if(neighbor.get_cost() < best_cost)
			{
				cur_solution = neighbor;
				best_cost = neighbor.get_cost();
			}
			neighbor.swap_solution(neighbor[i],neighbor[j]);
		}
	}
}

Solution local_search()
{
	
 	Solution best_solution(n,flow,dist,opt);
 	best_solution.first_solution();
	
 	Solution cur_solution(n,flow,dist,opt);
 	cur_solution = best_solution;

  	bool improve = true;

 	Solution candidate(n,flow,dist,opt);
 	candidate = cur_solution;
 	best_neighbor(candidate);

 	while(improve)
 	{
 		if (candidate < best_solution)
 		{
			best_solution = candidate;

 			cur_solution = candidate;

		}else if(candidate < cur_solution && candidate > best_solution)
 		{
 			cur_solution = candidate;
 		}
 		else
 		{
 			improve = false;
 		}
		candidate = cur_solution;
 		best_neighbor(candidate);
	}

 	QAP problem(n,dist,flow,best_solution);

 	return best_solution;
}

//Função de busca local para a busca local iterativa 
Solution local_search_aux( Solution cur_solution)
{
	
 	Solution best_solution(n,flow,dist,opt);
 	best_solution.first_solution();

	

  	bool improve = true;

 	Solution candidate(n,flow,dist,opt);
 	candidate = cur_solution;
 	best_neighbor(candidate);



 	while(improve)
 	{
 		if (candidate < best_solution)
 		{
			best_solution = candidate;

 			cur_solution = candidate;

		}else if(candidate < cur_solution && candidate > best_solution)
 		{

 			cur_solution = candidate;
 		}
 		else
 		{

 			improve = false;
 		}
		candidate = cur_solution;
 		best_neighbor(candidate);
	}


	return best_solution;


}

//Busca local iterativa 

Solution iterative_local_search()
{

 	Solution start_solution(n,flow,dist,opt);
 	start_solution.first_solution();
	
	Solution ls_solution(n,flow,dist,opt); 
	ls_solution = local_search_aux(start_solution);

	Solution best_solution(n,flow,dist); 
	best_solution = ls_solution;
	
	int k = 1;

 	QAP problem(n,dist,flow);
	//Utiliza-se a busca local ,sendo que a iteração avança em caso de não haver mais solução melhor do que a outra


	Solution candidate(n,flow,dist); 
	candidate = ls_solution;
	
	Solution ls_candidate(n,flow,dist); 
	ls_candidate = local_search_aux(candidate);

	while(k < n)
	{
		
		if (ls_candidate < best_solution)
		{
			best_solution = ls_candidate;

		} else{

			k++;

		}
		candidate.pertubation(k);

		ls_candidate = local_search_aux(candidate);

	}

	problem.set_best_solution(best_solution);

	return best_solution;
	
}

void run_experiments(string instance,string solution){

	read_instance(instance,solution);

	vector<int>custos_ls;
	vector<double>tempos_ls;
	std::clock_t start, end;

	double count_ls = 0;

	for(int i = 0 ; i <= 30 ; i++){
		Solution solution(n,flow,dist,opt);

		start = clock();
		solution = local_search();
		end = clock();

		count_ls = double(end - start)/ double(CLOCKS_PER_SEC);
		tempos_ls.push_back(count_ls);
		custos_ls.push_back(solution.get_cost());
	}
	
	vector<int>custos_ils;
	vector<double>tempos_ils;

	double count_ils = 0;	

	for(int i = 0 ; i <= 30 ; i++){
		Solution solution(n,flow,dist,opt);

		start = clock();
		solution = iterative_local_search();
		end = clock();

		count_ils = double(end - start)/ double(CLOCKS_PER_SEC);
		tempos_ils.push_back(count_ils);
		custos_ils.push_back(solution.get_cost());
	}

	Solution opt_sol(n,flow,dist,opt);

	int opt_cost= opt_sol.get_cost();

	Dados dados_ls = {custos_ls, tempos_ls, instance, n, opt_cost}; 
	Dados dados_ils = {custos_ils, tempos_ils, instance, n, opt_cost}; 

	calcEstatisticas(dados_ls);
	calcEstatisticas(dados_ils);

	for(int i = 0; i < n; ++i)
	{
		delete[] dist[i];
		delete[] flow[i];
	}

	delete[] dist;
	delete[] flow;
	delete[] opt;
}


