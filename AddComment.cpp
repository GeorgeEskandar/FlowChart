#include "AddComment.h"
#include "ApplicationManager.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Select.h"
#include "Statements\Statement.h"
#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddComment::AddComment(ApplicationManager *pAppManager):Action(pAppManager)
{
	//Clears if multi selection is set;
	Select::UnSelectAll(pAppManager);
}

void AddComment::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Add Comment : Please Choose A Statement");
	SelectedStatment = Select::getOneSelected(this->pManager);

	if(SelectedStatment!=NULL){
		pOut->PrintMessage("Add Comment : Please Enter Comment");
		this->UserComment = pIn->GetString(pOut);
		SelectedStatment->SetSelected(1);
	}	
	pOut->ClearStatusBar();		
}

void AddComment::Execute()
{
	ReadActionParameters();
	Output *pOut = pManager->GetOutput();

	if(SelectedStatment!=NULL) SelectedStatment->setComment(this->UserComment);
	else pOut->PrintMessage("You didn't choose a valid statment");
	
}

