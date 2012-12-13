//---------------------------------------------------------------------------

#ifndef ThreadSolverH
#define ThreadSolverH

#include "QuadEquation.h"
#include <vector>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

using namespace std;

class ThreadSolver{
	protected:
		vector<QuadEquation> * _resultVec;
		char * * _coeff;
		int _numEquations;
		boost::mutex * _vecMutex;
		boost::thread * _thread;
		void solveAll(); //solve equations
	public:
		//resultVec - pointer to the vector to write solved equations
		//coeff - pointer to an array of strings with coefficients of equations
		//numEquations - number of equations
		//mutex to safety write in resultVec
		ThreadSolver(vector<QuadEquation> * resultVec, char * * coeff, int numEquations, boost::mutex * vecMutex = NULL);

		void threadSolveAll();//create _thread and GO
		void join();//join and delete _thread
	protected:
//		ThreadSolver();
};

//---------------------------------------------------------------------------
#endif
