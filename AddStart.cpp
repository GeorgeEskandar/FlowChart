#include "AddStart.h"

#include "ApplicationManager.h"

#include "GUI\Input.h"
#include "GUI\Output.h"


#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddStart::AddStart(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddStart::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Start Statement: Click to add the statement");
	
	bool check = false;
	while(!check)
	{
		pIn->GetPointClicked(Position);
		if(Position.y < (UI.STARTEND_HI/2 + 3*UI.TlBrWdth) || Position.y > (UI.height-UI.STARTEND_HI/2 - UI.StBrWdth))
			pOut->PrintMessage("Error, out of bounds. Please click elsewhere.");
		else 
			check = true;
	}

	//pOut->PrintMessage("Enter the name of the variable that will be read: ");
	//Text = pIn->GetString(pOut);
	Text = "Start";

	//pOut->PrintMessage("Enter extra read para: ");
	//LeftSide = pIn->GetString(pOut); Might be used later. Leave for now.

	pOut->ClearStatusBar();		
}

void AddStart::Execute()
{
	ReadActionParameters();
		
	
	//Calculating left Center of assignement statement block
	Point Center;
	Center.x = Position.x;
	Center.y = Position.y ;
	
	Start *pAssign = new Start(Center, Text);

	pManager->AddStatement(pAssign);
	pAssign->setID(pManager->getStatCount());
}

