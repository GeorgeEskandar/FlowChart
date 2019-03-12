#ifndef CUT_H
#define CUT_H

#include "Actions\Action.h"
#include "Statements\Statement.h"
#include "Select.h"

class  Cut: public Action
{
private:
	
	Statement* Stat;  //Pointer to the current statement
	

public:
	Cut(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	
	
	virtual void Execute() ;
	
};

#endif
