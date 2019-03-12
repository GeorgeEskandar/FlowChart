#include "Move.h"
#include "ApplicationManager.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Select.h"
#include "Statements\Statement.h"
#include "CMUgraphicsLib\auxil.h"
#include "Condition.h"
#include <iostream>
using namespace std;

Move::Move(ApplicationManager *pAppManager):Action(pAppManager)
{
	//Clears if multi selection is set
	/*Select::UnSelectAll(pAppManager);*/
}

void Move::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Click and hold to move selected statements.");
	Point p;
	Point OffSet(0,0);
	window* pWind = pOut->GetWindPtr();
	pWind->FlushMouseQueue();
    pWind->FlushKeyQueue();
    int iX,iY;
	iX=iY=0; 
    int iXOld,iYOld;
    iYOld=iXOld=0;
	bool check = false; // used to avoid useless dragging
	Point max;
	Point min;
	Point temp;
	Point yes_end;
	Point no_end;
	Condition * Cptr;
	for(int i=0;i<pManager->StatCount;i++)
		if(pManager->StatList[i]->IsSelected())
		{ min = max = pManager->StatList[i]->GetCenter(); iXOld = max.x; iYOld = max.y; i = pManager->StatCount; check =true;}
	if(check)
	{
		for(int i=0;i<pManager->StatCount;i++) //MIN-MAX to determine bounds.
		{
			if(pManager->StatList[i]->IsSelected())
			{
				if(pManager->StatList[i]->GetCenter().x>max.x)
					max.x = pManager->StatList[i]->GetCenter().x;
				if(pManager->StatList[i]->GetCenter().y>max.y)
					max.y = pManager->StatList[i]->GetCenter().y;
				if(pManager->StatList[i]->GetCenter().x<min.x)
					min.x = pManager->StatList[i]->GetCenter().x;
				if(pManager->StatList[i]->GetCenter().y<min.y)
					min.y = pManager->StatList[i]->GetCenter().y;
			}
		}
		while(pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_UP)
		{}
		while(pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_DOWN)
		{
			OffSet.x = 0; OffSet.y = 0;
			if(iX != iXOld && iX>=0 && iX<=UI.width)
			{
				OffSet.x = (iX - iXOld); 
				iXOld = iX;
			}
			if(iY != iYOld && iY>=0 && iY<=UI.height)
			{
				OffSet.y = (iY - iYOld);
				iYOld = iY;
			}		
			if((min.y + OffSet.y) <= 3*UI.TlBrWdth) 
				OffSet.y = -(min.y - 3*UI.TlBrWdth);
			if((min.x + OffSet.x) <= 10) 
				OffSet.x = 0;
			if((max.y + OffSet.y) >= (UI.height - UI.StBrWdth)) 
				OffSet.y = UI.height-(max.y + UI.StBrWdth);
			if((max.x + OffSet.x) >= UI.width) 
				OffSet.x = UI.width-max.x;
			max.x +=OffSet.x;
			max.y +=OffSet.y;
			min.x +=OffSet.x;
			min.y +=OffSet.y;
			for(int i=0;i<pManager->StatCount;i++)
			{	
				Cptr = dynamic_cast <Condition*> (pManager->StatList[i]);
				if(pManager->StatList[i]->IsSelected() && Cptr==NULL)
				{ 
					pManager->StatList[i]->Move(OffSet);
					if(pManager->StatList[i]->getConnector()!=NULL)
						if(pManager->StatList[i]->getConnector()->getDstStat()==NULL)
						{
							temp = pManager->StatList[i]->getConnector()->getEndPoint();
							pManager->StatList[i]->getConnector()->setEndPoint(Point(temp.x+OffSet.x,temp.y+OffSet.y)); 
						}
				}
				else if(pManager->StatList[i]->IsSelected() && Cptr!=NULL)
				{
					pManager->StatList[i]->Move(OffSet);
					temp=Cptr->GetYesOut();
					if(Cptr->getYesConnector()->getDstStat()==NULL)
					{	
						yes_end.x=temp.x - 20 + OffSet.x;
						yes_end.y=temp.y + 20 + OffSet.y;
						Cptr->getYesConnector()->setEndPoint(yes_end);
					}
					Cptr->getYesConnector()->setStartPoint((Point(temp.x+OffSet.x,temp.y+OffSet.y)));
					temp=Cptr->GetNoOut();
					Cptr->getNoConnector()->setStartPoint((Point(temp.x+OffSet.x,temp.y+OffSet.y)));
					if(Cptr->getNoConnector()->getDstStat()==NULL)
					{	
						no_end.x=temp.x + 20 + OffSet.x;
						no_end.y=temp.y + 20 + OffSet.y;
						Cptr->getNoConnector()->setEndPoint(no_end);
					}
				}
			}
			Pause(10);
			pManager->UpdateInterface();
			pOut->ClearStatusBar();	
			pOut->ClearToolBar(3);	
			pOut->PrintMessage("Click and hold to move selected statements.");
		}
	pOut->ClearStatusBar();	
	pOut->CreateDesignToolBar();
	pOut->CreateMainToolBar();
	}
}

void Move::Execute()
{
	ReadActionParameters();
	pManager->UpdateInterface();

}
