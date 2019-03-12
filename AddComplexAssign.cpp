#include "AddComplexAssign.h"

#include "ApplicationManager.h"

#include "GUI\Input.h"
#include "GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddComplexAssign::AddComplexAssign(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddComplexAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Complex Assignment Statement: Click to add the statement");
	
	
	bool check = false;
	while(!check)
	{
		pIn->GetPointClicked(Position);
		if(Position.y < (UI.ASSGN_HI/2 + 3*UI.TlBrWdth) || Position.y > (UI.height-UI.ASSGN_HI/2 - UI.StBrWdth))
			pOut->PrintMessage("Error, out of bounds. Please click elsewhere.");
		else 
			check = true;
	}

	pOut->PrintMessage("Enter Variable Name: ");
	LeftSide = pIn->GetString(pOut);

	pOut->PrintMessage("Enter Expression: ");
	RightSide = pIn->GetString(pOut);

	pOut->ClearStatusBar();		
}

void AddComplexAssign::Execute()
{
	ReadActionParameters();
		
	
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x;
	Corner.y = Position.y;
	
	ComplexAssign *pAssign = new ComplexAssign(Corner, LeftSide, RightSide);
	
	pManager->AddStatement(pAssign);
	pAssign->setID(pManager->getStatCount());
}


