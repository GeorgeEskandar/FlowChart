# FlowChart
Object Oriented Programming Project with C++
April 2014

An application with GUI for a program where the user can draw a flowchart and run it to display results.
Use Cases: 
- User can add or delete statements and connect between them
- User can save or load a flowchart he has drawn
- User can simulate the algorithm written via the Flowchart
Each user action comes from a mouse click on the Actions Toolbar

The main class is AppManager that contains a list of statements and connectors that user has drawn. 
- Statement class is the parent class for SimpleAssignment, Complex Assignment, loop, condition..
- Action class is parent class for classes: Copy, save, delete, move..
- an input and output class use a graphics library and are responsible to draw to the screen and take user events (mouse click, key pressed)
- A connector is associated with two statements, every statement has 1 connector (if statement is deleted the in connector is deleted)
