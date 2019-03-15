#include "SmplAssign.h"
#include <sstream>
#include <iostream>

using namespace std;

SmplAssign::SmplAssign(Point center, string LeftHS, double RightHS)
{
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	Center = center;

	DeterDim();
	Inlet.x = LeftCorner.x + width /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + height;
	pConn = NULL;	//No connectors yet
	
	
}

void SmplAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
	DeterDim();
}

void SmplAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
	DeterDim();
}


void SmplAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 

	pOut->DrawAssign(Center, width , height, Text, Selected);
	
}


//This function should be called when LHS or RHS changes
void SmplAssign::UpdateStatementText()
{
	if(LHS=="")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T<<LHS<<" = "<<RHS;	
		Text = T.str();	 
	}
}


SmplAssign::SmplAssign(const SmplAssign& C1)   //COPY CONSTRUCTOR
{
	this->RHS=C1.RHS;
	this->LHS=C1.LHS;
	this->UpdateStatementText();
	this->Center=C1.Center;
	this->DeterDim();
	this->pConn=NULL;
}

Statement* SmplAssign::Copy() const
{
	return new SmplAssign(*this); 
}

void SmplAssign::GenerateCode(ofstream &OutFile)  //GENERATE CODE
{
	OutFile<<endl<<"double "<<this->LHS<<" = "<<this->RHS<<endl;
}

void SmplAssign::Save(ofstream &OutFile)  //SAVE
{
	OutFile<<"SMPLASSIGN "<<setw(5)<<ID<<setw(5)<<this->Center.x<<setw(5)<<this->Center.y<<setw(5)<<this->LHS<<setw(5)<<this->RHS<<setw(5)<<Comment<<endl;
}


void SmplAssign::Load(ifstream &Infile)  //LOAD
{
	int id;
	Infile>>id;
	setID(id);
	int x,y;
	Infile>>x;
	Infile>>y;
	setCenter(x,y);
	Infile>>LHS;
	Infile>>RHS;
	getline(Infile,Comment);
	UpdateStatementText();
	DeterDim();
}

void SmplAssign::Move(Point P)  //MOVE
{
	this->Center.x+=P.x;
	this->Center.y+=P.y;
	DeterDim();
}

bool SmplAssign::CheckPoint(Point P)
{
	//cout<<"Left<< "<<LeftCorner.x<<", "<<LeftCorner.y<<" Right<< "<<RightCorner.x<<" , "<<RightCorner.y<<endl;
	if(P.x>=this->LeftCorner.x && P.x<=this->RightCorner.x && P.y>=this->LeftCorner.y && P.y<=this->RightCorner.y)
	{
		return true;
	}
	return false;
}

void SmplAssign::DeterDim()
{
	width = UI.ASSGN_WDTH;
	int TextWidth; int TextHeight; int buffer;
	string bufferSpace = " ";
	StatWindPtr->GetStringSize(buffer, TextHeight, bufferSpace);
	StatWindPtr->GetStringSize(TextWidth, TextHeight, Text);
	width = (width>TextWidth+2*buffer)? width: TextWidth + 5*buffer;
	
	height = UI.ASSGN_HI;

	LeftCorner.x = Center.x - width/2;
	LeftCorner.y = Center.y - height/2;
	RightCorner.x = LeftCorner.x + width ;
	RightCorner.y = LeftCorner.y + height;

	Inlet.x = LeftCorner.x + width /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + height;
	//cout<<"Out Let "<<Outlet.x<<" , "<<Outlet.y<<endl; 
	LoopPosition.x=Center.x-width/2;
	LoopPosition.y=Center.y;
}

double SmplAssign::getRHS()
{
	return RHS;
}

string SmplAssign::getLHS()
{
	return LHS;
}
