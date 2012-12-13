//---------------------------------------------------------------------------
#pragma hdrstop

#include "ThreadSolver.h"
#include <stdio.h>
#include <iostream>

ThreadSolver::ThreadSolver(vector<QuadEquation> * resultVec, char * * coeff, int numEquations, boost::mutex * vecMutex){
	this->_resultVec = resultVec;
	this->_coeff = coeff;
	this->_numEquations = numEquations;
	this->_vecMutex = vecMutex;
	this->_thread = NULL;
}

void ThreadSolver::solveAll(){
	for (int i = 0; i < this->_numEquations; i++){

		QuadEquation eq(&this->_coeff[i*3]);

		boost::mutex::scoped_lock * scoped_lock;

		if (this->_vecMutex!=NULL) {
			scoped_lock = new boost::mutex::scoped_lock(*(this->_vecMutex));
		}

//		eq.printAnswer(); //if answer printing needed
		this->_resultVec->push_back(eq);

		if (this->_vecMutex!=NULL) {
			delete scoped_lock;
		}
	}
}

void ThreadSolver::threadSolveAll(){
	this->_thread = new boost::thread(&ThreadSolver::solveAll, this);
}

void ThreadSolver::join(){
	if (this->_thread!=NULL) {
		this->_thread->join();
		delete this->_thread;
		this->_thread = NULL;
	}
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
