#ifndef End_H
#define End_H

#include "Statements\Statement.h"

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value
class End : public Statement
{
private:
	//No connectors. Can't be a source.
		//A point a connection leaves this End

	Point LeftCorner,RightCorner;	//left corner and right corners of the End block.
	//Point Center; //Center Point
	virtual void UpdateStatementText() {}
	virtual void DeterDim();


public:
	End(Point center, string = "End");
	End(const End&);
	~End() {}

	virtual void SetEndText(string = "End");

	virtual void Draw(Output* pOut) const;

	virtual Statement* Copy() const;

	virtual void Move(Point);
	virtual void GenerateCode(ofstream &OutFile);
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	virtual bool CheckPoint(Point p);
	virtual void setConnector(Connector* pConnector);
};

#endif