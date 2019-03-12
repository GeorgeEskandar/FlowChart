#include "Connect.h"
#include "Actions\Action.h"
#include "Select.h"
#include "Condition.h"
#include "End.h"
#include "Loop.h"


Connect::Connect(ApplicationManager* pApp)
     :Action(pApp)
{}

void Connect::ReadActionParameters()
{
	Source=Select::getOneSelected(pManager);
	Destination= Select::getOneSelected(pManager);
	pManager->GetOutput()->ClearStatusBar();
}

void Connect::Execute()
{
	ReadActionParameters();
	if(Source==0 || Destination==0)
		return;
	Condition* pCond= dynamic_cast<Condition*>(Source);
	if(pCond!=0)
	{
		pManager->GetOutput()->PrintMessage("Cannot set a connection from a condition statement, edit yes or no connector");
		return;
	}
	End* pEnd= dynamic_cast<End*>(Source);
	if(pEnd!=0)
	{
		pManager->GetOutput()->PrintMessage("Cannot set a connection from an end statement");
		return;
	}
	if(Source->getConnector()!=0)
		{
		pManager->GetOutput()->PrintMessage("Already Connected");
		return;
	}
	if(Source==Destination)
	{
		pManager->GetOutput()->PrintMessage("Cannot connect an object to itself");
		return;
	}
	Connector* pConnector= new Connector(Source, Destination);
	Source->setConnector(pConnector);
	Destination->setConnected(true, pConnector);
	pManager->AddConnector(pConnector);
}