#include "ApplicationManager.h"
#include "Actions\AddSmplAssign.h"
#include "AddComplexAssign.h"
#include "Actions\AddRead.h"
#include "AddWrite.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Select.h"
#include "AddCondition.h"
#include "AddStart.h"
#include "AddEnd.h"
#include "AddLoop.h"
#include "Move.h"
#include "AddComment.h"
#include "Connect.h"
#include "EditConn.h"
#include "DelStat.h"
#include "Simulate.h"
#include "SimulateStepStep.h"
#include <iostream>
#include "Save.h"
#include "Load.h"
#include "EditStat.h"
#include "Copy.h"
#include "Paste.h"
#include "ValidateChart.h"
#include "Cut.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	Statement::StatWindPtr = pOut->GetWindPtr();

	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	ValidateChart * ptr;
	Action* pAct = NULL;
	ActionType DecisionType;
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
	       case ADD_SMPL_ASSIGN:
				pOut->PrintMessage("Action: add assignment statement , Click anywhere");
				pAct = new AddSmplAssign(this);
				break;

			case ADD_COMPLEX_ASSIGN:

				pOut->PrintMessage("Action: add assignment statement , Click anywhere");
				pAct = new AddComplexAssign(this);
				break;

			case DEL:
				pAct = new DelStat(this);
				break;
			case ADD_COMMENT:
				pAct = new AddComment(this);
				break;
			case ADD_READ:
				pOut->PrintMessage("Action: add read statment , Click anywhere");
				pAct = new AddRead(this);
				break;

			case ADD_WRITE:
				pOut->PrintMessage("Action: add write statment , Click anywhere");
				pAct = new AddWrite(this);
				break;

			case ZOOM_IN:
				pOut->PrintMessage("Action: a click on the zoom in button , Click anywhere");
				break;

			case ZOOM_OUT:
				pOut->PrintMessage("Action: a click on the zoom out button , Click anywhere");
				break;

			case EDIT_STAT:
				pOut->PrintMessage("Action: a click on the edit satement button , Click anywhere");
				pAct=new EditStat(this);
				break;
			case EDIT_CONN:
				pOut->PrintMessage("Action: a click on the edit connection button , Click anywhere");
				pAct=new EditConn(this);
				break;

			case ADD_CONDITION:
				pOut->CreateConditionToolBar();
				DecisionType=pIn->GetUserAction();
				if(DecisionType==IF_CONDITION)
					{
						pAct = new AddCondition(this);
				}
				else
				{
					pAct=new AddLoop(this);
				}
				break;

			case ADD_CONNECTOR:
				pOut->PrintMessage("Action: add a connector , Click anywhere");
				pAct = new Connect(this);
				break;

			case SELECT:
				pOut->PrintMessage("Action: Select One or More Statments.");
				pAct = new Select(this);
				break;
			
			case STATUS:
				pOut->PrintMessage("Action: a click on the Status Bar, Click anywhere");
				break;
 
			case DSN_TOOL:
				pOut->PrintMessage("Action: a click on the Design Toolbar, Click anywhere");
				break;

			case SIM_MODE:
				pOut->PrintMessage("Action: Switch to Simulation Mode, validating and then creating simualtion tool bar");
				ptr = new ValidateChart(this);
				if(ptr->isValidated()== true)
				{ pOut->CreateSimulationToolBar(); }
				else 
					pAct = NULL;
				break;


			case DSN_MODE:
				pOut->PrintMessage("Action: Switch to Design Mode, creating Design tool bar");
				pOut->CreateDesignToolBar();
				break;

			case SAVE:
				pOut->PrintMessage("Action: a click on the save button, Click anywhere");
				pAct = new Save(this);
				break;

			case LOAD:
				pOut->PrintMessage("Action: a click on the load button, Click anywhere");
				pAct=new Load(this);
				break;

			case ADD_START:
				pOut->PrintMessage("Action: add a start statement, Click anywhere");
				pAct = new AddStart(this);
				break;
			
			case ADD_END:
				pOut->PrintMessage("Action: add an end statement, Click anywhere");
				pAct = new AddEnd(this);
				break;

			case START_SIM:
				pOut->PrintMessage("Action: start executing the flowchart, Click anywhere");
				pAct = new Simulate(this);
				break;

			case STOP_SIM:
				pOut->PrintMessage("Action: stop executing the flowchart, Click anywhere");
				break;

			case DEBUG_SIM:
				pOut->PrintMessage("Action: start executing the flowchart in Step By Step, Click anywhere");
				pAct = new SimulateStepStep(this);
				break;

			case NEXT_SIM:
				pOut->PrintMessage("Action: execute the next statement in debug mode, Click anywhere");
				break;

			case C_PP_SIM:
				pOut->PrintMessage("Action: convert the fowchart into executable c++ code, Click anywhere");
				break;
			case COPY_STAT:
				pOut->PrintMessage("Action: copy a statement/block, Click anywhere");
				pAct = new Copy(this);
				break;

			case CUT_STAT:
				pOut->PrintMessage("Action: cut a statement/block, Click anywhere");
				pAct = new Cut(this);
				break;
			case PASTE_STAT:
				pAct = new Paste(this);
				pOut->PrintMessage("Action: paste a statement/block, Click anywhere");
				break;
			case MOVE:
				pOut->PrintMessage("Action: move a statement/block or connector, Click anywhere");
				pAct = new Move(this);

				break;
			case RESIZE:
				pOut->PrintMessage("Action: resize a statement/block, Click anywhere");
				break;
			case MAIN_TOOL:
				pOut->PrintMessage("Action: a click on the Main Toolbar, Click anywhere");
				break;
			case SIM_TOOL:
				pOut->PrintMessage("Action: a click on the Simulator Toolbar, Click anywhere");
				break;
			
			case EXIT:				
				break;
		}
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//
//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

