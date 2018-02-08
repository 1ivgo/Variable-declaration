#pragma once

#include <string>

using namespace std;

class Variable
{
public:
	Variable();
	~Variable();

	void setType(string);
	string getType();
	void setValue(int);
	int getValue();
	void setName(string);
	string getName();

private:
	string type;
	int iValue;
	bool bValue;
	string name;
};