#ifndef SMPL_ASSIGN_H
#define SMPL_ASSIGN_H

#include "Statement.h"

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value
class SmplAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)
	

	/*Connector *pConn;*/	//Simple Assignment Stat. has one Connector to next statement

	
	Point LeftCorner,RightCorner;	//left corner of the statement block.
	//Point Center; //Center Point

	virtual void UpdateStatementText();
	virtual void DeterDim();


public:
	~SmplAssign() {}
	SmplAssign(Point center, string LeftHS="", double RightHS=0);
	SmplAssign(const SmplAssign&);
	
	void setLHS(const string &L);
	void setRHS(double R);

	virtual void Draw(Output* pOut) const;
	virtual Statement* Copy() const;

	double getRHS();
	string getLHS();

	virtual void Move(Point P);
	virtual void GenerateCode(ofstream &OutFile);
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	virtual bool CheckPoint(Point p);

};

#endif