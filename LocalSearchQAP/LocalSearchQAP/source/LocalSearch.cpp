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
 	cur_solution.first_solution();

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

Solution path_relinking(){
	
	Solution start_solution(n,flow,dist,opt);
 	start_solution.first_solution();

 	Solution last_solution(n,flow,dist,opt);
 	last_solution.first_solution();

 	//Assumindo que o melhor por enquanto é a primeira solução
 	Solution best_solution(n,flow,dist,opt);
 	best_solution = start_solution;

 	// Candidato que ira representar o vizinho da solução
  	Solution candidate(n,flow,dist,opt);
  	candidate = start_solution;

 	for (int i = 0; i < n; ++i)
 	{
 		if(candidate[i] != last_solution[i])
 		{
 			//Varrendo o vetor a partir do valor diferente entre a start e last, caso ache, ocorre a troca
 			for (int j = i; j < n; ++j)
 			{
 				if(candidate[j] == last_solution[i]){
 					candidate.swap_solution(candidate[i],candidate[j]);
 				}
 			}
 			if( best_solution > candidate){
 				best_solution = candidate;
 			}
 		}
 	}

 	// Ultimo dos vizinho sendo testado
 	if (best_solution > last_solution)
 	{
 		best_solution = last_solution;
 	}

 	return best_solution;
}

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

Solution ils_path_relinking(){
	Solution start_solution = iterative_local_search();
 	Solution last_solution = iterative_local_search();

 	//Assumindo que o melhor por enquanto é a primeira solução
 	Solution best_solution(n,flow,dist,opt);
 	best_solution = start_solution;

 	// Candidato que ira representar o vizinho da solução
  	Solution candidate(n,flow,dist,opt);
  	candidate = start_solution;

 	for (int i = 0; i < n; ++i)
 	{
 		if(candidate[i] != last_solution[i])
 		{
 			//Varrendo o vetor a partir do valor diferente entre a start e last, caso ache, ocorre a troca
 			for (int j = i; j < n; ++j)
 			{
 				if(candidate[j] == last_solution[i]){
 					candidate.swap_solution(candidate[i],candidate[j]);
 				}
 			}
 			if( best_solution > candidate){
 				best_solution = candidate;
 			}
 		}
 	}

 	// Ultimo dos vizinho sendo testado
 	if (best_solution > last_solution)
 	{
 		best_solution = last_solution;
 	}

 	return best_solution;
}

Solution ils_path_relinking_forward(){
	Solution start_solution = iterative_local_search();
 	Solution last_solution = iterative_local_search();

 	Solution ini(n,flow,dist,opt);
 	Solution guide(n,flow,dist,opt);

 	if (start_solution < last_solution)
 	{
 		ini = last_solution;
 		guide = start_solution;
 	}else{
 		ini = start_solution;
 		guide = last_solution;
 	}

 	//Assumindo que o melhor por enquanto é a primeira solução
 	Solution best_solution(n,flow,dist,opt);
 	best_solution = ini;

 	// Candidato que ira representar o vizinho da solução
  	Solution candidate(n,flow,dist,opt);
  	candidate = ini;

 	for (int i = 0; i < n; ++i)
 	{
 		if(candidate[i] != guide[i])
 		{
 			//Varrendo o vetor a partir do valor diferente entre a start e last, caso ache, ocorre a troca
 			for (int j = i; j < n; ++j)
 			{
 				if(candidate[j] == guide[i]){
 					candidate.swap_solution(candidate[i],candidate[j]);
 				}
 			}
 			if( best_solution > candidate){
 				best_solution = candidate;
 			}
 		}
 	}

 	// Ultimo dos vizinho sendo testado
 	if (best_solution > guide)
 	{
 		best_solution = guide;
 	}

 	return best_solution;
}

Solution ils_path_relinking_backward(){
	Solution start_solution = iterative_local_search();
 	Solution last_solution = iterative_local_search();

 	Solution ini(n,flow,dist,opt);
 	Solution guide(n,flow,dist,opt);

 	if (start_solution < last_solution)
 	{
 		ini = start_solution;
 		guide = last_solution;
 	}else{
 		ini = last_solution;
 		guide = start_solution;
 	}

 	//Assumindo que o melhor por enquanto é a primeira solução
 	Solution best_solution(n,flow,dist,opt);
 	best_solution = ini;

 	// Candidato que ira representar o vizinho da solução
  	Solution candidate(n,flow,dist,opt);
  	candidate = ini;

 	for (int i = 0; i < n; ++i)
 	{
 		if(candidate[i] != guide[i])
 		{
 			//Varrendo o vetor a partir do valor diferente entre a start e last, caso ache, ocorre a troca
 			for (int j = i; j < n; ++j)
 			{
 				if(candidate[j] == guide[i]){
 					candidate.swap_solution(candidate[i],candidate[j]);
 				}
 			}
 			if( best_solution > candidate){
 				best_solution = candidate;
 			}
 		}
 	}

 	// Ultimo dos vizinho sendo testado
 	if (best_solution > guide)
 	{
 		best_solution = guide;
 	}

 	return best_solution;
}

