#include "End.h"
#include <sstream>
#include <iostream>

using namespace std;

End::End(Point center, string text)
{
	SetEndText(text);
	pConn=0;
	Center = center;

	DeterDim();
}

void End::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 

	pOut->DrawStartEnd(Center, width , height, Text, Selected);
	
}

void End::SetEndText(string text)
{
	Text = text;
	DeterDim();
}

End::End(const End& C1)   //COPY CONSTRUCTOR
{
	this->Text = C1.Text;
	this->SetEndText(C1.Text);
	this->Center=C1.Center;
	this->DeterDim();
}

Statement* End::Copy() const
{
	return new End(*this); 
}

void End::GenerateCode(ofstream &OutFile) 
{
	OutFile<<endl<<"return 0" << endl << "}" << endl;
}

void End::Save(ofstream &OutFile) 
{
	OutFile<<"END "<<setw(5)<<ID<<setw(5)<<this->Center.x<<setw(5)<<this->Center.y<<setw(5)<<Comment<<endl;
}

void End::Load(ifstream& Infile)
{
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

void End::Move(Point P)  
{
	this->Center.x+=P.x;
	this->Center.y+=P.y;
	DeterDim();
}

bool End::CheckPoint(Point P)
{
	//cout<<"Left<< "<<LeftCorner.x<<", "<<LeftCorner.y<<" Right<< "<<RightCorner.x<<" , "<<RightCorner.y<<endl;
	if(P.x>=this->LeftCorner.x && P.x<=this->RightCorner.x && P.y>=this->LeftCorner.y && P.y<=this->RightCorner.y)
	{
		return true;
	}
	return false;
}

void End::DeterDim()
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

	Inlet.x = LeftCorner.x + width /2;
	Inlet.y = LeftCorner.y;

	LoopPosition.x = Center.x - width/2;
	LoopPosition.y=Center.y;
}





 void End::setConnector(Connector* pConnector)
 {return;}