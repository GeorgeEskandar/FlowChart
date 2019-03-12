#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"

#include "Statements\Statement.h"
#include "Variable.h"
#include "Save.h"
class Input;
class Output;


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart
	private:
	int StatCount;		//Actual number of statements
	int ConnCount;		//Actual number of connectors
	Statement* StatList[MaxCount];	//List of all statements (Array of pointers)
	Connector* ConnList[MaxCount];	//List of all connectors (Array of pointers)
	Statement *pCopiedStat[1]; 
	Statement *pSelectedStat; //a pointer to the last selected statement
	
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

public:	
	friend class ValidateChart;
	friend class Simulate;
	friend class SimulateStepStep;
	friend class Select; // friend class to be able to access statments;
	friend class Move; // friend class to be able to access statments;
	friend class Load;
	friend class Copy;
	friend class Paste;
	friend class Cut;


	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Actions Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Statements/Connector Management Functions
	void AddStatement(Statement* pStat); //Adds a new Statement to the Flowchart
	Statement *GetStatement(Point P) const;	//search for a statement where point P belongs
	Statement* GetStatementByID(int id) const;
	void AddConnector(Connector* pConn); //Adds a new Connector to the Flowchart
	Connector *GetConnector(Point P) const;	//search for a Connector where point P belongs

	int getStatCount() {return StatCount;}
	int getConnCount() {return ConnCount;}
	Statement** getStatList() {return StatList;}
	Connector** getConnList() {return ConnList;}
	Statement *GetSelectedStatement() const;	//Returns the selected Statement
	void SetSelectedStatement(Statement *pStat); //Set the Statement selected by the user

	void DeleteSelectedStat();
	void DeleteStat(int);
	void DeleteConn(int);
	//void DeleteSelectedConn();
		
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window
	Statement *GetCopiedStatement() const;
	void SetCopiedStatement(Statement* copystat);

	////////Debug Fuctions//////////
	void PrintStats();
	
};

#endif