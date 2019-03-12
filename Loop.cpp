#include "Loop.h"
#include <sstream>
#include <iomanip>
Loop::Loop(Point Center, string LHS, string RHS, Relational op)
{
	this->LHS=LHS;
	this->RHS=RHS;
	this->op=op;
	string Operator=getOperator();
	UpdateStatementText();
	this->Center.x=Center.x;
	this->Center.y=Center.y;
	DeterDim();
	InLoop.x=Center.x-width/2;
	InLoop.y=Center.y;
	L= new LoopConnector(0,this);
	L->setEndPoint(InLoop);
	Point start;
	start.x=InLoop.x;
	start.y=InLoop.y + 100;
	L->setStartPoint(start);
}

Loop::Loop(const Loop & L2)  //George check
{
	this->RHS=L2.RHS;
	this->LHS=L2.LHS;
	this->op=L2.op;
	string Operator=getOperator();
	this->UpdateStatementText();
	this->Center=L2.Center;
	this->DeterDim();
	InLoop.x=Center.x-width/2;
	InLoop.y=Center.y;
	L= new LoopConnector(0,this);
	L->setEndPoint(InLoop);
	Point start;
	start.x=InLoop.x;
	start.y=InLoop.y + 100;
	L->setStartPoint(start);
}

string Loop::getOperator()
{
	string Operator;
	switch(op)
	{
		case EQ:
			Operator="==";
			break;
		case NOT:
			Operator="!=";
			break;
		case GRT:
			Operator=">";
			break;
		case LSS:
			Operator="<";
			break;
		case GRT_EQ:
			Operator=">=";
			break;
		case LSS_EQ:
			Operator="<=";
			break;
	}
	return Operator;
}


void Loop::UpdateStatementText()
{
	string Operator= getOperator();
	if(LHS.length()==0)
	{
		ostringstream T;
		T<<Operator;
		Text=T.str();
	}
	else
	{
		ostringstream T;
		T<<LHS<<Operator<<RHS;
		Text=T.str();
	}
	DeterDim();
}

void Loop::DeterDim()
{
		int TextWidth; int TextHeight; int buffer;
	string bufferSpace = " ";
	StatWindPtr->GetStringSize(buffer, TextHeight, bufferSpace);
	StatWindPtr->GetStringSize(TextWidth, TextHeight, Text);
	width = (width>TextWidth+5*buffer)? width: TextWidth + 8*buffer;
	if(width>UI.COND_WDTH)
		height = ceil(float(UI.COND_HI)*5*float(width/UI.COND_WDTH));
	else 
		height = UI.COND_HI;
	Inlet.x=Center.x;
	Inlet.y=Center.y-height/2;
	InLoop.x=Center.x-width/2;
	InLoop.y=Center.y;
	Outlet.x=Center.x;
	Outlet.y=Center.y+height/2;
}

/////////////////////////////////////////////////////////////////////////////////


void Loop::SetloopConnector(Connector*& Loop) 
{
	L= (LoopConnector*) Loop;
}
	
Statement* Loop::Copy() const
{
	return new Loop(*this);
}


Connector* Loop::GetloopConnector() const
{
	return L;
}	
	
Point Loop::GetloopPoint() const
{
	return InLoop;
}

void Loop::Draw(Output* pOut) const
{
	pOut->DrawLoop(Center,width,height,Text,Selected);
	L->Draw(pOut);	
}


void Loop::Save(ofstream &OutFile)  //SAVE
{
	OutFile<<"LOOP"<<setw(5)<<ID<<setw(5)<<Center.x<<setw(5)<<Center.y<<setw(5)<<LHS;
	string Operator;
	switch(op)
	{
		case EQ:
			Operator="EQL";
			break;
		case NOT:
			Operator="NEQL";
			break;
		case GRT:
			Operator="GRT";
			break;
		case LSS:
			Operator="SML";
			break;
		case GRT_EQ:
			Operator="GRT_EQL";
			break;
		case LSS_EQ:
			Operator="SML_EQL";
			break;
	}
	OutFile<<"    "<<Operator<<setw(5)<<RHS<<setw(5)<<Comment<<endl;
}

void Loop::Load(ifstream& Infile)
{
	int id;
	Infile>>id;
	setID(id);
	int x,y;
	Infile>>x;
	Infile>>y;
	setCenter(x,y);
	Infile>>LHS;
	string OP;
	Infile>>OP;
	if(OP=="EQL")
		op=EQ;
	else if(OP=="NEQL")
		op=NOT;
	else if(OP=="GRT")
		op=GRT;
	else if(OP=="SML")
		op=LSS;
	else if(OP=="GRT_EQL")
		op=GRT_EQ;
	else if(OP=="SML_EQL")
		op=LSS_EQ;
	string Operator=getOperator();
	Infile>>RHS;
	getline(Infile,Comment);
	UpdateStatementText();
	DeterDim();
	L->setEndPoint(InLoop);
	Point start;
	start.x=InLoop.x;
	start.y=InLoop.y + 100;
	L->setStartPoint(start);
}


void Loop::Move(Point P)  //MOVE
{
	this->Center.x+=P.x;
	this->Center.y+=P.y;
	DeterDim();
	L->setEndPoint(InLoop);
	if(pConn!=0)   //add this
		pConn->setStartPoint(Outlet);
	if(L->getSrcStat()==NULL)
		L->setStartPoint(Point(InLoop.x, InLoop.y + 100));
}


bool Loop::CheckPoint(Point P)
{
	//cout<<"Left<< "<<LeftCorner.x<<", "<<LeftCorner.y<<" Right<< "<<RightCorner.x<<" , "<<RightCorner.y<<endl;
	Point LeftCorner , RightCorner;
	LeftCorner.x = this->Center.x - width/2;
	LeftCorner.y = this->Center.y - height/2;

	RightCorner.x = this->Center.x + width/2;
	RightCorner.y = this->Center.y + height/2;

	//cout<<"Condition:: Left<< "<<LeftCorner.x<<", "<<LeftCorner.y<<" Right<< "<<RightCorner.x<<" , "<<RightCorner.y<<endl;
	

	if(P.x>=LeftCorner.x && P.x<=RightCorner.x && P.y>=LeftCorner.y && P.y<=RightCorner.y)
	{
		//cout<<"Inside"<<endl;
		return true;
	}
	return false;
}

void Loop::GenerateCode(ofstream &OutFile)  //GENERATE CODE
{
	OutFile<<"while("<<LHS<<op<<RHS<<")"<<endl<<"{"<<endl;

}

string Loop::getRHS()
{
	return RHS;
}
string Loop::getLHS()
{
	return LHS;
}
Relational Loop::getOp()
{
	return op;
}

void Loop::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
	DeterDim();
}

void Loop::setRHS(const string &R)
{
	RHS = R;
	UpdateStatementText();
	DeterDim();
}

void Loop::setOp(Relational OPER)
{
	op = OPER;
	UpdateStatementText();
}



