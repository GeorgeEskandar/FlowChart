#ifndef CONDITION_H
#define CONDITION_H

#include"Statements\Statement.h"
#include "Statements\Connector.h"
enum Relational
{
	EQ,
	NOT,
	GRT,
	LSS,
	GRT_EQ,
	LSS_EQ,
};

class Condition: public Statement
{
public:
	//CONSTRUCTORS
	Condition(Point Center, string LHS, string RHS, Relational); 
	Condition(const Condition& );
	~Condition() {}

	//ACTIONS
	virtual void Draw(Output* pOut) const;
	virtual Statement* Copy() const;
	virtual void GenerateCode(ofstream &OutFile);
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	virtual void Move(Point);
	virtual bool CheckPoint(Point p);
	//SET CONNECTIONS
	virtual void setConnector(Connector* pConnector);
	Connector* getYesConnector() const;
	Connector* getNoConnector() const;
	
	
	Point GetOutlet(Connector*);

	string getRHS();
	string getLHS();
	void setRHS(const string &);
	void setLHS(const string &);
	Relational getOp();
	void setOp(Relational);
	Point GetYesOut() const;
	Point GetNoOut() const;
protected:
	//CONNECTORS
	Connector* yes;
	Connector* no;
	//POINTS
	//Point Center;
	Point yes_outlet;
	Point no_outlet;
	//EXPRESSION
	string LHS;
	string RHS;
	Relational op;
	virtual void UpdateStatementText(); 
	virtual void DeterDim();
	string getOperator();  //convert op(enum) to string
};

#endif