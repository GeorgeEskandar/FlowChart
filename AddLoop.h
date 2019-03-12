#ifndef ADDLOOP_H
#define ADDLOOP_H

#include "Actions\Action.h"
#include "Loop.h"
#include<string>
class AddLoop: public Action
{
private:
	Point Position;
	string RightSide, LeftSide;
	Relational Operator;
public:
	AddLoop(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

	~AddLoop(){}
};




#endif