void ApplicationManager::AddConnector(Connector* pConn)
{
	if(ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;

}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL


	///Add your code here to search for a statement given a point P(x,y)	

	return NULL;
}

Statement* ApplicationManager::GetStatementByID(int id) const
{
	int found;
	//cout<<"Count "<<StatCount<<endl;
	//cout<<"Target id "<<id<<endl;
	for(int i=0;i<StatCount;i++)
	{
		//cout<<"Seacrhing id "<<StatList[i]->getID()<<endl;
		if(StatList[i]->getID()==id)
			{
				//cout<<"Found "<<endl;
				found=i;
				break;
		     }
	}
	//cout<<"Returning type "<< StatList[found]<<endl;
	return StatList[found];

}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{	pSelectedStat = pStat;	}

void ApplicationManager::DeleteStat(int Loc)
{
	delete StatList[Loc];
	for(int i = Loc; i < StatCount-1; i++)
	{
		StatList[i] = StatList[i+1];
	}
	StatList[StatCount-1] = NULL;
	StatCount--;
}

void ApplicationManager::DeleteConn(int Loc)
{
	delete ConnList[Loc];
	for(int i = Loc; i < ConnCount-1; i++)
	{
		ConnList[i] = ConnList[i+1];
	}
	ConnList[ConnCount-1] = NULL;
	ConnCount--;
}

void ApplicationManager::DeleteSelectedStat()
{
	PrintStats();
	bool checkSD = false;
	bool checkCD = false;
	LoopConnector * LC = NULL;
	Loop* LS = NULL;
	for(int i = 0; i<StatCount; i++) 
	{
		if(StatList[i]->IsSelected()==true) 
		{
			for(int j = 0; j < ConnCount; j++) 
			{
				if(ConnList[j]->getDstStat() == StatList[i])
				{ 
					LS=	NULL;
					LS = dynamic_cast <Loop*> (StatList[i]);
					if(LS==NULL)
					{
						ConnList[j]->setDstStat(NULL); 
						Point P(ConnList[j]->getStartPoint()); 
						P.y+=10;
						ConnList[j]->setEndPoint(P);
					}
					else 
					{
						if(LS->GetloopConnector() == ConnList[j])
						{ DeleteConn(j); j--; }
						else
						{
							ConnList[j]->setDstStat(NULL); 
							Point P(ConnList[j]->getStartPoint()); 
							P.y+=10;
							ConnList[j]->setEndPoint(P);
						}
					}
				}
				else if(ConnList[j]->getSrcStat() == StatList[i])
				{ 
					LC=NULL;
					LC = dynamic_cast <LoopConnector*> (ConnList[j]);
					if(LC==NULL) 
					{
						DeleteConn(j); j--; 
					}
					else
					{
						Point P(LC->getEndPoint());
						P.y+=100;
						LC->setStartPoint(P);
						LC->setSrcStat(NULL);
					}
				}
			}
			DeleteStat(i); i--;
		}
	}
}



//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
	pOut->ClearToolBar(3);
	//Draw all statements
	for(int i=0; i<StatCount; i++)
		StatList[i]->Draw(pOut);
	for(int i=0; i<StatCount; i++)
		StatList[i]->setID(i);
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
	{ ConnList[i]->Draw(pOut); } //cout << ConnList[i]->getStartPoint().x << " " <<ConnList[i]->getStartPoint().y;

}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////

//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<StatCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
	
}


////////////////////Debug Function///////////////////////////////
void ApplicationManager::PrintStats()
{
	//cout << StatCount <<endl;
	for(int i =0; i< StatCount; i++)
	{
		//cout << "X:" << StatList[i]->GetCenter().x << "Y:" << StatList[i]->GetCenter().y << endl;
	}
	//cout << "=============================================================="<<endl;
}

Statement* ApplicationManager::GetCopiedStatement() const
{
	return pCopiedStat[0];
}
void ApplicationManager::SetCopiedStatement(Statement* copystat)
{
	pCopiedStat[0] = copystat;
}

