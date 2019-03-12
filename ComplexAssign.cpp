#include "ComplexAssign.h"
#include <sstream>

using namespace std;

ComplexAssign::ComplexAssign(Point center, string LeftHS, string RightHS)
{
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	Center = center;
	DeterDim();
	
	pConn = NULL;	//No connectors yet
	
}

void ComplexAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
	DeterDim();
}

void ComplexAssign::setRHS(const string &R)
{
	RHS = R;
	UpdateStatementText();
	DeterDim();
}


void ComplexAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(Center, width, height, Text, Selected);
	
}


//This function should be called when LHS or RHS changes
void ComplexAssign::UpdateStatementText()
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


ComplexAssign::ComplexAssign(const ComplexAssign& C1)   //COPY CONSTRUCTOR
{
	this->RHS=C1.RHS;
	this->LHS=C1.LHS;
	this->UpdateStatementText();
	this->Center=C1.Center;
	this->DeterDim();
	this->pConn=NULL;
}


Statement* ComplexAssign::Copy() const
{
	return new ComplexAssign(*this); 
}

void ComplexAssign::GenerateCode(ofstream &OutFile)  //GENERATE CODE
{
	OutFile<<endl<<"double "<<this->LHS<<" = "<<this->RHS<<endl;
}


void ComplexAssign::Save(ofstream &OutFile)  //SAVE
{
	OutFile<<"SNGLOP "<<setw(5)<<ID<<setw(5)<<this->Center.x<<setw(5)<<this->Center.y<<setw(5)<<this->LHS<<setw(5);
	int i,operIndex(-1);
	char operation;
	for(i=0;i<this->RHS.size();i++)
	{
		if(this->RHS[i]=='+'||this->RHS[i]=='-'||this->RHS[i]=='/'||this->RHS[i]=='*')
		{
			operIndex = i;
			operation = this->RHS[i];
		}
	}
	if(operIndex==-1)
	{
		OutFile<<RHS<<setw(5)<<Comment<<endl;
		return;
	}

	string left=this->RHS.substr(0,operIndex);
	string right=this->RHS.substr(operIndex+1,this->RHS.size());
	
	OutFile<<left<<" ";

	if(operation=='*') OutFile<<"MUL";
	if(operation=='+') OutFile<<"ADD";
	if(operation=='/') OutFile<<"DIV";
	if(operation=='-') OutFile<<"SUB";

	OutFile<<setw(5)<<right<<setw(5)<<Comment<<endl;
}

void ComplexAssign::Load(ifstream& Infile)
{
	int id;
	Infile>>id;
	setID(id);
	int x,y;
	Infile>>x;
	Infile>>y;
	setCenter(x,y);
	Infile>>LHS;
	string left,right;
	Infile>>left;
	string OP;
	Infile>>OP;
	if(OP=="ADD")
		OP="+";
	else if(OP=="MUL")
		OP="*";
	else if(OP=="SUB")
		OP="-";
	else if(OP=="DIV")
		OP="/";
	Infile>>right;
	RHS=left+OP+right;
	getline(Infile,Comment);
	UpdateStatementText();
	DeterDim();
}

void ComplexAssign::Move(Point P)  //MOVE
{
	this->Center.x+=P.x;
	this->Center.y+=P.y;
	DeterDim();
}

bool ComplexAssign::CheckPoint(Point P)
{
	if(P.x>=this->LeftCorner.x && P.x<=this->RightCorner.x && P.y>=this->LeftCorner.y && P.y<=this->RightCorner.y)
	{
		return true;
	}
	return false;
}


void ComplexAssign::DeterDim()
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

	LoopPosition.x = Center.x- width/2;
	LoopPosition.y=Center.y;
}

//Connector* ComplexAssign::getConnector() const
//{
//	return pConn;
//}

string ComplexAssign::getRHS()
{
	return RHS;
}

string ComplexAssign::getLHS()
{
	return LHS;
}




