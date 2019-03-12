#ifndef DEFS_H
#define DEFS_H

//This file contais some global constants and definitions to be used in the project.




enum ActionType //The actions supported (you can add more if needed)
{
	ADD_SMPL_ASSIGN,//Add simple assignment statement
	ADD_VAR_ASSIGN,	//Add variable assignment statement
	ADD_COMPLEX_ASSIGN,
	ADD_CONDITION, //Add a conditional statement (for if and while-loop statements)
	ADD_READ, //Add a read statement
	ADD_WRITE, //Add a write statment
	ADD_START, //Add a start statment
	ADD_END, //Add an end statement
	ADD_COMMENT,//Add Comment
	ADD_CONNECTOR, //Add a connector between two statements
	IF_CONDITION,  //Mode of if or while
	WHILE_CONDITION,  //Comparison operator used
	EQUAL,
	NOT_EQUAL,
	GREATER_THAN,
	LESS_THAN,
	GREATER_EQUAL,
	LESS_EQUAL,

	EDIT_STAT,	//Edit a statement
	EDIT_CONN,
	CUT_STAT, //Cut a statement
	COPY_STAT, //Copy a statement 
	PASTE_STAT, //Paste a statement 

	SELECT,		//Select a statement, a connector

	DEL,		//Delete a figure(s)
	MOVE,		//Move a figure(s)
	RESIZE,		//Resize a figure(s)

	ZOOM_IN,	//Zoom in on the design
	ZOOM_OUT,	//Zoom out on the design

	SAVE,		//Save the whole graph to a file
	LOAD,		//Load a graph from a file
	EXIT,		//Exit the application
	STATUS,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar
	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to simulatiom mode
	SIM_TOOL,   //A click on an empty place in the simulation tool bar
	MAIN_TOOL,	//A click on an empty part of the Main toolbar 

	START_SIM,	//Start simulation
	STOP_SIM,	//Stop simualtion
	DEBUG_SIM,	//Debug mode
	NEXT_SIM,	//Execute next statement
	C_PP_SIM,	//Convert flowchart into c++ code
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION,
};


#ifndef NULL
#define NULL 0
#endif

#endif