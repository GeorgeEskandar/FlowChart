#include"Condition.h"
#include<iomanip>
#include<iostream>
#include <sstream>

//Private Functions


void Condition::UpdateStatementText()
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

void Condition::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
	DeterDim();
}

void Condition::setRHS(const string &R)
{
	RHS = R;
	UpdateStatementText();
	DeterDim();
}

void Condition::setOp(Relational OPER)
{
	op = OPER;
	UpdateStatementText();
}

string Condition::getOperator()
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
//////////////////////////////////////////////////////////////////////////////////////////
Condition::Condition(Point center, string LHS, string RHS,Relational op)     //CONSTRUCTOR
{
	this->LHS=LHS;
	this->RHS=RHS;
	this->op=op;
	string Operator=getOperator();
	Center.x=center.x;
	Center.y=center.y;
	UpdateStatementText();
	DeterDim();
	yes= new Connector(this,0);   //initialize yes and no connectors
	no= new Connector(this,0);
	yes->setStartPoint(yes_outlet);
	no->setStartPoint(no_outlet);
	Point yes_end;
	yes_end.x=yes_outlet.x -30;
	yes_end.y= yes_outlet.y + 30;
	yes->setEndPoint(yes_end);
	Point no_end;
	no_end.x=no_outlet.x +30;
	no_end.y= no_outlet.y + 30;
	no->setEndPoint(no_end);
	pConn=0;
}

Condition::Condition(const Condition& C2)   //COPY CONSTRUCTOR
{
	this->RHS=C2.RHS;
	this->LHS=C2.LHS;
	this->op=C2.op;
	string Operator=getOperator();
	this->UpdateStatementText();
	this->Center=C2.Center;
	this->DeterDim();
	yes= new Connector(this,0);   //initialize yes and no connectors
	no= new Connector(this,0);
	yes->setStartPoint(yes_outlet);
	Point yes_end;
	yes_end.x=yes_outlet.x -20;
	yes_end.y= yes_outlet.y + 20;
	yes->setEndPoint(yes_end);
	/////////////
	no->setStartPoint(no_outlet);
	Point no_end;
	no_end.x=no_outlet.x -20;
	no_end.y= no_outlet.y + 20;
	no->setEndPoint(no_end);
	
}
////////////////////////////////////////////////////////////////////
Connector* Condition::getYesConnector() const
{
	return yes;
}
Connector* Condition::getNoConnector() const
{
	return no;
}
/////////////////////////////////////////////////////////////////////
Statement* Condition::Copy() const  //COPY
{ return new Condition(*this); }

void Condition::GenerateCode(ofstream &OutFile)  //GENERATE CODE
{
	OutFile<<"if("<<LHS<<op<<RHS<<")"<<endl<<"{"<<endl;

}
void Condition::Save(ofstream &OutFile)  //SAVE
{
	OutFile<<"COND"<<setw(5)<<ID<<setw(5)<<Center.x<<setw(5)<<Center.y<<setw(5)<<LHS<<"    ";
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
	OutFile<<Operator<<setw(5)<<RHS<<setw(5)<<Comment<<endl;
}

void Condition::Load(ifstream& Infile)
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
	//Infile.ignore(5);
	Infile>>RHS;
	Text=LHS+Operator+RHS;
	//Infile.ignore(5);
	getline(Infile,Comment);
	UpdateStatementText();
	DeterDim();
		yes->setStartPoint(yes_outlet);
	no->setStartPoint(no_outlet);
	Point yes_end;
	yes_end.x=yes_outlet.x -30;
	yes_end.y= yes_outlet.y + 30;
	yes->setEndPoint(yes_end);
	Point no_end;
	no_end.x=no_outlet.x +30;
	no_end.y= no_outlet.y + 30;
	no->setEndPoint(no_end);
}



void Condition::Draw(Output* pOut) const  //DRAW
{
	pOut->DrawDecision(Center, width, height, Text,this->Selected);
}

void Condition::Move(Point P)  //MOVE
{
	this->Center.x+=P.x;
	this->Center.y+=P.y;
	DeterDim();
	yes->setStartPoint(yes_outlet);
	no->setEndPoint(no_outlet);
}

bool Condition::CheckPoint(Point P)
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
//void Condition::PrintInfo(Output* pOut) const
//{
//
//}

//void Condition::Edit()
//{
//
//}

void Condition::DeterDim()
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
	yes_outlet.y=Center.y ;
	yes_outlet.x=Center.x -width/2;
	no_outlet.x=Center.x+width/2;
	no_outlet.y=Center.y;
	Inlet.x=Center.x;
	Inlet.y=Center.y-height/2;
	LoopPosition.x=Center.x;
	LoopPosition.y=Center.y-height/2;
}


void Condition::setConnector(Connector* pConnector)
{
	return;
}

string Condition::getRHS()
{
	return RHS;
}
string Condition::getLHS()
{
	return LHS;
}
Relational Condition::getOp()
{
	return op;
}

Point Condition::GetOutlet(Connector * p)
{
	if(p == yes)
	{
		return yes_outlet;
	}
	else if(p == no)
	{
		return no_outlet;
	}
}

Point Condition::GetYesOut() const
{
	return yes_outlet;
}

Point Condition::GetNoOut() const
{
	return no_outlet;
}