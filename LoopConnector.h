#ifndef LOOPCONNECTOR_H
#define LOOPCONNECTOR_H

#include "Statements\Connector.h"
#include "Statements\Statement.h"
#include "GUI\Output.h"

class LoopConnector: public Connector
{
public:
	LoopConnector(Statement* Src, Statement* Dst);
	~LoopConnector() {}
	virtual void Draw(Output* pOut) ;
	virtual void Save(ofstream& Outfile);
	//virtual void Load(ifstream& Infile);

};


#endif