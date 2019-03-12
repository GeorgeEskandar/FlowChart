#ifndef COPY_H
#define COPY_H

#include "Actions\Action.h"
#include "Statements\Statement.h"
#include "Select.h"

class  Copy: public Action
{
private:
	
	Statement* Stat;  //Pointer to the current statement
	

public:
	Copy(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	
	
	virtual void Execute() ;
	
};

#endif
