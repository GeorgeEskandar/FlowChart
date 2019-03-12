#include"Variable.h"
#include"Condition.h"
#include<iostream>
using namespace std;

Variable::Variable()
{
	this->myVarsValue.clear();
	this->myVarsState.clear();
}

Variable::~Variable()
{
	this->myVarsValue.clear();
	this->myVarsState.clear();
}

bool Variable::AddVar(string name) // Creats a new varibale
{
	name = filterName(name);
	this->myVarsValue[name] = 0;
	this->myVarsState[name] = false;
	return true;
}

bool Variable::SetVar(string name,double value) // Assigns a value to a variable; if var exits return true otherwise false;
{
	name = filterName(name);
	this->myVarsValue[name]=value;
	this->myVarsState[name]=true;
	//cout<<"Setted "<<name<<":  "<<this->myVarsValue[name]<<" Bool: "<<this->myVarsState[name]<<endl;
	return true;
}

bool Variable::GetVar(string name,double &retValue) // If var exits return true and fills parameter with value, if var doesn't exit return 0;
{
	name = filterName(name);
	map<string,bool>::iterator itExist=this->myVarsState.find(name);
	//cout<<"Checking :"<<name<<"Value<< "<<this->myVarsValue[name]<<endl;
	//cout<<"It Exists First: "<<itExist->first<<" Second "<<itExist->second<<endl;
	if(itExist != this->myVarsState.end())
	{
		if(itExist->second == true)
		{
			//Variable has a value;
			retValue = this->myVarsValue[name];
			return true;
		}
		return false;// The variable has no value;
	}
	
	//Variable doesn't exits
	return false;

}

bool Variable::RunExp(string exp,double &retValue)//runs an algebric expression and return its value;
{
	int operIndex=-1;
	char operation;
	double val1,val2,tmp=0.0;
	string varA,varB;
	for(int i=0;i<exp.size();i++)
	{
		if(exp[i]=='+'||exp[i]=='-'||exp[i]=='/'||exp[i]=='*')
		{
			operIndex = i;
			operation = exp[i];
		}
	}
	if(operIndex==-1)
	{
		int i;
		for(i=0;i<exp.size()&&exp[i]==' ';i++){} // to escape spaces in the front
		if(exp[i]>='0'||exp[i]<='9')
		{
			//You cought a double value;
			retValue = strtod(exp.c_str(),NULL);
			return true;
		}else
		{
			//You cought a varialble name;
			double d;
			if(this->GetVar(exp,d))
			{
				retValue = d;
				return true;
			}else
			{
				//Variable not found
				return false;
			}
		}
	}else
	{
		// You found a operator '*,-,+,/'
		// Find its left side and right side ie: left * right
		int i,j;
		for(i=0;i<exp.size()-operIndex&&exp[i]==' ';i++){} // To get first non space char
		for(j=operIndex+1;j<exp.size()&&exp[j]==' ';j++){} // To get first non space char
		string left=exp.substr(i,operIndex-i),right=exp.substr(j,exp.size());
		
		if(left[0]>='0'&&left[0]<='9'&&right[0]>='0'&&right[0]<='9')
		{
			// Both are decimal values
			val1 = strtod(left.c_str(),NULL);
			val2 = strtod(right.c_str(),NULL);
		}else if(left[0]>='0'&&left[0]<='9')
		{
			// left is a decimal value and right is a variable name
			val1 = strtod(left.c_str(),NULL);
			if(!this->GetVar(right,val2))
			{
				//Variable Name doesn't exist;
				return false;
			}
		}else if(right[0]>='0'&&right[0]<='9')
		{
			// left is variable name , right is decimal value;
			val2 = strtod(right.c_str(),NULL);
			if(!this->GetVar(left,val1))
			{
				//Variable Name doesn't exist;
				return false;
			}
		}else
		{
			//both are variable names
			//cout<<"Here << "<<left<<endl;
			if(!this->GetVar(left,val1))
			{
				//Variable Name doesn't exist;
				
				return false;
			}
			if(!this->GetVar(right,val2))
			{
				//Variable Name doesn't exist;
				return false;
			}
		}
	}
	if(operation=='*') retValue = val1 * val2;
	if(operation=='+') retValue = val1 + val2;
	if(operation=='/') retValue = val1 / val2;
	if(operation=='-') retValue = val1 - val2;
	

	return true;
}

bool Variable::RunIneq(double Lvalue,double Rvalue,Relational op)
{
	switch(op)
	{
		case EQ:
			return Lvalue == Rvalue;

		case NOT:
			return Lvalue!= Rvalue;

		case GRT:
			return Lvalue > Rvalue;

		case LSS:
			return Lvalue < Rvalue;
			
		case GRT_EQ:
			return Lvalue >= Rvalue;
			
		case LSS_EQ:
			 return Lvalue <= Rvalue;
	}
	//Unknown;
	return false;
}

string Variable::filterName(string name)
{
	//Removes Any Spaces in the name;
	string tmp="";

	for(int i=0;i<name.size();i++) if(name[i]!=' ') tmp+=name[i];

	return tmp;
}

string Variable::AllVar()
{
	string StateOfVar ="";
	for(map<string,double>::iterator it=this->myVarsValue.begin();it!=this->myVarsValue.end();it++)
	{
		StateOfVar += " Name:" + it->first + " -> Value:" + to_string((long double)it->second) + ", ";
	}
	return StateOfVar;
}