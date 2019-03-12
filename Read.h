#ifndef READ_H
#define READ_H

#include "Statements\Statement.h"

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value
class Read : public Statement
{
private:
	string LHS;	//Left Handside
	string RHS;	//Right Handside (variable name)
	

	/*Connector *pConn;*/	//Simple Assignment Stat. has one Connector to next statement

	
	Point LeftCorner,RightCorner;	//left corner of the statement block.
	//Point Center; //Center Point

	virtual void UpdateStatementText();
	virtual void DeterDim();


public:
	Read(Point center, string RightHS, string LeftHS="Read");
	Read(const Read&);
	~Read() {}
	string getRHS();
	void setLHS(const string& L = "Read");
	void setRHS(const string& R);

	virtual void Draw(Output* pOut) const;

	virtual Statement* Copy() const;

	virtual void Move(Point P);
	virtual void GenerateCode(ofstream &OutFile);
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	virtual bool CheckPoint(Point p);
	
};

#endif