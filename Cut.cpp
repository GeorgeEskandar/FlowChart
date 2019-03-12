#include "Cut.h"
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

Cut::Cut(ApplicationManager *pAppManager):Action(pAppManager)
{
	//Clears if multi selection is set
	Select::UnSelectAll(pAppManager);
}

void Cut::ReadActionParameters()
{
	int index;
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pManager->GetOutput()->PrintMessage("Cut Statement, Click on statement you want to cut");
	Stat=Select::getOneSelected(pManager);
	if(Stat==0)
		return;
	
	pManager->pCopiedStat[0]= Stat->Copy();
	//pManager->DeleteStat(index);
	Stat->SetSelected(1);
	pManager->DeleteSelectedStat();
	pOut->ClearStatusBar();		
}

void Cut::Execute()
{
	ReadActionParameters();
}
