#ifndef SIMULATESTEPSTEP_H
#define SIMULATESTEPSTEP_H

#include "Actions\Action.h"
#include "ApplicationManager.h"
#include "Statements\Statement.h"
#include "Variable.h"

class SimulateStepStep:public Action
{
public:
	SimulateStepStep(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	void SubSimulate(Statement * ,Statement *);

	~SimulateStepStep(){}

private:
	
	Statement *CurSt;
	Statement *CurEnd;
	Variable *MyCPU;

};






#endif