//---------------------------------------------------------------------------

#ifndef QuadEquationH
#define QuadEquationH

class QuadEquation{
	protected:
		float _a, _b, _c;
		float _x1, _x2;
		int _numRoots;

		bool _autoSolve;
		bool _error;
		bool _anyRoot;

		bool strToFloat_bool(const char *str, float & f);
		//converts char* to float. Returns false if there is an error

		void doOnModify();
		//solves the equation if _autosolve==true

		bool _solved;
	public:
		QuadEquation(bool autoSolve = true);
		QuadEquation(float a, float b, float c, bool autoSolve = true);
		QuadEquation(char * * coefficients, bool autoSolve = true);

		void solve();

		void setCoefficients(float a=0, float b=0, float c=0);
		void setA(float value);
		void setB(float value);
		void setC(float value);

		float getA();
		float getB();
		float getC();

		bool isError();
		bool getAutoSolve();
		void setAutoSolve(bool value);

		bool isAnyRoot();

		int getNumRoots();
		float getRoot1();
		float getRoot2();

		void printAnswer();

		bool isSolved();
};



//---------------------------------------------------------------------------
#endif
