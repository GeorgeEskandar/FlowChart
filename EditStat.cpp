#include "EditStat.h"
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

EditStat::EditStat(ApplicationManager* pApp)
	:Action(pApp)
{}
void EditStat::ReadActionParameters()
{
	SmplAssign*SimpAssignptr;
	ComplexAssign*CompAssignptr;
	Condition*Condptr;
	Loop* LoopPtr;
	Read* ReadPtr;
	Write* WritePtr;

	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pManager->GetOutput()->PrintMessage("Edit Statement, Click on statement");
	Statarr=Select::getOneSelected(pManager);
	SimpAssignptr = dynamic_cast<SmplAssign*>(Statarr);
	CompAssignptr = dynamic_cast<ComplexAssign*>(Statarr);
	Condptr = dynamic_cast<Condition*>(Statarr);
	LoopPtr = dynamic_cast<Loop*>(Statarr);
	ReadPtr = dynamic_cast<Read*>(Statarr);
    WritePtr = dynamic_cast<Write*>(Statarr);
	if(Statarr==0)
		return;
	if(SimpAssignptr!=NULL)
	{
		string LHS;
		double RHS;
		Point c;
		
		pOut->PrintMessage("Enter Variable Name: ");
		LHS = pIn->GetString(pOut);

		pOut->PrintMessage("Enter Value: ");
		RHS = pIn->GetValue(pOut);
		SimpAssignptr->setLHS(LHS);
		SimpAssignptr->setRHS(RHS);
	}
	else if(CompAssignptr!=NULL)
	{
		string LHS;
		string RHS;
		Point c;
		
		pOut->PrintMessage("Enter Variable Name: ");
		LHS = pIn->GetString(pOut);

		pOut->PrintMessage("Enter Expression: ");
		RHS = pIn->GetString(pOut);

		CompAssignptr->setLHS(LHS);
		CompAssignptr->setRHS(RHS);
	}
	else if(Condptr!=NULL)
	{
		string LHS;
		string RHS;
		Point c;
		Relational Operator;

		pOut->PrintMessage("Enter New text: ");
		LHS = pIn->GetString(pOut);

		pOut->PrintMessage("Enter Value: ");
		RHS = pIn->GetString(pOut);
		pOut->CreateConditionOperToolBar();
		pOut->PrintMessage("Choose operator from toolbar: ");
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
		Condptr->setOp(Operator);
		Condptr->setLHS(LHS);
		Condptr->setRHS(RHS);
	}
	else if(LoopPtr)
	{
		string LHS;
		string RHS;
		Relational Operator;

		pOut->PrintMessage("Enter first Variable Name: ");
		LHS = pIn->GetString(pOut);

		pOut->PrintMessage("Enter second Variable Name or Value: ");
		RHS = pIn->GetString(pOut);
		pOut->CreateConditionOperToolBar();
		pOut->PrintMessage("Choose operator from toolbar: ");
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

		LoopPtr->setOp(Operator);
		LoopPtr->setLHS(LHS);
		LoopPtr->setRHS(RHS);
	}
	else if(dynamic_cast<Start*>(Statarr))
	{
		pOut->PrintMessage("You cannot edit a Start statement.");
		return;
	}
	else if(dynamic_cast<End*>(Statarr))
	{
		pOut->PrintMessage("You cannot edit an End statement.");
		return;
	}
	else if(ReadPtr)
	{
		string RHS;
		pOut->PrintMessage("Enter Variable Name: ");
		RHS = pIn->GetString(pOut);
		ReadPtr->setRHS(RHS);
	}
	else if(WritePtr)
	{
		string RHS;
		pOut->PrintMessage("Enter Variable Name: ");
		RHS = pIn->GetString(pOut);
		WritePtr->setRHS(RHS);
	}
	pManager->GetOutput()->ClearStatusBar();
}

 void EditStat::Execute()
 {
	ReadActionParameters();
 }
