#include "LoopConnector.h"


void LoopConnector::Draw(Output* pOut) 
{
	if(SrcStat!=NULL)
		Start=SrcStat->getLoopInlet();   
	bool Selected=false;
	if(end_selected || start_selected)
		Selected=true;
	pOut->DrawLoopArrow(Start.x, Start.y, End.x,End.y,Selected);
}

LoopConnector::LoopConnector(Statement* Src, Statement* Dst)
	:Connector(Src,  Dst)
{}

void LoopConnector::Save(ofstream& Outfile)
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
	Outfile<<"3"<<endl;
}
