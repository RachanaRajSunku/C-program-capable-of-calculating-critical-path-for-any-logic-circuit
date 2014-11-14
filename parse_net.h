#ifndef PARSE_NET_H
#define PARSE_NET_H

#include<iostream>

struct net_data
{
	char *oper1, *oper2;
	char *spoper;
	char **input;
	int numinputs;
	char *output;	
};

net_data* parse_net(char *nfilename, int *nlen, char ***INPUTS, char ***OUTPUTS, char ***REGS, char ***WIRES, int *inputcount, int *outputcount, int *regcount, int *wirecount);

#endif
