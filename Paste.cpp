#include "Paste.h"
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
#include <string>


using namespace std;

Paste::Paste(ApplicationManager *pAppManager):Action(pAppManager)
{
	//Clears if multi selection is set
	Select::UnSelectAll(pAppManager);
}

void Paste::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	bool check = false;
	while(!check)
	{
		pIn->GetPointClicked(Position);
		if(Position.y < (UI.ASSGN_HI/2 + 3*UI.TlBrWdth) || Position.y > (UI.height-UI.ASSGN_HI/2 - UI.StBrWdth))
			pOut->PrintMessage("Error, out of bounds. Please click elsewhere.");
		else 
			check = true;
	}			
}

void Paste::Execute()
{
	Output *pOut = pManager->GetOutput();
	ReadActionParameters();
	if(pManager->pCopiedStat[0]==NULL)
		return;
	pManager->pCopiedStat[0]->setCenter(Position.x,Position.y);
	pManager->pCopiedStat[0]->DeterDim();
	Condition* pCond=dynamic_cast<Condition*>(pManager->pCopiedStat[0]);
	if(pCond!=NULL)
	{
		Point P(pCond->GetNoOut());
		P.x+=20;
		P.y+=20;
		pCond->getNoConnector()->setEndPoint(P);
		Point Q(pCond->GetYesOut());
		Q.x-=20;
		Q.y+=20;
		pCond->getYesConnector()->setEndPoint(Q);
		pManager->AddConnector(pCond->getYesConnector());
		pManager->AddConnector(pCond->getNoConnector());
	}
	Loop* pLoop= dynamic_cast<Loop*>(pManager->pCopiedStat[0]);
	if(dynamic_cast<Loop*>(pManager->pCopiedStat[0]))
	{
		Point P(pLoop->GetloopPoint());
		P.y+=100;
		pLoop->GetloopConnector()->setStartPoint(P);
		pLoop->GetloopConnector()->setEndPoint(pLoop->GetloopPoint());
		pManager->AddConnector(pLoop->GetloopConnector());
	}
	/*if(dynamic_cast<Loop*>(pManager->pCopiedStat[0]))
	{
		Loop* CopyStat =  dynamic_cast<Loop*>(pManager->pCopiedStat[0]);
		string Left = CopyStat->getLHS();
		string Right = CopyStat->getRHS();
		Relational Operator = CopyStat->getOp();
		Loop* newcopy = new Loop(Position, Left, Right, Operator);
		pManager->AddStatement(newcopy);
	}*/
	/*if(dynamic_cast<SmplAssign*>(pManager->pCopiedStat[0]))
	{
		SmplAssign *CopyStat =  dynamic_cast<SmplAssign*>(pManager->pCopiedStat[0]);
		string Left = CopyStat->getLHS();
		double Right = CopyStat->getRHS();
		SmplAssign *newcopy = new SmplAssign(Position, Left, Right);
		pManager->AddStatement(newcopy);
	}
	else if(dynamic_cast<ComplexAssign*>(pManager->pCopiedStat[0]))
	{
		ComplexAssign* CopyStat =  dynamic_cast<ComplexAssign*>(pManager->pCopiedStat[0]);
		string Left = CopyStat->getLHS();
		string Right = CopyStat->getRHS();
		ComplexAssign* newcopy = new ComplexAssign(Position, Left, Right);
		pManager->AddStatement(newcopy);
	}
	else if(dynamic_cast<Condition*>(pManager->pCopiedStat[0]))
	{
		Condition* CopyStat =  dynamic_cast<Condition*>(pManager->pCopiedStat[0]);
		string Left = CopyStat->getLHS();
		string Right = CopyStat->getRHS();
		Relational Operator = CopyStat->getOp();
		Condition* newcopy = new Condition(Position, Left, Right, Operator);
		pManager->AddStatement(newcopy);
	}
	else if(dynamic_cast<Loop*>(pManager->pCopiedStat[0]))
	{
		Loop* CopyStat =  dynamic_cast<Loop*>(pManager->pCopiedStat[0]);
		string Left = CopyStat->getLHS();
		string Right = CopyStat->getRHS();
		Relational Operator = CopyStat->getOp();
		Loop* newcopy = new Loop(Position, Left, Right, Operator);
		pManager->AddStatement(newcopy);
	}
	else if(dynamic_cast<Start*>(pManager->pCopiedStat[0]))
	{
		Start* CopyStat =  dynamic_cast<Start*>(pManager->pCopiedStat[0]);
		string text = CopyStat->getText();
		Start* newcopy = new Start(Position,text);
		pManager->AddStatement(newcopy);
	}
	else if(dynamic_cast<End*>(pManager->pCopiedStat[0]))
	{
		End* CopyStat =  dynamic_cast<End*>(pManager->pCopiedStat[0]);
		string text = CopyStat->getComment();
		End* newcopy = new End(Position,text);
		pManager->AddStatement(newcopy);
	}
	else if(dynamic_cast<Read*>(pManager->pCopiedStat[0]))
	{
		Read* CopyStat = dynamic_cast<Read*>(pManager->pCopiedStat[0]);
		string Left = "Read";
		string Right = CopyStat->getRHS();
		Read* newcopy = new Read(Position, Left, Right);
		pManager->AddStatement(newcopy);
	}
	else if(dynamic_cast<Write*>(pManager->pCopiedStat[0]))
	{
		Write* CopyStat =  dynamic_cast<Write*>(pManager->pCopiedStat[0]);
		string Left = "Write";
		string Right = CopyStat->getRHS();
		Write* newcopy = new Write(Position, Left, Right);
		pManager->AddStatement(newcopy);
	}*/
    pManager->AddStatement(pManager->pCopiedStat[0]);
	pManager->pCopiedStat[0]=NULL;
	pOut->PrintMessage("The Statement has been pasted");
	pOut->ClearStatusBar();
}
