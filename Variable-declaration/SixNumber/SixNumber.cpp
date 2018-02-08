// SixNumber.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Parser.h"

int main()
{
	Parser prs;

	prs.readLine();
	prs.mainParser();
	prs.result();

	return 0;
}

