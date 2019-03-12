
#ifndef LOOP_H
#define LOOP_H

#include "GUI\UI_Info.h"
#include "GUI\output.h"
#include "Statements\Connector.h"
#include "Condition.h"
#include "LoopConnector.h"

class Loop: public Statement
{
private:
	string getOperator(); //Text
	string RHS,LHS;
	Relational op;

	LoopConnector* L; //Connectors and points

	Point InLoop;
	void DeterDim();
	virtual void UpdateStatementText(); 

public:
	Loop(Point Center, string LHS, string RHS, Relational);
	Loop(const Loop & L);
	~Loop() {}

	void SetloopConnector(Connector*& Loop); //setEndPoint()
	Connector* GetloopConnector() const;
	

	Point GetloopPoint() const; 

	void Draw(Output* pOut) const;

	virtual Statement* Copy() const;

	virtual void Move(Point P);

	virtual bool CheckPoint(Point p);

	virtual void GenerateCode(ofstream &OutFile);
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);

	void setRHS(const string &);
	void setLHS(const string &);
	void setOp(Relational);
	string getRHS();
	string getLHS();
	Relational getOp();
};

#endif