Solution ils_path_relinking_forward(int x){
	Solution start_solution = iterative_local_search();
 	Solution last_solution = iterative_local_search();

 	Solution ini(n,flow,dist,opt);
 	Solution guide(n,flow,dist,opt);

 	if (start_solution < last_solution)
 	{
 		ini = last_solution;
 		guide = start_solution;
 	}else{
 		ini = start_solution;
 		guide = last_solution;
 	}

 	//Assumindo que o melhor por enquanto é a primeira solução
 	Solution best_solution(n,flow,dist,opt);
 	best_solution = ini;

 	// Candidato que ira representar o vizinho da solução
  	Solution candidate(n,flow,dist,opt);
  	candidate = ini;

 	for (int i = 0; i < n*x; ++i)
 	{
 		if(candidate[i] != guide[i])
 		{
 			//Varrendo o vetor a partir do valor diferente entre a start e last, caso ache, ocorre a troca
 			for (int j = i; j < n; ++j)
 			{
 				if(candidate[j] == guide[i]){
 					candidate.swap_solution(candidate[i],candidate[j]);
 				}
 			}
 			if( best_solution > candidate){
 				best_solution = candidate;
 			}
 		}
 	}

 	// Ultimo dos vizinho sendo testado
 	if (best_solution > guide)
 	{
 		best_solution = guide;
 	}

 	return best_solution;
}

Solution ils_path_relinking_backward(int x){
	Solution start_solution = iterative_local_search();
 	Solution last_solution = iterative_local_search();

 	Solution ini(n,flow,dist,opt);
 	Solution guide(n,flow,dist,opt);

 	if (start_solution < last_solution)
 	{
 		ini = start_solution;
 		guide = last_solution;
 	}else{
 		ini = last_solution;
 		guide = start_solution;
 	}

 	//Assumindo que o melhor por enquanto é a primeira solução
 	Solution best_solution(n,flow,dist,opt);
 	best_solution = ini;

 	// Candidato que ira representar o vizinho da solução
  	Solution candidate(n,flow,dist,opt);
  	candidate = ini;

 	for (int i = 0; i < n*x; ++i)
 	{
 		if(candidate[i] != guide[i])
 		{
 			//Varrendo o vetor a partir do valor diferente entre a start e last, caso ache, ocorre a troca
 			for (int j = i; j < n; ++j)
 			{
 				if(candidate[j] == guide[i]){
 					candidate.swap_solution(candidate[i],candidate[j]);
 				}
 			}
 			if( best_solution > candidate){
 				best_solution = candidate;
 			}
 		}
 	}

 	// Ultimo dos vizinho sendo testado
 	if (best_solution > guide)
 	{
 		best_solution = guide;
 	}

 	return best_solution;
}

Solution ils_path_relinking_forward(Solution start_solution, Solution last_solution){

 	Solution ini(n,flow,dist,opt);
 	Solution guide(n,flow,dist,opt);

 	if (start_solution < last_solution)
 	{
 		ini = last_solution;
 		guide = start_solution;
 	}else{
 		ini = start_solution;
 		guide = last_solution;
 	}

 	//Assumindo que o melhor por enquanto é a primeira solução
 	Solution best_solution(n,flow,dist,opt);
 	best_solution = ini;

 	// Candidato que ira representar o vizinho da solução
  	Solution candidate(n,flow,dist,opt);
  	candidate = ini;

 	for (int i = 0; i < n; ++i)
 	{
 		if(candidate[i] != guide[i])
 		{
 			//Varrendo o vetor a partir do valor diferente entre a start e last, caso ache, ocorre a troca
 			for (int j = i; j < n; ++j)
 			{
 				if(candidate[j] == guide[i]){
 					candidate.swap_solution(candidate[i],candidate[j]);
 				}
 			}
 			if( best_solution > candidate){
 				best_solution = candidate;
 			}
 		}
 	}

 	// Ultimo dos vizinho sendo testado
 	if (best_solution > guide)
 	{
 		best_solution = guide;
 	}

 	return best_solution;
}

