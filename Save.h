#ifndef SAVE_H
#define SAVE_H

#include "Actions\Action.h"
#include "Statements\Statement.h"
#include"ApplicationManager.h"
#include<iostream>
#include<fstream>
#include "Statements\Connector.h"
#include "LoopConnector.h"
using namespace std;

class Save:public Action
{
private:
	ofstream Outfile;
public:
	Save(ApplicationManager* );
	virtual void ReadActionParameters();
	virtual void Execute();
};


#endif