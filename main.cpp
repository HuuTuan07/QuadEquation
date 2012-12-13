#pragma hdrstop
#pragma argsused

#include <stdio.h>
#include <iostream>
#include <vector>
#include <boost/thread/mutex.hpp>
#include <math.h>

#include "QuadEquation.h"
#include "ThreadSolver.h"

using namespace std;

int main(int argc, char * argv[]){
	int N = (argc-1)/3; //Number of equations
	if ((argc-1)%3 != 0) {
		cout << "There are excess strings in argv[]" << endl;
	}
	if (N==0) {
		cout << "No equations" << endl;
	}

    //Number of processor cores
	//max(...,1) because hardware_concurrency can return 0 in some operation systems
	int numCores = max<int>(boost::thread::hardware_concurrency(),1);

	int numThreads =0; //Number of threads
	if (numCores>=N) {
		numThreads = N;
	}else{
		numThreads = numCores;
	}

	int * eqsPerThread; //number of equations for each thread
	eqsPerThread = new int[numThreads];
	for (int i = 0; i < numThreads; i++) {
		eqsPerThread[i] = N/numThreads;
		if (i<N%numThreads)
			eqsPerThread[i]++;
	}

	cout << "Number of equations: " << N << endl;
	cout << "Number of cores: " << numCores << endl;
	cout << "Number of threads: " << numThreads << endl;

	vector<QuadEquation> eqVector(N); //vector of equations
	eqVector.clear();


	ThreadSolver * * threadArr; //array of ThreadSolvers
	threadArr = new ThreadSolver * [numThreads];


	boost::mutex vecMutex; //mutex for safe push_back in eqVector

	//start threads
	int coeffOffset = 1;
	for (int i = 0; i < numThreads; i++) {
		threadArr[i] = new ThreadSolver(
				&eqVector, //pointer to the equation vector
				&(argv[coeffOffset]), //pointer to array of coefficients of equations
				eqsPerThread[i], // number of equations per thread
				&vecMutex); //pointer to mutex
		coeffOffset+=eqsPerThread[i]*3;
		threadArr[i]->threadSolveAll();
	}
	delete [] eqsPerThread;


	//wait for finishing threads
	for (int i = 0; i < numThreads; i++) {
		threadArr[i]->join();
		delete threadArr[i];
	}

	delete [] threadArr;

	//result printing
	cout << endl;
	vector<QuadEquation>::iterator iter = eqVector.begin();
	while (iter != eqVector.end()){
		iter->printAnswer();
		cout << endl;
		iter++;
	}

	cin.get();
	return 0;
}
