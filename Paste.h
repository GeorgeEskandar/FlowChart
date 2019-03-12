
#ifndef PASTE_H
#define PASTE_H

#include "Actions\Action.h"
#include "Statements\Statement.h"
#include "Select.h"
//This class is responsible for 
// 1 - Moving statements and connectors
class  Paste: public Action
{
private:
	Point Position;	//Position where you want to paste
	
	

public:
	Paste(ApplicationManager *pAppManager);

	//Read statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif
