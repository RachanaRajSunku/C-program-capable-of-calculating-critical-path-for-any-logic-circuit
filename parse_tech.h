#ifndef PARSE_TECH_H
#define PARSE_TECH_H

#include <iostream>

struct tech_data
{
	char *opname;
	int numinputs;
	float delay;
};

tech_data* parse_tech(char *tfilename, int *tlen);

#endif
