#include "stdafx.h"
#include "Parser.h"
#include "Token.h"

Parser::Parser()
{
	input = "";
	name = "";
	token = 0;
	index = 0;
	value = 0;
	varCount = 0;
	isMinus = false;
	variable = new vector<Variable*>();
}

Parser::~Parser()
{
	for (auto v : *variable)
		delete v;
	delete variable;
}

int Parser::scanner()
{
	if (input.substr(index, 3) == "int")
	{
		index += 3;
		return INT;
	}
	if (input.substr(index, 4) == "bool")
	{
		index += 4;
		return BOOL;
	}
	if (input.substr(index, 4) == "true")
	{
		index += 4;
		return TRUE;
	}
	if (input.substr(index, 5) == "false")
	{
		index += 5;
		return FALSE;
	}
	if (input[index] == '-')
	{
		index++;
		return MINUS;
	}
	if (isName())
	{
		int tmp = index;
		while (isName())
			index++;
		name = input.substr(tmp, index - tmp);
		return NAME;
	}
	if (input[index] == ' ')
	{
		index++;
		return SPACE;
	}
	if (input[index] == ';')
	{
		index++;
		return SEMI;
	}
	if (input[index] == '*')
	{
		index++;
		return POINTER;
	}
	if (isNumber(&input[index]))
	{
		string numStr;
		int start = index;

		while (isNumber(&input[index]))
		{
			index++;
			numStr = input.substr(start, index - start);
			value = atoi(numStr.c_str());
		}
		return INT_VALUE;
	}
	if (input[index] == '=')
	{
		index++;
		return EQUALS;
	}
	if (input[index] == ',')
	{
		index++;
		return COMMA;
	}
}

void Parser::result()
{
	for (auto v : *variable)
	{
		if (v->getType() == "int")
		{
			cout << "Int var:" << endl
				<< v->getName() << "\t" << v->getValue() << endl;
		}
		else if (v->getType() == "bool")
		{
			string boolValue("");
			if (v->getValue() == 0)
				boolValue = "false";
			else
				boolValue = "true";
			cout << "Bool var:" << endl
				<< v->getName() << "\t" << boolValue << endl;
		}
	}

	system("PAUSE");
}

void Parser::errorExit(const char * strError)
{
	printf("Error:%s\tIndex:%d\n", strError, index);
}

bool Parser::isNumber(char *symbol)
{
	if (*symbol >= '0' && *symbol <= '9')
		return true;
	else
		return false;
}

bool Parser::isName()
{
	bool result = false;
	if (((char)input[index] >= 'A') && ((char)input[index] <= 'Z'))
		result = true;
	if (((char)input[index] >= '_') && ((char)input[index] <= 'z'))
		result = true;
	return result;
}

void Parser::readLine()
{
	getline(cin, input);
}

void Parser::mainParser()
{
	token = scanner();

	while (token != SEMI)
	{
		exprParser();
		token = scanner();
	}
}

void Parser::exprParser()
{
	if (token == INT)
		defParser();
	else if (token == BOOL)
		defParser();
	else
		return;
}

void Parser::defParser()
{
	if (token == INT)
		typeParser();
	else if (token == BOOL)
		typeParser();

	token = scanner();
	if (token == SPACE)
	{
		token = scanner();
		if (token == NAME)
			varlistParser();
		else
			errorExit("Unexpected token! Expected varlist.\tIndex: ");
	}
	else
	{
		errorExit("Unexpected token! Expected space or semi.\t Index: ");
	}
}

void Parser::typeParser()
{
	if (token == INT)
		type = "int";
	else if (token == BOOL)
		type = "bool";
	else
		errorExit("Unexpected token! Expected type.\tIndex: ");
}

void Parser::varlistParser()
{
	if (token == SPACE)
		token = scanner();

	if (token == NAME)
		varParser();
	else
		errorExit("Unexpected token! Expected varlist.\tIndex: ");

	if (token == COMMA)
	{
		token = scanner();
		varlistParser();
	}
	else
		return;
}

void Parser::varParser()
{
	if (token == NAME)
	{
		Variable *tmpVar = new Variable();
		tmpVar->setType(type);
		tmpVar->setName(name);
		variable->push_back(tmpVar);
		varCount++;

		token = scanner();
		if (token == SPACE)
		{
			token = scanner();
			if (token == EQUALS)
			{
				token = scanner();
				if (token == SPACE)
				{
					token = scanner();
					if (token == MINUS)
					{
						isMinus = true;
						token = scanner();
					}
					if (token == INT_VALUE)
					{
						if (isMinus)
							variable->at(varCount - 1)->setValue((-1)*value);
						else
							variable->at(varCount - 1)->setValue(value);
					}
					else if (token == TRUE)
						variable->at(varCount - 1)->setValue(1);
					else if (token == FALSE)
						variable->at(varCount - 1)->setValue(0);
				}
				else if (token == INT_VALUE)
				{
					variable->at(varCount - 1)->setValue(value);
				}
				else
					errorExit("Unexpected token! Expected INT or BOOL.\tIndex:");
			}
			else
			{
				return;
			}
		}
		else if (token == EQUALS)
		{
			token = scanner();
			if (token == SPACE)
			{
				token = scanner();
				if (token == MINUS)
				{
					isMinus = true;
					token = scanner();
				}
				if (token == INT_VALUE)
				{
					if (isMinus)
						variable->at(varCount - 1)->setValue((-1)*value);
					else
						variable->at(varCount - 1)->setValue(value);
				}
				else if (token == TRUE)
					variable->at(varCount - 1)->setValue(1);
				else if (token == FALSE)
					variable->at(varCount - 1)->setValue(0);
			}
			else if (token == INT_VALUE)
			{
				variable->at(varCount - 1)->setValue(value);
			}
			else
				errorExit("Unexpected token! Expected INT or BOOL.\tIndex:");
		}
		else
		{
			return;
		}
	}
}
