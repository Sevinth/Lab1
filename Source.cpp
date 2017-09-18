#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <fstream>

#include <omp.h>

void sumFunc(double*, int);
void piFunc(double*,int);
void bothFunctions(double*, int);

auto timing = [](auto&& F, auto&& ... params) {
	auto start = std::chrono::steady_clock::now();
	F(std::forward<decltype(params)>(params)...);
	return std::chrono::duration_cast<std::chrono::nanoseconds>(
		std::chrono::steady_clock::now() - start).count();
};

int main() {

	int N = 1;
	double *a = NULL;
	
	std::ofstream BothFunctionsFile;
	std::ofstream SumFunctionFile;
	std::ofstream AFunctionFile;
	

	double A = 0; 
	int numTrials = 50;

	BothFunctionsFile.open("BothFunctions_Timing.txt");
	for (int i = 0; i < numTrials; i++) {
	
		a = new double[N];
		auto seconds = timing(bothFunctions, a, N);
		//double seconds = 0;
		BothFunctionsFile << N << " " << seconds << std::endl;
		delete a;
		N = N + 1;

	}
	BothFunctionsFile.close();
	N = 1;

	SumFunctionFile.open("SumFunction_Timing.txt");
	for (int i = 0; i < 10; i++) {

		a = new double[N];

		piFunc(a, N);

		auto seconds = timing(sumFunc, a, N);
		//double seconds = 0;
		SumFunctionFile << N << " " << seconds << std::endl;
		delete a;
		N = pow(2,i+1);

	}
	SumFunctionFile.close();
	N = 1;

	AFunctionFile.open("PiFunction_Timing.txt");
	for (int i = 0; i < numTrials; i++) {
	
		a = new double[N];
		auto seconds = timing(piFunc, a, N);
		//double seconds = 0;
		AFunctionFile << N << " " << seconds << std::endl;
		delete a;
		N = N + 1;

	}
	N = 0;
	AFunctionFile.close();


	system("PAUSE");
}


void bothFunctions(double *a, int N) {
	piFunc(a, N);
	sumFunc(a, N);
}

void sumFunc(double *a, int N) {
	double res = 0;

	for (int i = 0; i < N; i++) {
		res += a[i];
		}

//std::cout << "Result: " << res << std::endl;
}


void piFunc(double *a, int N) {
	
	for (int i = 0; i < N; i++) {
		a[i] = pow(-1.0, (i+1) + 1.0) / (2.0 * (i+1) - 1);
	}

}

