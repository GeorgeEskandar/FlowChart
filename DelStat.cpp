#include "DelStat.h"
#include "ApplicationManager.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
DelStat::DelStat(ApplicationManager *pAppManager):Action(pAppManager)
{}

void DelStat::ReadActionParameters()
{
	pManager->GetUserAction();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Delete Statement: Click the icon again to delete all selected statements and connectors; click anywhere else to cancel");
	Act = pManager->GetUserAction();
	pOut->ClearStatusBar();		
}

void DelStat::Execute()
{
	ReadActionParameters();
	if(Act == DEL)
	{
		pManager->DeleteSelectedStat();
		//pManager->DeleteSelectedConn();
	}
}

