#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "Connector.h"
//class Output;
#include "..\GUI\Output.h"
#include<fstream>
#include<iomanip>
#include<iostream>
using namespace std;
//Base class for all Statements
class Statement
{
protected:
	int ID;			//Each Statement has an ID
	string Text;	//Statement text (e.g.  "X = 5" OR "if(salary > 3000)" and so on )
	bool Selected;	//true if the statement is selected on the folwchart
	int height; //statement hieght 
	int width; //statement width 
	virtual void DeterDim() = 0; //Adjusts statment widths according to text size
	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	
	bool Connected;
	string Comment;
	Point Center;  //Important points
	Point Inlet;
	Point Outlet;
	Connector* pConn; //Connector from the statement
	//LOOPS
	Point LoopPosition;
	Connector* LoopConn;
	bool ValidPass; 
	friend class Paste;
	friend class Cut;
public:
	bool isPassed();
	void setPassed(bool);
	static window *StatWindPtr;
	Statement();
	virtual ~Statement()
	{}
    virtual bool isConnected() const;  //returns if connected
	virtual void setConnected(bool, Connector*);  //set a connection into the statement
    virtual void setConnector(Connector* pConnector); //set a connector from the statement
	virtual Connector* getConnector() const;  //returns if a connector comes from the statement
	virtual void setLoopConnector(Connector* pL);   //sets a loop connector into the statement
	virtual Point GetCenter();
	virtual Point GetDim();
	virtual Point GetOutlet();
	virtual Point GetInlet();
	void SetSelected(bool s);
	bool IsSelected() const;
	Connector * Statement::getLoopConnector() const;
	virtual Point getLoopInlet() const;
	virtual void setCenter(int,int);
	void setComment(string UserComment);
	string getComment();

	void setID(int);
	int getID() const;
	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement

	
	//void move(int x,int y);
	virtual Statement* Copy() const =0;
	virtual void disconnect()  {pConn=0;}
	///The following functions should be supported by the Statement class
	///It should be overridden by each inherited Statement
	///Decide the parameters that you should pass to each function	

	virtual bool CheckPoint(Point p)=0;

	virtual void Move(Point) = 0;		//Move the Statement on the flowchart
	/*virtual void Edit() = 0;*/		//Edit the Statement parameter

	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file


	virtual void GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file
	/*virtual void Simulate();*/	//Execute the statement in the simulation mode



	/*virtual void PrintInfo(Output* pOut) = 0;*/	//print all Statement info on the status bar
};

#endif