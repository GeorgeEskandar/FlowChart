#include "EditConn.h"
#include "Condition.h"
#include "End.h"
#include "Loop.h"
EditConn::EditConn(ApplicationManager* pApp)
	:Action(pApp)
{}
void EditConn::ReadActionParameters()
{
	Point P;
	pManager->GetOutput()->PrintMessage("Edit Connector, Click on a start or end point");
	edConn=Select::SelectConnector(pManager);
	pManager->GetOutput()->ClearStatusBar();
}

 void EditConn::Execute()
 {
	 Point P;
	 ReadActionParameters();
	 if(edConn==0)
		 return;
	 if(edConn->isEndSelected())
	 {
		 edConn->SetStartSelected(false); //reset selected flags to false
		 edConn->SetEndSelected(false);
		 pManager->GetOutput()->PrintMessage("End point selected, select new destination");
         Statement* dest=Select::getOneSelected(pManager); //select new destination statement
	 	 pManager->GetOutput()->ClearStatusBar();
		  if(dest==0)  //check if new destination exists 
			  return;
		  LoopConnector* pL= dynamic_cast<LoopConnector*>(edConn);  //check if it's a loop connector
		  if(pL!=0)
		  {
			  pManager->GetOutput()->PrintMessage("Cannot change the location of the endpoint of this connector");
			  return;
		  }
		   if(dest==edConn->getSrcStat()) //checks if the new destination is the same as the source 
		  {
			  pManager->GetOutput()->PrintMessage("new destination and source are the same");
			  return;
		  }
		  if(edConn->getDstStat()!=0)
			  edConn->getDstStat()->setConnected(false,edConn);  //old destination is now not connected
		  dest->setConnected(true,edConn);  //new destination is now connected
		  edConn->setDstStat(dest);  //connector now has a pointer to the new destination statement
	 }
	 else if(edConn->isStartSelected())
	 {
		  edConn->SetStartSelected(false);    //reset selected flags to false
		  edConn->SetEndSelected(false);
		  pManager->GetOutput()->PrintMessage("Start point selected, select new destination");
          Statement* Source=Select::getOneSelected(pManager);  //select new destination statement
	 	  pManager->GetOutput()->ClearStatusBar();
		  if(Source==0)   //check if new destination exists 
			  return;
		  Condition* pCond= dynamic_cast<Condition*>(edConn->getSrcStat());  //check if it is a condition
		  if(pCond!=0)
		  {
			  pManager->GetOutput()->PrintMessage("Cannot change the location of the start point of this connector");
			  return;
		  }

		  Loop* pLoop= dynamic_cast<Loop*>(edConn->getDstStat());  //check if it is a loop
		  if(pLoop!=0)
		  {
			  edConn= (LoopConnector*) edConn;  //cast edited connector into a loop connector
			 edConn->setSrcStat(Source);
			  Source->setLoopConnector(edConn);
			  return;
		  }


		  if(Source==edConn->getDstStat()) //checks if the new destination is the same as the source 
		  {
			  pManager->GetOutput()->PrintMessage("new destination and source are the same");
			  return;
		  }
		  if(Source->getConnector()!=0)  //checks if the new source has a connector in its outlet
		  {
			 pManager->GetOutput()->PrintMessage("There is already a connector here");
			 return;
		  }
		  if(edConn->getSrcStat()!=0)
			  edConn->getSrcStat()->disconnect();  //disconnects the old source from the connector
		  edConn->setSrcStat(Source); //sets the connector to the new source  
		  Source->setConnector(edConn);  //source has now  a pointer to the connector
	 }
 }