#ifndef LOAD_H
#define LOAD_H

#include "Actions\Action.h"
#include "Statements\Statement.h"
#include"ApplicationManager.h"
#include<iostream>
#include<fstream>
using namespace std;

class Load:public Action
{
private:
	ifstream Infile;
public:
	Load(ApplicationManager* );
	virtual void ReadActionParameters();
	virtual void Execute();
};


#endif