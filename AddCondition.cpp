#include "AddCondition.h"
#include <sstream>
#include <iostream>
AddCondition::AddCondition(ApplicationManager* pApp)
	:Action(pApp)
{}

void AddCondition::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Action: add conditional statement, Click anywhere");
	bool check = false;
	while(!check)
	{
		pIn->GetPointClicked(Position);
		if(Position.y < (UI.COND_HI/2 + 3*UI.TlBrWdth) || Position.y > (UI.height-UI.COND_HI/2 - UI.StBrWdth))
			pOut->PrintMessage("Error, out of bounds. Please click elsewhere.");
		else 
			check = true;
	}
	pOut->CreateConditionOperToolBar();
	ActionType Act= pIn->GetUserAction();
		if(Act == EQUAL)
		{
			Operator=EQ;
		}
		else if(Act  == NOT_EQUAL)
		{
			Operator=NOT;
		}
		else if(Act  == GREATER_THAN)
		{
			Operator= GRT;
		}
		else if(Act == LESS_THAN)
		{
			Operator=LSS;
		}
		else if(Act == GREATER_EQUAL)
		{
			Operator=GRT_EQ;
		}
		else if(Act== LESS_EQUAL)
		{
			Operator=LSS_EQ;
		}
		pOut->PrintMessage("Enter first Variable Name: ");
		LeftSide = pIn->GetString(pOut);
		pOut->PrintMessage("Enter second Variable Name: ");
		RightSide = pIn->GetString(pOut);
		pOut->ClearToolBar(3);
		pOut->ClearStatusBar();		
}


void AddCondition::Execute()
{
	Output* pOut=pManager->GetOutput();
	ReadActionParameters();
	Condition* pCondition=new Condition(Position, LeftSide,RightSide,Operator);
	pManager->AddStatement(pCondition);	
	pManager->AddConnector(pCondition->getYesConnector());
	pManager->AddConnector(pCondition->getNoConnector());
	pCondition->setID(pManager->getStatCount());
}