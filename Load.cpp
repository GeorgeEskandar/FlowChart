#include"Load.h"
#include "Loop.h"
#include "ComplexAssign.h"
#include "Condition.h"
#include "Read.h"
#include "Write.h"
#include "Statements\SmplAssign.h"
#include "Start.h"
#include "End.h"
#include "LoopConnector.h"
#include "Statements\Connector.h"

Load::Load(ApplicationManager* pApp)
	:Action(pApp)
{
}

void Load::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	if(pManager->StatCount == 0)
	{
		pOut->PrintMessage("Load: click to write directory of destination file");
		Point P;
		pIn->GetPointClicked(P);
		pOut->ClearStatusBar();
		string address;
		pIn->GetString(pOut);
		Infile.open(address);
		if(!Infile)
			Infile.open("Save_Default.txt");
	}
	else
	{
		ActionType CutQ;
		pOut->PrintMessage("You already have a chart drawn; if you want to delete it and load a different one, click the icon again. Click elsewhere if not.");
		CutQ=pIn->GetUserAction();
		if(CutQ==LOAD)
		{
			for(int i=0;i<pManager->StatCount;i++)
			{
				pManager->StatList[i]->SetSelected(1);
			}
			pManager->DeleteSelectedStat();
			pOut->PrintMessage("Load: click to write directory of destination file");
			Point P;
			pIn->GetPointClicked(P);
			pOut->ClearStatusBar();
			string address;
			pIn->GetString(pOut);
			Infile.open(address);
			if(!Infile)
				Infile.open("Save_Default.txt");
		}
	}
	pOut->ClearStatusBar();
}

void Load::Execute()
{
	ReadActionParameters();
	int count=0;
	Infile>>count;
	for(int i=0;i<count && !Infile.eof();i++)
	{
		//cout<<"Step: "<<i<<endl;
		string type;
		Infile>>type;
		Point default_center;
		default_center.x=0;
		default_center.y=0;
		if(type=="SMPLASSIGN")
		{
			SmplAssign* pAssign= new SmplAssign(default_center);
			pAssign->Load(Infile);
			//cout<<"ID is "<<pAssign->getID()<<endl;
			pManager->AddStatement(pAssign);
		}
		else if(type=="STRT")
		{
			Start*pStart= new Start(default_center);
			pStart->Load(Infile);
			pManager->AddStatement(pStart);
		}
		else if(type=="END")
		{
			End*pEnd= new End(default_center);
			pEnd->Load(Infile);
			pManager->AddStatement(pEnd);
		}
		else if(type=="READ")
		{
			Read*pRead= new Read(default_center,"");
			pRead->Load(Infile);
			pManager->AddStatement(pRead);
		}
		else if(type=="WRITE")
		{
			Write* pWrite= new Write(default_center,"");
			pWrite->Load(Infile);
			pManager->AddStatement(pWrite);
		}
		else if(type=="COND")
		{
			 Condition* pCond= new Condition(default_center,"","",EQ);
			pCond->Load(Infile);
			pManager->AddStatement(pCond);
			pManager->AddConnector(pCond->getYesConnector());
			pManager->AddConnector(pCond->getNoConnector());
		}
		else if(type=="SNGLOP")
		{
			ComplexAssign*pComplex= new ComplexAssign(default_center);
			pComplex->Load(Infile);
			pManager->AddStatement(pComplex);
		}
		else if(type=="LOOP")
		{
			Loop* pLoop= new Loop(default_center,"","",EQ);
			 pLoop->Load(Infile);
			pManager->AddStatement( pLoop);
			pManager->AddConnector( pLoop->GetloopConnector());
		}		
	}	
			count=0;
			Infile>>count;
			for(int i=0; i<count && !Infile.eof();i++)
			{
				//cout<<"Connector Step: "<<i<<endl;
				int id1,id2,type;
				Infile>>id1>>id2>>type;
				Statement* Source=0;
				Statement* Destination=0;
	            if(id1!=-1)
					Source=pManager->GetStatementByID(id1);
				//cout<<pManager->GetStatementByID(id1)<<endl;
				if(id2!=-1)
					Destination=pManager->GetStatementByID(id2);
				/*cout<<"Source Just After"<<Source<<endl;
				cout<<"Destination Just After"<<Destination<<endl;
				cout<<"Id From : "<<id1<<" , Id To :"<<id2<<" Type: "<<type<<endl;*/

				if(type==0)
				{
					if(id1==-1)
						Source=0;
					if(id2==-1)
						Destination=0;
					Connector* pConnector= new Connector(Source, Destination);
					Source->setConnector(pConnector);
					pConnector->setStartPoint(Source->GetOutlet());
					if(Destination!=0)
						Destination->setConnected(true, pConnector);
					else
					{
						Point P(pConnector->getStartPoint());
						P.y+=30;
						pConnector->setEndPoint(P);
					}					
					pManager->AddConnector(pConnector);
				}
				else if(type==1)
				{
					Condition* pCond=dynamic_cast<Condition*>(Source);
					Connector* pYes=pCond->getYesConnector();
					if(Destination!=0)
						Destination->setConnected(true, pYes);
					else
					{
						Point P(pYes->getStartPoint());
						P.y+=30;
						pYes->setEndPoint(P);
					}
					pYes->setDstStat(Destination);
				}
				else if(type==2)
				{
					Condition* pCond=dynamic_cast<Condition*>(Source);
					Connector* pNo=pCond->getNoConnector();
					if(Destination!=0)
						Destination->setConnected(true, pNo);
					else
					{
						Point P(pNo->getStartPoint());
						P.y+=30;
						pNo->setEndPoint(P);
					}
					pNo->setDstStat(Destination);
				}
				else if(type==3)
				{
					Loop* pLoop=dynamic_cast<Loop*>(Destination);
					Connector* pLoopConn=pLoop->GetloopConnector();
					if(Source!=0)
						Source->setLoopConnector(pLoopConn);
					else
					{
						Point P(pLoopConn->getEndPoint());
						P.y+=100;
						pLoopConn->setStartPoint(P);
					}
					pLoopConn->setSrcStat(Source);
				}
			}
	Infile.close();
}