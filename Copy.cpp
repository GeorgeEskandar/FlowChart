#include "Copy.h"
#include "ApplicationManager.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Select.h"
#include "Statements\Statement.h"
#include "Actions\AddSmplAssign.h"
#include "AddComplexAssign.h"
#include "AddCondition.h"
#include "AddWrite.h"
#include "AddStart.h"
#include "AddEnd.h"
#include "AddLoop.h"
#include "Actions\AddRead.h"
#include "Condition.h"
#include "End.h"
#include "Loop.h"

using namespace std;

Copy::Copy(ApplicationManager *pAppManager):Action(pAppManager)
{
	//Clears if multi selection is set
	Select::UnSelectAll(pAppManager);
}

void Copy::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pManager->GetOutput()->PrintMessage("Copy Statement, Click on statement you want to copy");
	Stat=Select::getOneSelected(pManager);
	if(Stat==0)
		return;

	pManager->pCopiedStat[0]= Stat->Copy();

	pOut->ClearStatusBar();		
}

void Copy::Execute()
{
	ReadActionParameters();
}
