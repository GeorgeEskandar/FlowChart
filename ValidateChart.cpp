#include "ApplicationManager.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Statements\Statement.h"
#include <iostream>
#include "ValidateChart.h"
using namespace std;

ValidateChart::ValidateChart(ApplicationManager *pAppManager):Action(pAppManager)
{}

void ValidateChart::ReadActionParameters()
{
	for(int i = 0; i < pManager->StatCount; i++)
	{
		 pManager->StatList[i]->setPassed(false);
	}
	Output* pOut = pManager->GetOutput();
	Validated = false;
	int temp;
	temp = checkOneStart();
	switch (temp)
	{
	case 0:
		//cout << "This flowchart has no Start point!" << endl;
		pOut->PrintMessage("This flowchart has no Start point!");
		return;
		break;
	case 2:
		//cout << "This flowchart has more than one Start point!" << endl;
		pOut->PrintMessage("This flowchart has more than one Start point!");
		return;
		break;
	}
	temp = checkOneEnd();
	switch (temp)
	{
	case 0:
		//cout << "This flowchart has no End point!" << endl;
		pOut->PrintMessage("This flowchart has no End point!");
		return;
		break;
	case 2:
		//cout << "This flowchart has more than one End point!" << endl;
		pOut->PrintMessage("This flowchart has more than one End point!");
		return;
		break;
	}
	temp = checkStatConnections();
	switch (temp)
	{
	case 1:
		//cout << "Some statement(s) is/are not connected." << endl;
		pOut->PrintMessage("Some statement(s) is/are not connected.");
		return;
		break;
	case 2:
		//cout << "Some statement(s) do not have an exit connector." << endl;
		pOut->PrintMessage("Some statement(s) do not have an exit connector.");
		return;
		break;
	}
	temp = checkConnConnections();
	switch (temp)
	{
	case 1:
		//cout << "Some connector(s) do/does not have a Source statment." << endl;
		pOut->PrintMessage("Some connector(s) do/does not have a Source statment.");
		return;
		break;
	case 2:
		//cout << "Some connector(s) do/does not have a Destination statment." << endl;
		pOut->PrintMessage("Some connector(s) do/does not have a Destination statment.");
		return;
		break;
	}
	Start* STARTptr;
	for(int i = 0; i < pManager->StatCount; i++)
	{
		STARTptr= dynamic_cast <Start*> (pManager->StatList[i]);
		if(STARTptr!=NULL)
			i = pManager->StatCount; //exiting the loop
	}
	Validated = checkEndGOTO(STARTptr);
	if(Validated == false)
		//cout << "This flowchart has either a GOTO branch or at least one path does not lead to the END statment." << endl;
		pOut->PrintMessage("This flowchart has either a GOTO branch or all paths do not lead to the END statment.");
	pOut->ClearStatusBar();		
}

void ValidateChart::Execute()
{
	ValidateChart::ReadActionParameters();
	
}

bool ValidateChart::isValidated()
{
	ValidateChart::Execute();
	return Validated;
}


int ValidateChart::checkOneStart()
{
	//Case=1, one Start found. Validated. Case=0, no Start found. Not validated. Case=2, more than one Start found. Not validated. 
	int Case = 0;
	for(int i =0; i < pManager->getStatCount(); i++)
		if(dynamic_cast <Start*> (pManager->StatList[i])!=NULL)
		{
			if(Case==0)
				Case=1;
			else if(Case==1)
			{ Case=2; return Case; }
		}
	return Case;
}

int ValidateChart::checkOneEnd()
{
	//Case=1, one End found. Validated. Case=0, no End found. Not validated. Case=2, more than one End found. Not validated.
	int Case = 0;
	for(int i =0; i < pManager->getStatCount(); i++)
		if(dynamic_cast <End*> (pManager->StatList[i])!=NULL)
		{
			if(Case==0)
				Case=1;
			else if(Case==1)
			{ Case=2; return Case; }
		}
	return Case;
}

int ValidateChart::checkStatConnections()
{
	//Case=0, All statements are connected. Validated. Case=1, Some statement(s) is/are not connected. Not validated. 
	//Case=2, Some statement(s) do not have an exit connector. Not validated.
	Start* STARTptr;
	End* ENDptr;
	Condition*ConPtr;
	int Case = 0;
	for(int i =0; i < pManager->getStatCount(); i++)
	{
		STARTptr= dynamic_cast <Start*> (pManager->StatList[i]);
		ENDptr= dynamic_cast <End*> (pManager->StatList[i]);
		ConPtr=dynamic_cast <Condition*> (pManager->StatList[i]);
		if(pManager->StatList[i]->isConnected()==false && STARTptr==NULL)
		{
			//cout << pManager->StatList[i]->isConnected();
			Case=1; return Case;
		}
		if(pManager->StatList[i]->getConnector()==NULL && ENDptr==NULL && ConPtr==NULL)
		{
			Case=2; return Case;
		}
	}
	return Case;
}

int ValidateChart::checkConnConnections()
{
	//Case=0, All connectors are connected. Validated. Case=1, Some connector(s) do/does not have a Source statment. Not validated. 
	//Case=2, Some connector(s) do/does not have a Destination statment. Not validated.
	int Case = 0;
	for(int i =0; i < pManager->getConnCount(); i++)
	{
		if(pManager->ConnList[i]->getSrcStat() == NULL)
		{
			Case=1; return Case;
		}
		if(pManager->ConnList[i]->getDstStat() == NULL)
		{
			Case=2; return Case;
		}
	}
	return Case;
}


bool ValidateChart::checkEndGOTO(Statement*CUR)
{	//This function returns true if all paths lead to an End and if there are no GOTO statements.
	Condition* CONDptr = dynamic_cast <Condition*> (CUR);
	End* ENDptr = dynamic_cast <End*> (CUR);
	if(ENDptr != NULL)
		return true;
	if(CUR->isPassed())
		return false;
	else if(CONDptr == NULL)
	{ CUR->setPassed(true); return checkEndGOTO(CUR->getConnector()->getDstStat()); } 
	else if(CONDptr != NULL)
	{	
		CUR->setPassed(true); 
		return (checkEndGOTO(CONDptr->getYesConnector()->getDstStat()) && checkEndGOTO(CONDptr->getNoConnector()->getDstStat())); 
	}
}


