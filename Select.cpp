#include "ApplicationManager.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Select.h"
#include "Statements\Statement.h"
#include <iostream>
using namespace std;

Select::Select(ApplicationManager *pAppManager):Action(pAppManager)
{num =0;}

void Select::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Please Select/Unselect a Statment:");
	pIn->GetPointClicked(Position);

	int stopLoop=13;
	while(stopLoop==13)
	{
		//cout<<"X ,Y "<<Position.x<<" "<<Position.y<<endl;
		for(int i=0;i<pManager->StatCount;i++)
		{
			if(pManager->StatList[i]->CheckPoint(Position))
			{
				if(!pManager->StatList[i]->IsSelected())
				{
					string StatementComment = pManager->StatList[i]->getComment();
					if(StatementComment.size()!=0) pOut->PrintMessage("Statement Comment: "+StatementComment+" \\ To Select/Unselect More , Or Choose Anther Action: ");
					else pOut->PrintMessage("To Select/Unselect More , Or Choose Anther Action: ");
					pManager->StatList[i]->SetSelected(1);
				}else
				{
					pManager->StatList[i]->SetSelected(0);
					pOut->PrintMessage("To Select/Unselect More , Or Choose Anther Action: ");
				}
			}
		}
		pManager->UpdateInterface();
		
		pIn->GetPointClicked(Position);
		if(Position.y<150) break; 
	}

	pOut->ClearStatusBar();		
}

void Select::Execute()
{
	Select::ReadActionParameters();
}

Statement* Select::getOneSelected(ApplicationManager *pAppManager)
{
	Point p;
	pAppManager->pIn->GetPointClicked(p);
	for(int i=0;i<pAppManager->StatCount;i++)
	{
			if(pAppManager->StatList[i]->CheckPoint(p)) return pAppManager->StatList[i];
	}
	//if selected outside the statments;
	return NULL;
}

Connector* Select::SelectConnector(ApplicationManager *pAppManager)
{
	Point p;
	pAppManager->pIn->GetPointClicked(p);
	for(int i=0;i<pAppManager->ConnCount;i++)
	{
		if(pAppManager->ConnList[i]->CheckEnd(p))
		{
			pAppManager->ConnList[i]->SetEndSelected(true);
			pAppManager->UpdateInterface();
			return pAppManager->ConnList[i];
		}
		else if( pAppManager->ConnList[i]->CheckStart(p))
		{
			pAppManager->ConnList[i]->SetStartSelected(true);
			pAppManager->UpdateInterface();
			return pAppManager->ConnList[i];
		}
		
	}
	//if selected outside the statments;
	return NULL;
}

void Select::UnSelectAll(ApplicationManager *pAppManager)
{
	for(int i=0;i<pAppManager->StatCount;i++)
	{
		pAppManager->StatList[i]->SetSelected(0);
	}
}