#include "map_net_tech.h"
#define COMPONENTS 10
#define COMP_MAX_NAME_LEN 7
#define COMP_MAX_LEN 2 

using namespace std;

void map_net_tech(tech_data **T, int len_T, net_data **N, int len_N, char ***INPUTS, int inputcount, char ***OUTPUTS, int outputcount, char ***REGS, int regcount, char ***WIRES, int wirecount)
{
	char ***MAP;
	int i, j, k;
	int index = 0;
	bool matchfound = false;
	MAP = (char ***)malloc(COMPONENTS*sizeof(char**));
	for(i=0; i<COMPONENTS; i++)
	{
		MAP[i] = (char **)malloc(COMP_MAX_NAME_LEN*sizeof(char*));
	}
	for(i=0; i<COMPONENTS; i++)
	{
		MAP[i][0] = (char *)malloc(COMP_MAX_LEN*sizeof(char));
		MAP[i][1] = (char *)malloc(COMP_MAX_NAME_LEN*sizeof(char));
	}

	strcpy(MAP[0][0], "=");	strcpy(MAP[0][1], "REG");
	strcpy(MAP[1][0], "+");	strcpy(MAP[1][1], "ADD32");
	strcpy(MAP[2][0], "-");	strcpy(MAP[2][1], "SUB32");
	strcpy(MAP[3][0], "*");	strcpy(MAP[3][1], "MUL32");
	strcpy(MAP[4][0], ">");	strcpy(MAP[4][1], "COMPGT");
	strcpy(MAP[5][0], "<");	strcpy(MAP[5][1], "COMPLT");
	strcpy(MAP[6][0], "=="); strcpy(MAP[6][1], "COMPEQ");
	strcpy(MAP[7][0], "?");	strcpy(MAP[7][1],"MUX2x1");
	strcpy(MAP[8][0], ">>"); strcpy(MAP[8][1],"SHR");
	strcpy(MAP[9][0], "<<"); strcpy(MAP[9][1], "SHL");

	for(index=0; index<len_N; index++)
	{
		matchfound = false;
		for(j=0; j<COMPONENTS; j++)
		{
			//cout << N[index]->oper1 << endl;
			//cout << MAP[j][0] << endl << endl;
			if(strcmp((*N)[index].oper1, MAP[j][0]) == 0)
			{
				//cout << j << MAP[j][0] << N[index]->oper1 << endl;
				for(k=0; k<len_T; k++)
				{
					//cout << MAP[j][1] << " " << T[k]->opname << endl;
					if(strcmp(MAP[j][1], (*T)[k].opname) == 0)
					{
						if((*N)[index].numinputs == (*T)[k].numinputs)
						{
							matchfound = true;
						}
					}
				}
			}
		}
		if(matchfound == false)
		{
			cout<<"Index" << index << endl;
			cout << "Error: Undefined operator in netlist file or mismatch in the number of inputs of an operator" << endl;
			exit(0);
		}
	}		
}
