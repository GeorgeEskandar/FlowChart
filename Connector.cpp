#include "Connector.h"
#include "Statement.h"
#include "..\\Condition.h"
Connector::Connector(Statement* Src, Statement* Dst)	
//When a connector is created, it must have a source statement and a destination statement
//There are no free connectors in the folwchart
{
	start_selected=end_selected=false;
	SrcStat = Src;
	DstStat = Dst;
}

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint()
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}

bool Connector::isEndSelected() const
{return end_selected;}

bool Connector::isStartSelected() const
{return start_selected;}

void Connector::Draw(Output* pOut) 
{
	if(SrcStat!=0)
	{
		Condition * ptr = dynamic_cast <Condition*> (SrcStat);
		if(ptr!=NULL)
		{
			Start = ptr->GetOutlet(this);
		}
		else 
			Start = SrcStat->GetOutlet();
		if(DstStat!=NULL)
		End = DstStat->GetInlet();
	}	
	bool Selected=false;
	if(end_selected || start_selected)
		Selected=true;	
	pOut->DrawBetterArrow(Start.x,Start.y,End.x,End.y,Selected);
}


bool Connector::CheckEnd(Point& Click) const
{
	if(Click.x <= End.x + 20 && Click.x >= End.x -20 && Click.y <= End.y +20 && Click.y >= End.y -20)
		return true;
	else 
		return false;
}
bool Connector::CheckStart(Point& Click) const
{
	if(Click.x <= Start.x + 20 && Click.x >= Start.x -20 && Click.y <= Start.y +20 && Click.y >= Start.y -20)
		return true;
	else 
		return false;
}

void Connector::SetEndSelected(bool b)
{ end_selected=b; }
void Connector::SetStartSelected(bool b)
{ start_selected=b;}


void Connector::Save(ofstream& Outfile)
{
	if(SrcStat==0)
	{
		Outfile<<-1<<"     ";
	}
	else
	{
		Outfile<<SrcStat->getID()<<"     ";
	}
	if(DstStat==0)
	{
		Outfile<<-1<<"     ";
	}
	else
	{
		Outfile<<DstStat->getID()<<"      ";
	}
	Condition* pCond=dynamic_cast<Condition*>(SrcStat);
	if(pCond!=0)
	{
		if(this==pCond->getYesConnector())
			Outfile<<"1"<<endl;
		else if(this==pCond->getNoConnector())
			Outfile<<"2"<<endl;
	}
	else
		Outfile<<"0"<<endl;
}
//void Connector::Load(ifstream& Infile)
//{
//	int id1,id2,type;
//	Infile>>id1>>id2>>type;
//	if(
//}

