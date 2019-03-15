#include "Statement.h"

window* Statement::StatWindPtr;

Statement::Statement()	
{ 
	pConn=0;
	LoopConn=0;
	Text = "";
	Selected = false;
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

void Statement::setID(int id)
{ ID=id;}

void Statement::setConnected(bool b, Connector*pc)
{
	Connected = b;
	if(b)
		pc->setEndPoint(Inlet);
}

void Statement::setCenter(int x,int y)
{
	Center.x=x;
	Center.y=y;
}

bool Statement::isConnected() const
{
	return Connected;
}

void Statement::setComment(string userComment)
{
	this->Comment = userComment;
}

string Statement::getComment()
{
	return this->Comment;
}

void Statement::Move(Point P)
{
	this->Center.x+=P.x;
	this->Center.y+=P.y;
	DeterDim();
}
//
Connector* Statement::getConnector() const
{
	return pConn;
}

void Statement::setLoopConnector(Connector*pL)
{
	if(pL!=0)
	{
		pL->setStartPoint(LoopPosition);
		pL->setSrcStat(this);
	}
	LoopConn=pL;
}

void Statement::setConnector(Connector* pC)
{
	if(pC!=0)
		pC->setStartPoint(Outlet);
	pConn=pC;
}

Point Statement::GetCenter()
{
	return Center;
}

Connector * Statement::getLoopConnector() const
{
	return LoopConn;
}

Point Statement::GetDim()
{
	return Point(width, height);
}

Point Statement::GetOutlet()
{
	return Outlet;
}

Point Statement::GetInlet()
{
	return Inlet;
}

int Statement::getID() const
{return ID;}

Point Statement::getLoopInlet() const
{ 
	return LoopPosition;
}

bool Statement::isPassed()
{
	return ValidPass;
}
void Statement::setPassed(bool B)
{
	ValidPass = B;
}