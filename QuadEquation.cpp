//---------------------------------------------------------------------------

#pragma hdrstop

#include "QuadEquation.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;


QuadEquation::QuadEquation(bool autoSolve):
	_a(0),
	_b(0),
	_c(0),
	_autoSolve(autoSolve),
	_solved(false)
{
	this->doOnModify();
}

QuadEquation::QuadEquation(float a, float b, float c, bool autoSolve):
	_a(a),
	_b(b),
	_c(c),
	_autoSolve(autoSolve),
	_solved(false),
	_error(false)
{
	this->doOnModify();
}

QuadEquation::QuadEquation(char * * coefficients, bool autoSolve):
	_autoSolve(autoSolve),
	_solved(false)
{
	bool noError = true;
	noError = noError && this->strToFloat_bool(coefficients[0],this->_a);
	noError = noError && this->strToFloat_bool(coefficients[1],this->_b);
	noError = noError && this->strToFloat_bool(coefficients[2],this->_c);
	this->_error = !noError;
	if (noError) {
		this->doOnModify();
	}
}

void QuadEquation::doOnModify(){
	if (this->_autoSolve) {
		this->solve();
	}
}

void QuadEquation::setCoefficients(float a, float b, float c){
	this->_solved = false;
	this->_a = a;
	this->_b = b;
	this->_c = c;
	this->doOnModify();
}

void QuadEquation::solve(){
	_anyRoot = false;
	_error = false;
	_solved = true;
	if (_a == 0.0) {
		if (_b == 0.0) {
			if (_c == 0.0) {
				_anyRoot = true;
			}else{
				_numRoots = 0;
			}
		}else{
			_numRoots = 1;
			_x1 = _x2 = _c/_b;
		}
	}else{
		float D = _b*_b - 4.0*_a*_c;
		if (D == 0.0) {
			_numRoots = 1;
			_x1 = _x2 = -_b/(2.0*_a);
		}else if(D > 0){
		   _numRoots = 2;
		   _x1 = (-_b + sqrt(D))/(2.0*_a);
		   _x2 = (-_b - sqrt(D))/(2.0*_a);
		}else{
		   _numRoots = 0;
		}
	}

}

void QuadEquation::setA(float value){
	this->_solved = false;
	this->_a = value;
	this->doOnModify();
}
void QuadEquation::setB(float value){
	this->_solved = false;
	this->_b = value;
	this->doOnModify();
}
void QuadEquation::setC(float value){
	this->_solved = false;
	this->_c = value;
	this->doOnModify();
}

bool QuadEquation::isError(){
	return this->_error;
}
bool QuadEquation::getAutoSolve(){
	return this->_autoSolve;
}
void QuadEquation::setAutoSolve(bool value){
	if (value != this->_autoSolve) {
		this->_autoSolve = value;
		if (value) {
            this->solve();
		}
	}
}

bool QuadEquation::isAnyRoot(){
	return this->_anyRoot;
}

int QuadEquation::getNumRoots(){
	return this->_numRoots;
}

void QuadEquation::printAnswer(){
	if (!_error) {
		cout << "a = " << _a << ", b = " << _b << ", c = " << _c << endl;
	}

	if (_error){
		cout << "Coefficient format error" << endl;
	}else if (!_solved) {
		cout << "Equation need to be solved" << endl;
	}else if (_anyRoot) {
		cout << "Every number is a root" << endl;
	}else if (_numRoots == 0) {
		cout << "No roots" << endl;
	}else if (_numRoots == 1) {
		cout << "One root:\t"<< _x1 << endl;
	}else if (_numRoots == 2) {
		cout << "Two roots:\t"<< _x1 << '\t' << _x2 << endl;
	}else{
		cout << "Solve the equation" << endl;
    }
}

bool QuadEquation::isSolved(){
	return this->_solved;
}

bool QuadEquation::strToFloat_bool(const char *str, float & f){
	bool result = false;
	char * err;

	f = strtod(str,&err);
	if (err == &str[strlen(str)])
		result = true;
	return result;
}

float QuadEquation::getA(){
	return _a;
}
float QuadEquation::getB(){
	return _b;
}
float QuadEquation::getC(){
	return _c;
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
