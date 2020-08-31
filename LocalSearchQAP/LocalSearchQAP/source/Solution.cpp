#include "../include/Solution.h"

using namespace std;

Solution::Solution(int n,int**flow,int**dist){
	this->n = n;
	this->dist = dist;
	this->flow = flow;

	this->solution.reserve(n);

	
}

Solution::Solution(int n, int** flow, int** dist,int* solution){
	this->n = n;
	this->dist = dist;
	this->flow = flow;

	this->solution.reserve(n);
	
	this->solution.insert(this->solution.begin(),solution,solution+n);

	
	double cost = 0;
	

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++){
			//cout << i << "-" << j << endl;

			cost += flow[this->solution[i]-1][this->solution[j]-1] * dist[i][j];
		
		}
	}
	
	this->cost = cost;

}

Solution::Solution(int n, int** flow, int** dist,vector<int> solution){
	this->n = n;
	this->dist = dist;
	this->flow = flow;

	this->solution.reserve(n);
	
	this->solution = solution;
	
	double cost = 0;
	

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++){

			cost += flow[this->solution[i]-1][this->solution[j]-1] * dist[i][j];
		
		}
	}
	
	this->cost = cost;

}
// Criação da primeira solução com a randomização do vetor dado pela instância

void Solution::first_solution(){

	//std::srand ( unsigned ( std::time(0) ) );
	shuffle(this->solution.begin(),this->solution.end(),std::default_random_engine(seed));
	double cost = 0;
	

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++){

			cost += this->flow[this->solution[i]-1][this->solution[j]-1] * this->dist[i][j];
		
		}
	}
	
	this->cost = cost;
}

Solution::~Solution(){
}

int Solution::get_Size(){
	return this->n;
}

vector<int> Solution::get_solution(){
	return this->solution;
}

int** Solution::get_matrix_of_flows(){
	return this->flow;
}

int** Solution::get_matrix_of_distances(){
	return this->dist;
}

double Solution::get_cost(){
	return this->cost;
}

void Solution::set_cost(double new_cost){
	this->cost = new_cost;
}

void Solution::set_solution(int* new_solution){
	std::vector<int> aux;
	aux.insert(this->solution.begin(),new_solution,new_solution+n);


	this->solution = aux;
}

void Solution::operator= (Solution b){
	
	this->solution = b.get_solution();

	this->cost = b.cost;
}

bool Solution::operator >(Solution b){
	if(get_cost() > b.get_cost()){
		return true;
	}
	return false;
}

bool Solution::operator <(Solution b){
	if(get_cost() < b.get_cost()){
		return true;
	}
	return false;
}

bool Solution::operator ==( Solution b){
	for(int i = 0 ; i < n ; i++){
		if( this->solution[i] != b[i]){
			return false;
		}
	}

	return true;
}

bool Solution::operator !=( Solution b){
	for(int i = 0 ; i < n ; i++){
		if( this->solution[i] != b[i]){
			return true;
		}
	}

	return false;
}

int& Solution::operator[](int index){
	return this->solution[index];
}

void Solution::swap_solution(int &a,int &b){
	int temp = a;
	a = b;
	b = temp;

	int cost = 0;

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++){

			cost += this->flow[this->solution[i]-1][this->solution[j]-1] * this->dist[i][j];
		
		}
	}
	
	this->cost = cost;
}

void Solution::pertubation(int k){	

	std::mt19937 mt(seed);
	std::uniform_int_distribution<int> linear_dis(0,get_Size()-k);
	int init = linear_dis(mt);

	std::random_shuffle(this->solution.begin()+init, this->solution.begin()+init+k);
}

void Solution::print_solution(){
	for (auto i = this->solution.begin(); i < this->solution.end(); ++i)
	{
		std::cout << *i << " ";
	}
}


