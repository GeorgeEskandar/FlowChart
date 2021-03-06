#ifndef SIMULATE_H
#define SIMULATE_H

#include "Actions\Action.h"
#include "ApplicationManager.h"
#include "Statements\Statement.h"
#include "Variable.h"

class Simulate:public Action
{
public:
	Simulate(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	void SubSimulate(Statement * ,Statement *);

	~Simulate(){}

private:
	
	Statement *CurSt;
	Statement *CurEnd;
	Variable *MyCPU;

};






#endif