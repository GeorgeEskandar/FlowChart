#include "Read.h"
#include <sstream>
#include <iostream>

using namespace std;

Read::Read(Point center, string RightHS, string LeftHS)
{
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	Center = center;

	DeterDim();

	pConn = NULL;	//No connectors yet
	
}

void Read::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
	DeterDim();
}

void Read::setRHS(const string& R)
{
	RHS = R;
	UpdateStatementText();
	DeterDim();
}


void Read::Draw(Output* pOut) const
{
	pOut->DrawReadSt(Center, width , height, Text, Selected);
	
}


//This function should be called when LHS or RHS changes
void Read::UpdateStatementText()
{
	if(RHS=="")	//No left handside ==>statement has no valid text yet
		Text = LHS+ "     ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T<<LHS <<" "<<RHS;	
		Text = T.str();	 
	}
	Text=' '+Text+' ';
}


Read::Read(const Read& C1)   //COPY CONSTRUCTOR
{
	this->RHS=C1.RHS;
	this->LHS=C1.LHS;
	this->UpdateStatementText();
	this->Center=C1.Center;
	this->DeterDim();
	this->pConn=NULL;
}

Statement* Read::Copy() const
{
	return new Read(*this); 
}

void Read::GenerateCode(ofstream &OutFile)  //GENERATE CODE
{
	OutFile<<endl<<"cin>>"<< "RHS";
}

void Read::Save(ofstream &OutFile)  //SAVE
{
	OutFile<<"READ "<<setw(5)<<ID<<setw(5)<<this->Center.x<<setw(5)<<this->Center.y<<setw(5)<<this->RHS<<setw(5)<<Comment<<endl;
}


void Read::Load(ifstream& Infile)
{
	int id;
	Infile>>id;
	setID(id);
	int x,y;
	Infile>>x;
	Infile>>y;
	setCenter(x,y);
	Infile>>RHS;
	LHS="Read";
	getline(Infile,Comment);
	UpdateStatementText();
	DeterDim();
}

void Read::Move(Point P)  //MOVE
{
	this->Center.x+=P.x;
	this->Center.y+=P.y;
	UpdateStatementText();
	DeterDim();
}

bool Read::CheckPoint(Point P)
{
	if(P.x>=this->LeftCorner.x && P.x<=this->RightCorner.x && P.y>=this->LeftCorner.y && P.y<=this->RightCorner.y)
	{
		return true;
	}
	return false;
}

void Read::DeterDim()
{
	width = UI.READ_WIDTH;
	int TextWidth; int TextHeight; 
	StatWindPtr->GetStringSize(TextWidth, TextHeight, Text);
	width = (width>TextWidth)? width: TextWidth + UI.READ_WIDTH/10;
	height = UI.READ_HEIGHT;

	LeftCorner.x = Center.x - width/2 - 10;
	LeftCorner.y = Center.y - height/2;
	RightCorner.x = LeftCorner.x + width + 10;
	RightCorner.y = LeftCorner.y + height;

	Inlet.x = Center.x;
	Inlet.y = Center.y - height/2;

	Outlet.x = Inlet.x;
	Outlet.y = Center.y + height/2;
	LoopPosition.x=Center.x-width/2;
	LoopPosition.y=Center.y;
}

string Read::getRHS()
{
	return RHS;
}

