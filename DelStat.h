#ifndef DEL_STAT_H
#define DEL_STAT_H

#include "Actions\Action.h"

class DelStat: public Action
{
private:
	ActionType Act;
public:
	DelStat(ApplicationManager *pAppManager);
	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
	
	~DelStat(){}
};

#endif