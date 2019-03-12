#ifndef SELECT_H
#define SELECT_H

#include "Actions\Action.h"
#include "Statements\Statement.h"
#include "Statements\Connector.h"
#include "ApplicationManager.h"
//Select/Multiselect Statement Action
//This class is responsible for 
// 1 - Getting coordinates of mouse click
// 2 - Check which statment is selected
// 3 - Adding the created object to the list of Selected Statments statements

class Select : public Action
{
private:
	int num;
	Point Position;
public:
	Select(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
	static Statement * getOneSelected(ApplicationManager *pAppManager);
	static void UnSelectAll(ApplicationManager *pAppManager);
	static Connector* SelectConnector(ApplicationManager *pAppManager);

	~Select(){}
};

#endif