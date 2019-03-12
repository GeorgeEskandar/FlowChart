#ifndef COMPLEXASSIGN_H
#define COMPLEXASSIGN_H

#include "Statements\Statement.h"

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value
class ComplexAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS;	//Right Handside (Expression)
	
	/*Connector *pConn;*/	//Complex Assignment Stat. has one Connector to next statement

	Point LeftCorner,RightCorner;	//left corner of the statement block.
	//Point Center; //Center Point
	virtual void UpdateStatementText();
	virtual void DeterDim();
	
public:
	string getRHS();
	string getLHS();

	ComplexAssign(Point center, string LeftHS="", string RightHS="");
	ComplexAssign(const ComplexAssign&);
	~ComplexAssign() {}


	void setLHS(const string &L);
	void setRHS(const string &R);

	virtual void Draw(Output* pOut) const;
	virtual bool CheckPoint(Point);
	
	virtual Statement* Copy() const;

	virtual void Move(Point);
	virtual void GenerateCode(ofstream &OutFile);
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
};

#endif