Solution ils_path_relinking_backward(Solution start_solution, Solution last_solution){

 	Solution ini(n,flow,dist,opt);
 	Solution guide(n,flow,dist,opt);

 	if (start_solution < last_solution)
 	{
 		ini = start_solution;
 		guide = last_solution;
 	}else{
 		ini = last_solution;
 		guide = start_solution;
 	}

 	//Assumindo que o melhor por enquanto é a primeira solução
 	Solution best_solution(n,flow,dist,opt);
 	best_solution = ini;

 	// Candidato que ira representar o vizinho da solução
  	Solution candidate(n,flow,dist,opt);
  	candidate = ini;

 	for (int i = 0; i < n; ++i)
 	{
 		if(candidate[i] != guide[i])
 		{
 			//Varrendo o vetor a partir do valor diferente entre a start e last, caso ache, ocorre a troca
 			for (int j = i; j < n; ++j)
 			{
 				if(candidate[j] == guide[i]){
 					candidate.swap_solution(candidate[i],candidate[j]);
 				}
 			}
 			if( best_solution > candidate){
 				best_solution = candidate;
 			}
 		}
 	}

 	// Ultimo dos vizinho sendo testado
 	if (best_solution > guide)
 	{
 		best_solution = guide;
 	}

 	return best_solution;
}

Solution ils_path_relinking_back_and_forward(){
	Solution start_solution = iterative_local_search();
 	Solution last_solution = iterative_local_search();

 	Solution x_s = ils_path_relinking_backward(start_solution,last_solution);
 	Solution x_t = ils_path_relinking_forward(start_solution,last_solution);

 	if( x_t < x_s ){
 		return x_t;
 	}else{
 		return x_s;
 	}

 	return x_s;
}




//Calcula a distância simétrica, logo os movimentos serão guardados
std::vector<int> hamming_distance(Solution ini , Solution guide){

	std::vector<int> Moves;

	for (int i = 0 ; i < guide.get_Size() ; ++i)
	{
		if( ini[i] != guide[i])
		{
			Moves.push_back(i);
		}
	}

	return Moves;
}
//Aplica o movimento a partir da solução inicial e da guia
//E pega o primeiro movimento da lista 
void move(Solution& ini, Solution& guide, std::vector<int>& Moves){
	for (int i = Moves[0]; i < guide.get_Size(); ++i)
 			{
 				if(ini[Moves[0]] == guide[i]){
 					ini.swap_solution(ini[Moves[0]],guide[i]);
 				}
 			}
}

Solution ils_path_relinking_mixed(){
	Solution start_solution = iterative_local_search();
	Solution last_solution = iterative_local_search();

 	Solution best_solution(n,flow,dist,opt);
 	//Variavel auxiliar para alterar o sentido do caminho
	bool turn = true;
	std::vector<int> Moves = hamming_distance(start_solution,last_solution); 

	//Guarda a melhor solução
	if(start_solution < last_solution)
	{
		best_solution = start_solution;
	
	}else{
		
		best_solution = last_solution;
	
	}

	//Será feito até que acabe o número de movimentos,ou seja, quando start e last forem iguais
	while(Moves.size() > 0){

		if(turn){
			move(start_solution,last_solution,Moves);

			//Guarda a melhor solução até então
 			if( best_solution > start_solution){
 				best_solution = start_solution;
 			}

 			Moves.erase(Moves.begin());
 			turn = false;

		}else{
			move(last_solution,start_solution,Moves);

			if( best_solution > last_solution){
 				best_solution = last_solution;
 			}

 			Moves.erase(Moves.begin());
 			turn = true;

		}

	}

	return best_solution;

}

