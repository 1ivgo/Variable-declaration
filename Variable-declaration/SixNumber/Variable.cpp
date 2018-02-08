#include "stdafx.h"
#include "Variable.h"

Variable::Variable()
{
	name = "";
	iValue = 0;
	bValue = false;
	name = "";
}

Variable::~Variable()
{
}

void Variable::setType(string s)
{
	type = s;
}

string Variable::getType()
{
	return type;
}

void Variable::setValue(int i)
{
	iValue = i;
}

int Variable::getValue()
{
	return iValue;
}

void Variable::setName(string s)
{
	name = s;
}

string Variable::getName()
{
	return name;
}
