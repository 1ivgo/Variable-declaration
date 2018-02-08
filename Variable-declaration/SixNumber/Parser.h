#pragma once

#include <iostream>
#include <vector>

#include "Variable.h"

class Parser
{
public:
	Parser();
	~Parser();

	void mainParser();
	void result();
	void readLine();

private:
	int scanner();
	void errorExit(const char*);
	bool isNumber(char*);
	bool isName();
	void exprParser();
	void defParser();
	void typeParser();
	void varlistParser();
	void varParser();

protected:
	string input;
	string name;
	string type;
	int token;
	int index;
	int value;
	int varCount;
	bool isMinus;
	vector<Variable*> *variable;
};
