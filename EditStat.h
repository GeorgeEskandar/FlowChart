#ifndef EDIT_STAT_H
#define EDIT_STAT_H

#include "Actions\Action.h"
#include "Statements\Statement.h"
#include "Connect.h"
#include "ApplicationManager.h"
#include "Select.h"

class EditStat :public Action
{
private:
	Statement* Statarr;
public:
	EditStat(ApplicationManager* );
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif
