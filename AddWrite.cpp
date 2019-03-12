#include "AddWrite.h"

#include "ApplicationManager.h"

#include "GUI\Input.h"
#include "GUI\Output.h"


#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddWrite::AddWrite(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddWrite::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Write Statement: Click to add the statement");
	
	bool check = false;
	while(!check)
	{
		pIn->GetPointClicked(Position);
		if(Position.y < (UI.READ_HEIGHT/2 + 3*UI.TlBrWdth) || Position.y > (UI.height-UI.READ_HEIGHT/2  - UI.StBrWdth))
			pOut->PrintMessage("Error, out of bounds. Please click elsewhere.");
		else 
			check = true;
	}

	pOut->PrintMessage("Enter the name of the variable that will be written: ");
	RightSide = pIn->GetString(pOut);

	//pOut->PrintMessage("Enter extra write para: ");
	//LeftSide = pIn->GetString(pOut); Might be used later. Leave for now.

	pOut->ClearStatusBar();		
}

void AddWrite::Execute()
{
	ReadActionParameters();
		

	Point Center;
	Center.x = Position.x;
	Center.y = Position.y ;
	
	Write *pAssign = new Write(Center, RightSide);

	pManager->AddStatement(pAssign);
	pAssign->setID(pManager->getStatCount());
}

