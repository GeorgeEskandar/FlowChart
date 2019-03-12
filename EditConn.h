#ifndef EDIT_CONN_H
#define EDIT_CONN_H

#include "Actions\Action.h"
#include "Statements\Connector.h"
#include "Connect.h"
#include "ApplicationManager.h"
#include "Select.h"

class EditConn :public Action
{
private:
	Connector* edConn;
public:
	EditConn(ApplicationManager* );
	virtual void ReadActionParameters();
	virtual void Execute();

	~EditConn(){}
};

#endif