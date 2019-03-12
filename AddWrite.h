#ifndef ADD_WRITE_H
#define ADD_WRITE_H

#include "Actions\Action.h"
#include "Write.h"

//Add Simple Assignment Statement Action
//This class is responsible for 
// 1 - Getting Read stat. coordinates from the user
// 2 - Creating an object of Read class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddWrite : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	string RightSide, LeftSide;
public:
	AddWrite(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;

	~AddWrite(){}
	
};

#endif