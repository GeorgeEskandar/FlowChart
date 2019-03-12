#ifndef MOVE_H
#define MOVE_H

#include "Actions\Action.h"
#include "Statements\Statement.h"
#include "Select.h"
//This class is responsible for 
// 1 - Moving statements and connectors
class  Move: public Action
{
private:
	Point Position1;	//Position where the user clicks on to move from
	Point Position2;	//Position where the user clicks on to move to
	Point Final_Position; //Final Position coordinates
public:
	Move(ApplicationManager *pAppManager);

	//Read statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
	~Move(){}
};

#endif