void run_experiments(string instance,string solution){

	read_instance(instance,solution);

	vector<double>custos;
	vector<double>tempos;
	std::clock_t start, end;
	double count = 0;
	int c;

	std::cout << " Escolha uma das tecnicas a ser utilizadas:\n";
	std::cout << " 1.Busca Local\n";
	std::cout << " 2.Busca Local iterativa\n";
	std::cout << " 3.Path Relinking + Busca Local Iterativa\n";
	std::cout << " 4.Path Relinking Forward + Busca Local Iterativa\n";
	std::cout << " 5.Path Relinking Backward + Busca Local Iterativa\n";
	std::cout << " 6.Path Relinking Back and Forward + Busca Local Iterativa\n";
	std::cout << " 7.Path Relinking Mixed + Busca Local Iterativa\n";
	std::cout << " 8.Path Relinking Forward Truncated + Busca Local Iterativa\n";
	std::cout << " 9.Path Relinking Backward Truncated + Busca Local Iterativa\n";


	
	std::cin >> c ;

	switch(c){
		case 1:
			for(int i = 0 ; i <= 30 ; i++){
	 			Solution solution(n,flow,dist,opt);

	 			start = clock();
	 			solution = local_search();
	 			end = clock();

	 			count = double(end - start)/ double(CLOCKS_PER_SEC);
	 			tempos.push_back(count);
	 			custos.push_back(solution.get_cost());
	 		}	
			break;
		case 2:
			for(int i = 0 ; i <= 30 ; i++){
		 		Solution solution(n,flow,dist,opt);

		 		start = clock();
		 		solution = iterative_local_search();
		 		end = clock();

		 		count = double(end - start)/ double(CLOCKS_PER_SEC);
	 			tempos.push_back(count);
	 			custos.push_back(solution.get_cost());
		 	}	
			break; 
		case 3:
			for(int i = 0 ; i <= 30 ; i++){
		 		Solution solution(n,flow,dist,opt);

		 		start = clock();
		 		solution = path_relinking();
		 		end = clock();

		 		count = double(end - start)/ double(CLOCKS_PER_SEC);
	 			tempos.push_back(count);
	 			custos.push_back(solution.get_cost());
		 	}	
			break; 
		case 4:
			for(int i = 0 ; i <= 30 ; i++){
		 		Solution solution(n,flow,dist,opt);

		 		start = clock();
		 		solution = ils_path_relinking_forward();
		 		end = clock();

		 		count = double(end - start)/ double(CLOCKS_PER_SEC);
	 			tempos.push_back(count);
	 			custos.push_back(solution.get_cost());
		 	}	
			break; 
		case 5:
			for(int i = 0 ; i <= 30 ; i++){
		 		Solution solution(n,flow,dist,opt);

		 		start = clock();
		 		solution = ils_path_relinking_backward();
		 		end = clock();

		 		count = double(end - start)/ double(CLOCKS_PER_SEC);
	 			tempos.push_back(count);
	 			custos.push_back(solution.get_cost());
	 			
		 	}	
			break;
		case 6:
			for(int i = 0 ; i <= 30 ; i++){
		 		Solution solution(n,flow,dist,opt);

		 		start = clock();
		 		solution = ils_path_relinking_back_and_forward();
		 		end = clock();

		 		count = double(end - start)/ double(CLOCKS_PER_SEC);
	 			tempos.push_back(count);
	 			custos.push_back(solution.get_cost());
		 	}	
			break;
		case 7:
			for(int i = 0 ; i <= 30 ; i++){
		 		Solution solution(n,flow,dist,opt);

		 		start = clock();
		 		solution = ils_path_relinking_mixed();
		 		end = clock();

		 		count = double(end - start)/ double(CLOCKS_PER_SEC);
	 			tempos.push_back(count);
	 			custos.push_back(solution.get_cost());
		 	}	
			break;
		case 8:
			for(int i = 0 ; i <= 30 ; i++){
		 		Solution solution(n,flow,dist,opt);

		 		start = clock();
		 		solution = ils_path_relinking_forward(0.6);
		 		end = clock();

		 		count = double(end - start)/ double(CLOCKS_PER_SEC);
	 			tempos.push_back(count);
	 			custos.push_back(solution.get_cost());
		 	}	
			break; 
		case 9:
			for(int i = 0 ; i <= 30 ; i++){
		 		Solution solution(n,flow,dist,opt);

		 		start = clock();
		 		solution = ils_path_relinking_backward(0.6);
		 		end = clock();

		 		count = double(end - start)/ double(CLOCKS_PER_SEC);
	 			tempos.push_back(count);
	 			custos.push_back(solution.get_cost());
		 	}	
			break;  
	}

	

	Solution opt_sol(n,flow,dist,opt);

	double opt_cost= opt_sol.get_cost();

	Dados dados = {custos, tempos, instance, n, opt_cost}; 

	calcEstatisticas(dados);

	for(int i = 0; i < n; ++i)
	{
		delete[] dist[i];
		delete[] flow[i];
	}

	delete[] dist;
	delete[] flow;
	delete[] opt;
}


