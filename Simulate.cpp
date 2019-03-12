#include "Simulate.h"
#include "Connect.h"
#include "Actions\Action.h"
#include "Condition.h"
#include "End.h"
#include "Loop.h"
#include "Read.h"
#include "Write.h"
#include "Start.h"
#include "End.h"
#include "Statements\SmplAssign.h"
#include "ComplexAssign.h"
#include "Variable.h"
#include <string>
#include <iostream>
using namespace std;

Simulate::Simulate(ApplicationManager* pApp)
     :Action(pApp)
{
	MyCPU = new Variable;
}

void Simulate::ReadActionParameters()
{
	//Searches for the start and End statment	
	for(int i=0;i<pManager->StatCount;i++)
	{
		if(dynamic_cast<Start *>(pManager->StatList[i]))
		{
			CurSt = pManager->StatList[i];
			
		}else if(dynamic_cast<End *>(pManager->StatList[i]))
		{
			CurEnd = pManager->StatList[i];
		}
	}
}

void Simulate::SubSimulate(Statement * StartSt,Statement * EndSt)
{
	Connector * CurConnetor;
	string VarName,Exp,SimMessage;
	double VarValue,ExpValue;
	Point p;
	p.x = 150;
	p.y=150;
	while(StartSt!=EndSt) // Simulation ends when you find end of Branch Statement
	{
		if(dynamic_cast<Start *>(StartSt))
		{
			// Only Follow to the next statement
			CurConnetor = StartSt->getConnector();
		}
		else if (dynamic_cast<Read *>(StartSt))  // A Read Statement is encountered;
		{
			Read * ReadStat = (Read *)StartSt;
			SimMessage = "Please Click Any Where  to Enter { "+ ReadStat->getRHS() + " } A double Value";
			pManager->pOut->PrintMessage(SimMessage);
			pManager->pIn->GetPointClicked(p);

			VarName = ReadStat->getRHS();
			VarValue = pManager->pIn->GetValue(pManager->pOut);
			//Assign the value to the variable in MyCPU;
			MyCPU->SetVar(VarName,VarValue);
			//cout<<"Name "<<VarName<<" Value "<<VarValue<<endl;
			CurConnetor = StartSt->getConnector();
		}else if (dynamic_cast<Write *>(StartSt))  // A Write Statement is encountered;
		{
			Write * WriteStat = (Write *)StartSt;
			
			VarName = WriteStat->getRHS();
			if(MyCPU->GetVar(VarName,VarValue))
			{				
				SimMessage = "Name: "+ VarName +" ,Value "+ to_string((long double)VarValue) + " , Please Click any where to continue";
				pManager->pOut->PrintMessage(SimMessage);
				pManager->pIn->GetPointClicked(p);
				
			}else
			{
				//Message
				SimMessage = "Message:: "+VarName;
				pManager->pOut->PrintMessage(SimMessage);
				pManager->pIn->GetPointClicked(p);
			
			}
			 CurConnetor = StartSt->getConnector();
			
		}else if (dynamic_cast<SmplAssign *>(StartSt))  // A Simple Assigment Statement is encountered;
		{
			SmplAssign * SmpStat = (SmplAssign *)StartSt ;
			VarName = SmpStat->getLHS();
			VarValue = SmpStat->getRHS();
			
			//Assign The Value to the variable
			MyCPU->SetVar(VarName,VarValue);
			CurConnetor = StartSt->getConnector();
		}else if (dynamic_cast<ComplexAssign *>(StartSt))  // A Simple Assigment Statement is encountered;
		{
			ComplexAssign * ComStat = (ComplexAssign *)StartSt ;
			VarName = ComStat->getLHS();
			Exp = ComStat->getRHS();
			//cout<<"Expression "<<Exp<<endl;
			if(!MyCPU->RunExp(Exp,VarValue))
			{
				//Run Time Error , Trying to Access a Variable not previously declared;
				SimMessage = "Run Time Error , Trying to Access a Variable not previously declared , Return to Design Mode Again";
				pManager->pOut->PrintMessage(SimMessage);
				return;
			}
			//cout<<"Expression "<<Exp<<" Value "<<VarValue<<endl;
			//Assign The Value to the variable
			MyCPU->SetVar(VarName,VarValue);
			CurConnetor = StartSt->getConnector();
		}else if (dynamic_cast<Loop *>(StartSt))  // A Loop Statement is encountered;
		{
			//cout<<"Loop "<<endl;
			Loop * HeadOfLoop = (Loop *) StartSt;
			Statement * EndOfLoop = NULL;
			bool stopLoop = 1;
			for(int i=0;i<pManager->StatCount&&stopLoop;i++)
			{
				//	cout<<"Checking"<<endl;
				if(pManager->StatList[i]->getLoopConnector()!=NULL)
				{
					if(pManager->StatList[i]->getLoopConnector()->getDstStat()==HeadOfLoop)
					{
						EndOfLoop = pManager->StatList[i];
					//	cout<<"Got its end"<<endl;
						stopLoop=0;
					}
				}	
			}

			if(EndOfLoop==NULL)// A While Loop that has to ending statement
			{
				//Run Time Error , Trying to Access a Variable not previously declared;
				SimMessage = "Run Time Error ,A Loop that has no ending statement, Return to Design Mode Again";
				pManager->pOut->PrintMessage(SimMessage);
				return;
			}
			double Lvalue,Rvalue;
			//cout<<"Ok exp "<<endl;
			VarName = HeadOfLoop->getLHS();
			Exp = HeadOfLoop->getRHS();
			
			if(!MyCPU->GetVar(VarName,Lvalue))
			{				
				//Run Time Error , Trying to Access a Variable not previously declared;
				SimMessage = "Run Time Error , Trying to Access a Variable not previously declared , Return to Design Mode Again";
				pManager->pOut->PrintMessage(SimMessage);
				return;
			}
			
			if(!MyCPU->RunExp(Exp,Rvalue))
			{
				//Run Time Error , Trying to Access a Variable not previously declared;
				SimMessage = "Run Time Error , Trying to Access a Variable not previously declared , Return to Design Mode Again";
				pManager->pOut->PrintMessage(SimMessage);
				return;
			}

			
			while(MyCPU->RunIneq(Lvalue,Rvalue,HeadOfLoop->getOp()))
			{
					//Do the steps between the Loop Block
						//cout<<"Lvalue "<<Lvalue<<" Rvalue "<<Rvalue<<" Enterning Sub Loop "<<endl;
						//cout<<"Step to "<<HeadOfLoop->getConnector()->getDstStat()<<" end to "<<EndOfLoop->getConnector()->getDstStat()<<endl;
						SubSimulate(HeadOfLoop->getConnector()->getDstStat(),EndOfLoop->getConnector()->getDstStat());
					//Update Values of Lvalue and Rvalue;
						if(!MyCPU->GetVar(VarName,Lvalue))
						{				
							//Run Time Error , Trying to Access a Variable not previously declared;
							SimMessage = "Run Time Error , Trying to Access a Variable not previously declared , Return to Design Mode Again";
							pManager->pOut->PrintMessage(SimMessage);
							return;
						}
			
						if(!MyCPU->RunExp(Exp,Rvalue))
						{
							//Run Time Error , Trying to Access a Variable not previously declared;
							SimMessage = "Run Time Error , Trying to Access a Variable not previously declared , Return to Design Mode Again";
							pManager->pOut->PrintMessage(SimMessage);
							return;
						}
			}
			CurConnetor = EndOfLoop->getConnector();
		}else if (dynamic_cast<Condition *>(StartSt))  // A Loop Statement is encountered;
		{
			Condition * CondStat = (Condition *)StartSt ;
			double Lvalue,Rvalue;
			VarName = CondStat->getLHS();
			if(!MyCPU->GetVar(VarName,Lvalue))
			{				
				//Run Time Error , Trying to Access a Variable not previously declared;
				SimMessage = "Run Time Error , Trying to Access a Variable not previously declared , Return to Design Mode Again";
				pManager->pOut->PrintMessage(SimMessage);
				return;
			}

			Exp = CondStat->getRHS();
			if(!MyCPU->RunExp(Exp,Rvalue))
			{
				//Run Time Error , Trying to Access a Variable not previously declared;
				SimMessage = "Run Time Error , Trying to Access a Variable not previously declared , Return to Design Mode Again";
				pManager->pOut->PrintMessage(SimMessage);
				return;
			}

			// Decide is it True or False;
			if(MyCPU->RunIneq(Lvalue,Rvalue,CondStat->getOp()))
			{
				//True;
				//Directs to the true connector;
				CurConnetor = CondStat->getYesConnector();
			}else
			{
				//False;
				//Directs to the False connector;
				CurConnetor = CondStat->getNoConnector();
			}

		}

			//Proceed to the next Statment;
			 StartSt=CurConnetor->getDstStat();
			 if(p.y<100) return;
			 //cout<<"End of Sim "<<endl;
	}//End of While
	//cout<<"End of Sim"<<endl;
}

void Simulate::Execute()
{
	ReadActionParameters();
	if(CurSt==NULL || CurEnd == NULL ) 
		{
			return ; // The flow chart has no start or no End;
		}
	SubSimulate(CurSt,CurEnd);
	string SimMessage = MyCPU->AllVar() + " Simulation Ended Successfully ";
	pManager->pOut->PrintMessage(SimMessage);
}