#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "..\GUI\UI_Info.h"
#include "..\GUI\output.h"
#include<fstream>
#include<iomanip>
#include<iostream>
using namespace std;

class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
protected:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	bool end_selected; 
	bool start_selected;
	
public:
	
	Connector(Statement* Src, Statement* Dst);
	virtual ~Connector(){}

	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();

	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	bool isEndSelected() const;
	bool isStartSelected() const;

	void SetEndSelected(bool b);
	void SetStartSelected(bool b);

	bool CheckEnd(Point& Click) const;
	bool CheckStart(Point& Click) const;

	virtual void Draw(Output* pOut);

	virtual void Save(ofstream& Outfile);
	//virtual void Load(ifstream& Infile);
	
};

#endif