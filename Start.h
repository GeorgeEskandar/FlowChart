#ifndef START_H
#define START_H

#include "Statements\Statement.h"

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value
class Start : public Statement
{
private:
	/*Connector *pConn;*/	//Simple Assignment Stat. has one Connector to next statement
		//A point a connection leaves this Start

	Point LeftCorner,RightCorner;	//left corner and right corners of the start block.
	//Point Center; //Center Point
	virtual void UpdateStatementText() {}
	virtual void DeterDim();


public:
	Start(Point center, string = "Start");
	Start(const Start&);
	~Start(){}
	virtual void SetStartText(string = "Start");

	virtual void setLoopConnector(Connector* pL);
	virtual void Draw(Output* pOut) const;
	/*Connector* getConnector() const;*/
	virtual void setConnected(bool , Connector* pC);
	virtual Statement* Copy() const;

	virtual void Move(Point);
	virtual void GenerateCode(ofstream &OutFile);
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	virtual bool CheckPoint(Point p);
	string getText();
};

#endif