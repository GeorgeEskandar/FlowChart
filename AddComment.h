#ifndef ADDCOMMENT_H
#define ADDCOMMENT_H

#include "Actions\Action.h"
#include "Statements\Statement.h"
#include "Select.h"
//Add Simple Assignment Statement Action
//This class is responsible for 
// 1 - GetStatment Selected
// 2 - GetUser Comment
// 3 - AddUser Comment 
class  AddComment: public Action
{
private:
	Point Position;	//Position where the user clicks to add comment
	string UserComment;
	Statement *SelectedStatment ;
public:
	AddComment(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	~AddComment(){}
};

#endif