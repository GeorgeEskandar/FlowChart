#include "Start.h"
#include <sstream>
#include <iostream>

using namespace std;

Start::Start(Point center, string text)
{
	SetStartText(text);

	Center = center;

	DeterDim();

	pConn = NULL;	//No connectors yet
	Connected=false;
}

void Start::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 

	pOut->DrawStartEnd(Center, width , height, Text, Selected);
	
}

void Start::SetStartText(string text)
{
	Text = text;
	DeterDim();
}




Start::Start(const Start& C1)   //COPY CONSTRUCTOR
{
	this->Text = C1.Text;
	this->SetStartText(C1.Text);
	this->Center=C1.Center;
	this->DeterDim();
	this->pConn=NULL;
	Connected=false;
}

Statement* Start::Copy() const
{
	return new Start(*this); 
}

void Start::GenerateCode(ofstream &OutFile) 
{
	OutFile<<endl<<"int main()" << endl << "{" << endl;
}

void Start::Save(ofstream &OutFile) 
{
	OutFile<<"STRT "<<setw(5)<<ID<<setw(5)<<this->Center.x<<setw(5)<<this->Center.y<<setw(5)<<Comment<<endl;
}

void Start::Load(ifstream& Infile)
{
	Infile.ignore(5);
	int id;
	Infile>>id;
	setID(id);
	int x,y;
	Infile>>x;
	Infile>>y;
	setCenter(x,y);
	getline(Infile,Comment);
	UpdateStatementText();
	DeterDim();
}

void Start::Move(Point P)  
{
	this->Center.x+=P.x;
	this->Center.y+=P.y;
	DeterDim();
}

bool Start::CheckPoint(Point P)
{
	//cout<<"Left<< "<<LeftCorner.x<<", "<<LeftCorner.y<<" Right<< "<<RightCorner.x<<" , "<<RightCorner.y<<endl;
	if(P.x>=this->LeftCorner.x && P.x<=this->RightCorner.x && P.y>=this->LeftCorner.y && P.y<=this->RightCorner.y)
	{
		return true;
	}
	return false;
}

void Start::DeterDim()
{
	width = UI.STARTEND_WDTH;
	int TextWidth; int TextHeight; int buffer;
	string bufferSpace = " ";
	StatWindPtr->GetStringSize(buffer, TextHeight, bufferSpace);
	StatWindPtr->GetStringSize(TextWidth, TextHeight, Text);
	width = (width>TextWidth+2*buffer)? width: TextWidth + 5*buffer;
	height = UI.STARTEND_HI;


	LeftCorner.x = Center.x - width/2;
	LeftCorner.y = Center.y - height/2;
	RightCorner.x = LeftCorner.x + width ;
	RightCorner.y = LeftCorner.y + height;

	Outlet.x = LeftCorner.x + width /2;
	Outlet.y = LeftCorner.y + height;

	
}

void Start::setLoopConnector(Connector* pL)
{
	return;
}


void Start::setConnected(bool b, Connector* pC)
{
	Statement::setConnected(false,pC);
}

string Start::getText()
{
	return Text;
}
