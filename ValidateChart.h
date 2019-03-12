#ifndef VALIDATE_CHART_H
#define VALIDATE_CHART_H

#include "ApplicationManager.h"
#include "Actions\Action.h"
#include "Loop.h"
#include "ComplexAssign.h"
#include "Condition.h"
#include "Read.h"
#include "Write.h"
#include "Statements\SmplAssign.h"
#include "Start.h"
#include "End.h"


class ValidateChart :public Action 
{
protected:
	bool Validated;

public:
	ValidateChart(ApplicationManager *pAppManager);

	//Reads parameters required for action to execute
	void ReadActionParameters();
	
	//Execute action (code depends on action type)
	void Execute();
	bool isValidated();

	int checkOneStart();
	int checkOneEnd();
	int checkStatConnections();
	int checkConnConnections();
	bool checkEndGOTO(Statement*);
	~ValidateChart(){}
};

#endif
