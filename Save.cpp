#include"Save.h"

Save::Save(ApplicationManager* pApp)
	:Action(pApp)
{}

void Save::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Save: click to write directory of destination file");
	Point P;
	pIn->GetPointClicked(P);
	pOut->ClearStatusBar();
	string address;
	pIn->GetString(pOut);
	Outfile.open(address);
	if(!Outfile)
		Outfile.open("Save_Default.txt");
	pOut->ClearStatusBar();
}

void Save::Execute()
{
	ReadActionParameters();
	Outfile<<pManager->getStatCount()<<endl;
	for(int i=0; i<pManager->getStatCount();i++)
	{
		pManager->getStatList()[i]->Save(Outfile);
	}
	Outfile<<pManager->getConnCount()<<endl;
	for(int i=0; i<pManager->getConnCount();i++)
	{
		pManager->getConnList()[i]->Save(Outfile);
	}
	Outfile.close();
}