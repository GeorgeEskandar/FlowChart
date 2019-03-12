#include "Write.h"
#include <sstream>
#include <iostream>

using namespace std;

Write::Write(Point center, string RightHS, string LeftHS)
{
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	Center = center;

	DeterDim();

	pConn = NULL;	//No connectors yet
	
}

void Write::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
	DeterDim();
}

void Write::setRHS(const string& R)
{
	RHS = R;
	UpdateStatementText();
	DeterDim();
}


void Write::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 

	pOut->DrawWriteSt(Center, width , height, Text, Selected);
	
}


//This function should be called when LHS or RHS changes
void Write::UpdateStatementText()
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
	Text = " " + Text + " ";
}


Write::Write(const Write& C1)   //COPY CONSTRUCTOR
{
	this->RHS=C1.RHS;
	this->LHS=C1.LHS;
	this->UpdateStatementText();
	this->Center=C1.Center;
	this->DeterDim();
	this->pConn=NULL;
}

Statement* Write::Copy() const
{
	return new Write(*this); 
}

void Write::GenerateCode(ofstream &OutFile)  //GENERATE CODE
{
	OutFile<<endl<<"cout<<"<< "RHS"; //have to see out RHS value not name. 
}

void Write::Save(ofstream &OutFile)  //SAVE
{
	OutFile<<"WRITE "<<setw(5)<<ID<<setw(5)<<this->Center.x<<setw(5)<<this->Center.y<<setw(5)<<this->RHS<<setw(5)<<Comment<<endl;
}


void Write::Load(ifstream& Infile)
{
	int id;
	Infile>>id;
	setID(id);
	int x,y;
	Infile>>x;
	Infile>>y;
	setCenter(x,y);
	Infile>>RHS;
	LHS="Write";
	getline(Infile,Comment);
	UpdateStatementText();
	DeterDim();
}


void Write::Move(Point P)  //MOVE
{
	this->Center.x+=P.x;
	this->Center.y+=P.y;
	DeterDim();
}

bool Write::CheckPoint(Point P)
{
	if(P.x>=this->LeftCorner.x && P.x<=this->RightCorner.x && P.y>=this->LeftCorner.y && P.y<=this->RightCorner.y)
	{
		return true;
	}
	return false;
}

void Write::DeterDim()
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


//Connector* Write::getConnector() const
//{ return pConn;}

string Write::getRHS()
{
	return RHS;
}
