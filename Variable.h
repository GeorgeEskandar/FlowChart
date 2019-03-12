#ifndef VARIABLE_H
#define VARIABLE_H
/*
	Developed By Nagy Mohamed
*/
#include<map>
#include<string>
#include<string.h>
#include"Condition.h"
using namespace std;

class Variable
{
	map<string,double> myVarsValue; //to track variable values
	map<string,bool> myVarsState;  // to track if a variable has a value or not , to avoid outputing garbage
public:
	Variable();
	~Variable();

	bool AddVar(string); // Creats a new varibale
	bool SetVar(string ,double); // Assigns a value to a variable; if var exits return true otherwise false;
	bool GetVar(string ,double &); // If var exits return true and fills parameter with value, if var doesn't exit return 0;
	bool RunExp(string exp,double &retValue); //runs an algebric expression and return its value , if unable to do , return false;
	bool RunIneq(double Rvalue,double Lvalue,Relational op);// Runs an inquality;
	string filterName(string name);
	string AllVar();
};

#endif