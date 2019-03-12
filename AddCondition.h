#ifndef ADDCONDITION_H
#define ADDCONDITION_H

#include "Actions\Action.h"
#include "Condition.h"
#include "ApplicationManager.h"
#include<string>
class AddCondition: public Action
{
private:
	Point Position;
	string RightSide, LeftSide;
	Relational Operator;
public:
	AddCondition(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

	~AddCondition(){}
};




#endif