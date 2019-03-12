#ifndef CONNECT_H
#define CONNECT_H

#include "Actions\Action.h"
#include "ApplicationManager.h"
#include "Statements\Statement.h"

class Connect:public Action
{
public:
	Connect(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
private:
	Statement* Source;
	Statement* Destination;

	~Connect(){}
};






#endif