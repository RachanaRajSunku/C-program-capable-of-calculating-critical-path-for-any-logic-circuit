#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "parse_net.h"

using namespace std;

net_data* parse_net(char *netfilename, int *linecount, char ***INPUTS, char ***OUTPUTS, char ***REGS, char ***WIRES, int *inputcount, int *outputcount, int *regcount, int *wirecount)
{	
	char netline[500], dupnetline[500], newnetline[500];
	char *temp, *tmp;
	FILE *netfile;
	int count = 0;
	int index = 0;
	int i = 0, j = 0;
	*linecount = 0;
	net_data *N;
	int lineindex = 0, linelength = 0;
	bool flaginput = false, flagoutput = false, flagregs = false, flagwires = false;
	bool inputsfound = false, outputsfound = false, regsfound = false, wiresfound = false;
	*inputcount = -1; *outputcount = -1; *regcount = -1; *wirecount = -1;
	int index_input = 0;	
	netfile = fopen(netfilename, "r");
	if(netfile == NULL)
	{
		cout << "Unable to open the netlist file" << endl;
		exit(0);
	}
	if(netfile != NULL)
	{
		while (fgets(netline, sizeof(netline), netfile) != NULL)
		{
			if(strlen(netline) == 1)
				continue;
			strcpy(newnetline, netline);
			newnetline[strlen(netline)-1] = '\0';		
			temp = strtok(newnetline, " ");
			if(strcmp(temp, "INPUTS") == 0)
			{
				if(inputsfound == true)
				{
					cout << "Multiple lines with input declaration" << endl;
					exit(0);
				}
				while(temp != NULL)
				{
					if(strcmp(temp,":") == 0)
					{
					}	
					else
					{
						(*inputcount)++;
					}
					temp = strtok(NULL, " ");
				}
				inputsfound = true;
			}
			else if (strcmp(temp, "OUTPUTS") == 0)
			{
				if(outputsfound == true)
				{
					cout << "Multiple lines with output declaration" << endl;
					exit(0);
				}
				while(temp != NULL)
				{
					if(strcmp(temp,":") == 0)
					{
					}
					else
					{
						(*outputcount)++;
					}
					temp = strtok(NULL, " ");
				}
				outputsfound = true;
			}
			else if (strcmp(temp, "REGS") == 0)
			{
				if(regsfound == true)
				{
					cout << "Multiple lines with reg declaration" << endl;
					exit(0);
				}	
				while(temp != NULL)
				{
					if(strcmp(temp,":") == 0)
					{	
					}
					else
					{
						(*regcount)++;
					}
					temp = strtok(NULL, " ");
				}
				regsfound = true;
			}
			else if (strcmp(temp, "WIRES") == 0)
			{
				if(wiresfound == true)
				{
					cout << "Multiple lines with wire declaration" << endl;
					exit(0);
				}
				while(temp != NULL)
				{
					if(strcmp(temp,":") == 0)
					{
					}	
					else
					{
						(*wirecount)++;
					}
					temp = strtok(NULL, " ");
				}
				wiresfound = true;
			}
			else
			{
				if( (strlen(netline) > 1) && (netline[0] != '/') && (netline[1] != '/') )
					(*linecount)++;
			}
		}
		
	}
	fclose(netfile);

	if((*inputcount) <= 0)
	{
		cout << "No inputs provided in the netlist file" << endl;
		exit(0);
	}
	
	if((*outputcount) <= 0)
	{
		cout << "No outputs provided in the netlist file" << endl;
		exit(0);
	}
	
	*INPUTS = (char **)malloc((*inputcount)*sizeof(char *));
	*OUTPUTS = (char **)malloc((*outputcount)*sizeof(char *));		
	*REGS = (char **)malloc((*regcount)*sizeof(char *));
	*WIRES = (char **)malloc((*wirecount)*sizeof(char *));	
	
	netfile = fopen(netfilename, "r");
	if(netfile != NULL)
	{
		while (fgets(netline, sizeof(netline), netfile) != NULL)
		{
			if(strlen(netline) == 1)
				continue;
			strcpy(newnetline, netline);
			newnetline[strlen(netline)-1] = '\0'; 
			temp = strtok(newnetline, " ");
			if(strcmp(temp, "INPUTS") == 0)
			{
				while(temp != NULL)
				{
					if( (strcmp(temp,"INPUTS") == 0) || (strcmp(temp, ":") == 0) )
					{
					}
					else
					{
						(*INPUTS)[index] = (char *)malloc(strlen(temp)*sizeof(char));
						strcpy((*INPUTS)[index], temp);
						index++;							
					}
					temp = strtok(NULL, " ");
				}
			}
			else if(strcmp(temp, "OUTPUTS") == 0)
			{
				while(temp != NULL)
				{
					if ((strcmp(temp, "OUTPUTS") == 0) || (strcmp(temp, ":") == 0))
					{
					}
					else
					{
						(*OUTPUTS)[index] = (char *)malloc(strlen(temp)*sizeof(char));
						strcpy((*OUTPUTS)[index], temp);
						index++; 
					}
					temp = strtok(NULL, " ");
				}
			}
			else if(strcmp(temp, "REGS") == 0)
			{
				while(temp != NULL)
				{
					if ((strcmp(temp, "REGS") == 0) || (strcmp(temp, ":") == 0))
					{
					}
					else
					{
						(*REGS)[index] = (char *)malloc(strlen(temp)*sizeof(char));
						strcpy((*REGS)[index], temp);
						index++; 
					}
					temp = strtok(NULL, " ");
				}
			}
			else if(strcmp(temp, "WIRES") == 0)
			{
				while(temp != NULL)
				{
					if ((strcmp(temp, "WIRES") == 0) || (strcmp(temp, ":") == 0))
					{
					}
					else
					{
						(*WIRES)[index] = (char *)malloc(strlen(temp)*sizeof(char));
						strcpy((*WIRES)[index], temp);
						index++; 
					}
					temp = strtok(NULL, " ");
				}
			}
			index = 0;			
		}
	}
	fclose(netfile);

	N = (net_data *)malloc((*linecount)*sizeof(net_data));
		
	netfile = fopen(netfilename, "r");
	index = 0;
	if(netfile != NULL)
	{
		while(fgets(netline, sizeof(netline), netfile) != NULL)
		{
			strcpy(dupnetline, netline);
			temp = strtok(dupnetline, " ");	
			
			if((strcmp(temp, "INPUTS") == 0) || (strcmp(temp, "OUTPUTS") == 0) || (strcmp(temp, "WIRES") == 0) || (strcmp(temp, "REGS") == 0))
			{
			}
			else if(strlen(netline) == 1)
			{
			}
			else if( (netline[0] == '/') && (netline[1] == '/') )
			{
			}
			else
			{
				linelength = 0;
				strcpy(newnetline, netline);
				newnetline[strlen(netline)-1] = '\0';
				tmp = strtok(newnetline, " ");
				while(tmp != NULL)
				{
					linelength++;
					tmp = strtok(NULL, " ");
				}
				if(linelength == 3)
				{
					N[index].input = (char **)malloc(1*sizeof(char *));
					strcpy(newnetline, netline);
					newnetline[strlen(netline)-1] = '\0';
					tmp = strtok(newnetline, " ");
					lineindex = 0;
					while(tmp != NULL)
					{
						if(lineindex == 0)
						{
							N[index].output = (char *)malloc(strlen(tmp)*sizeof(char));
							strcpy(N[index].output, tmp);
						}
						else if(lineindex == 1)
						{
							if(strcmp(tmp, "=") == 1)
							{
								cout << "Error in netlist file: format problem, missing = sign" << endl;
								exit(0);
							}
							else
							{
								N[index].oper1 = (char *)malloc(2*sizeof(char));
								strcpy(N[index].oper1, tmp);
								N[index].spoper = (char *)malloc(2*sizeof(char));
								strcpy(N[index].spoper, tmp);
							}
						}
						else if(lineindex == 2)
						{
							N[index].input[0] = (char *)malloc(strlen(tmp)*sizeof(char));
							strcpy(N[index].input[0], tmp);
						}
						tmp = strtok(NULL, " ");
						lineindex++;
					}
					N[index].numinputs = 1;	
				}
				else
				{
					N[index].input = (char **)malloc(((linelength-1)/2)*sizeof(char *));
					N[index].numinputs = (linelength-1)/2;
					strcpy(newnetline, netline);
					newnetline[strlen(netline)-1] = '\0';
					tmp = strtok(newnetline, " ");
					lineindex = 0;
					index_input = 0;
					while(tmp != NULL)
					{
						if(lineindex == 0)
						{
							N[index].output = (char *)malloc(strlen(tmp)*sizeof(char));
							strcpy(N[index].output, tmp);	
						}
						else if((lineindex%2) == 1)
						{
							if(lineindex == 1)
							{
								if(strcmp(tmp,"=") != 0)
								{
									cout << "Error in the netlist file: format problem" << endl;
									exit(0);
								}
								else
								{
									N[index].spoper = (char *)malloc(2*sizeof(char));
									strcpy(N[index].spoper, tmp);
								}
							}
							else if(lineindex == 3)
							{
								N[index].oper1 = (char *)malloc(2*sizeof(char));
								strcpy(N[index].oper1, tmp);	
							}
							else
							{
								if(strcmp(tmp,N[index].oper1) == 0)
								{
								}
								else if((strcmp(tmp, ":") == 0) && (strcmp(N[index].oper1,"?") == 0))
								{
									N[index].oper2 = (char *)malloc(1*sizeof(char));
									strcpy(N[index].oper2, tmp);
								}
								else
								{
									cout << "Error in netlist file: Wrong combination of operators" << endl;
									exit(0);
								}
								
							}
						}
						else if(lineindex%2 == 0)
						{
							N[index].input[index_input] = (char *)malloc(strlen(tmp)*sizeof(char));
							strcpy(N[index].input[index_input], tmp);
							index_input++;	
						}
						tmp = strtok(NULL, " ");
						lineindex++;
					}
				}
				/*else if(linelength == 5)
				{
					N[index].input = (char **)malloc(2*sizeof(char *));
					strcpy(newnetline, netline);
					newnetline[strlen(netline)-1] = '\0';
					tmp = strtok(newnetline, " ");
					lineindex = 0;
					while(tmp != NULL)
					{
						if(lineindex == 0)
						{
							N[index].output = (char *)malloc(strlen(tmp)*sizeof(char));
							strcpy(N[index].output, tmp);	
						}
						else if(lineindex == 1)
						{
						}
						else if(lineindex == 2)
						{
							N[index].input[0] = (char *)malloc(strlen(tmp)*sizeof(char));
							strcpy(N[index].input[0], tmp);
						}
						else if(lineindex == 3)
						{
							N[index].oper1 = (char *)malloc(2*sizeof(char));
							strcpy(N[index].oper1, tmp); 
						}
						else if(lineindex == 4)
						{
							N[index].input[1] = (char *)malloc(strlen(tmp)*sizeof(char));
							strcpy(N[index].input[1], tmp);	
						}
						tmp = strtok(NULL, " ");
						lineindex++;	
					}
					N[index].numinputs = 2;
				}
				else if(linelength == 7)
				{
					N[index].input = (char **)malloc(3*sizeof(char *));
					strcpy(newnetline, netline);
					newnetline[strlen(netline)-1] = '\0';
					tmp = strtok(newnetline, " ");
					lineindex = 0;
					while(tmp != NULL)
					{
						if(lineindex == 0)
						{
							N[index].output = (char *)malloc(strlen(tmp)*sizeof(char));
							strcpy(N[index].output, tmp);	
						}
						else if(lineindex == 1)
						{
						}
						else if(lineindex == 2)
						{
							N[index].input[0] = (char *)malloc(strlen(tmp)*sizeof(char));
							strcpy(N[index].input[0], tmp);
						}
						else if(lineindex == 3)
						{
							N[index].oper1 = (char *)malloc(2*sizeof(char));
							strcpy(N[index].oper1, tmp); 
						}
						else if(lineindex == 4)
						{
							N[index].input[1] = (char *)malloc(strlen(tmp)*sizeof(char));
							strcpy(N[index].input[1], tmp);	
						}
						else if(lineindex == 5)
						{
							N[index].oper2 = (char *)malloc(1*sizeof(char));
							strcpy(N[index].oper2, tmp);
						}
						else if(lineindex == 6)
						{
							N[index].input[2] = (char *)malloc(strlen(tmp)*sizeof(char));
							strcpy(N[index].input[2], tmp);	
						}
						tmp = strtok(NULL, " ");
						lineindex++;	
					}
					N[index].numinputs = 3;	
				}*/
				index++;	
			}
				
		}
	} 
	fclose(netfile);	
	
	// Error checking for duplicacy across INPUTS, OUTPUTS, REGS, WIRES
	
	// Compare inputs with outputs
	for(i=0; i<(*inputcount); i++)
	{
		for(j=0; j<(*outputcount); j++)
		{
			if(strcmp((*INPUTS)[i], (*OUTPUTS)[j]) == 0)
			{
				cout << "Duplicate declaration between inputs and outputs" << endl;
				exit(0); 
			}
		}
	}

	// Compare inputs with regs
	for(i=0; i<(*inputcount); i++)
	{
		for(j=0; j<(*regcount); j++)
		{
			if(strcmp((*INPUTS)[i], (*REGS)[j]) == 0)
			{
				cout << "Duplicate declaration between inputs and registers" << endl;
				exit(0); 
			}
		}
	}
	
	// Compare inputs with wires
	for(i=0; i<(*inputcount); i++)
	{
		for(j=0; j<(*wirecount); j++)
		{
			if(strcmp((*INPUTS)[i], (*WIRES)[j]) == 0)
			{
				cout << "Duplicate declaration between inputs and wires" << endl;
				exit(0); 
			}
		}
	}

	// Compare outputs with regs
	for(i=0; i<(*outputcount); i++)
	{
		for(j=0; j<(*regcount); j++)
		{
			if(strcmp((*OUTPUTS)[i], (*REGS)[j]) == 0)
			{
				cout << "Duplicate declaration between outputs and registers" << endl;
				exit(0); 
			}
		}
	}

	// Compare outputs with wires
	for(i=0; i<(*outputcount); i++)
	{
		for(j=0; j<(*wirecount); j++)
		{
			if(strcmp((*OUTPUTS)[i], (*WIRES)[j]) == 0)
			{
				cout << "Duplicate declaration between outputs and wires" << endl;
				exit(0); 
			}
		}
	}

	// Compare regs with wires
	for(i=0; i<(*regcount); i++)
	{
		for(j=0; j<(*wirecount); j++)
		{
			if(strcmp((*REGS)[i], (*WIRES)[j]) == 0)
			{
				cout << "Duplicate declaration between registers and wires" << endl;
				exit(0); 
			}
		}
	}
 
	// Duplicate declarations of inputs
	for(i=0; i<(*inputcount); i++)
	{
		for(j=0; j<(*inputcount); j++)
		{
			if(strcmp((*INPUTS)[i],(*INPUTS)[j]) == 0)
			{
				if(i != j)
				{
					cout << "Duplicate declaration between inputs" << endl;
					exit(0);
				}
			}
		}
	}
	
	// Duplicate declarations of outputs
	for(i=0; i<(*outputcount); i++)
	{
		for(j=0; j<(*outputcount); j++)
		{
			if(strcmp((*OUTPUTS)[i],(*OUTPUTS)[j]) == 0)
			{
				if(i != j)
				{
					cout << "Duplicate declaration between outputs" << endl;
					exit(0);
				}
			}
		}
	}
	
	// Duplicate declarations of regs
	for(i=0; i<(*regcount); i++)
	{
		for(j=0; j<(*regcount); j++)
		{
			if(strcmp((*REGS)[i],(*REGS)[j]) == 0)
			{
				if(i != j)
				{
					cout << "Duplicate declaration between registers" << endl;
					exit(0);
				}
			}
		}
	}
	
	// Duplicate declarations of wires
	for(i=0; i<(*wirecount); i++)
	{
		for(j=0; j<(*wirecount); j++)
		{
			if(strcmp((*WIRES)[i],(*WIRES)[j]) == 0)
			{
				if(i != j)
				{
					cout << "Duplicate declaration between wires" << endl;
					exit(0);
				}
			}
		}
	}

	// Check if everything on the LHS of equations is either OUTPUT or REG or WIRE
	for(index=0; index<(*linecount); index++)
	{
		flagoutput = false;
		flagregs = false;
		flagwires = false;
		
		for(i=0; i<(*outputcount); i++)
		{
			if(strcmp(N[index].output, (*OUTPUTS)[i]) == 0)
			{
				flagoutput = true;
				break;
			}
		}
		if(flagoutput == false)
		{
			for(i=0; i<(*regcount); i++)
			{
				if(strcmp(N[index].output, (*REGS)[i]) == 0)
				{
					flagregs = true;
					break;
				}
			}
	
		}
		if( (flagregs == false) && (flagoutput == false) )
		{
			for(i=0; i<(*wirecount); i++)
			{
				if(strcmp(N[index].output, (*WIRES)[i]) == 0)
				{
					flagwires = true;
					break;
				}
			}
	
		}
		if((flagoutput == false) && (flagregs == false) && (flagwires == false))
		{
			cout << "LHS side of node index " << index << " not an output or reg or wire variable" << endl;
			exit(0);
		}	
			
	}
	
	// Check if everything on the RHS of equations is either an input or reg or wire
	
	for(index=0; index<(*linecount); index++)
	{
		for(i=0; i<N[index].numinputs; i++)
		{
			flaginput = false;
			flagregs = false;
			flagwires = false;
			
			for(j=0; j<(*inputcount); j++)
			{
				if(strcmp(N[index].input[i], (*INPUTS)[j]) == 0)
				{
					flaginput = true;
					break;
				}
			}

			if(flaginput == false)
			{
				for(j=0; j<(*regcount); j++)
				{
					if(strcmp(N[index].input[i], (*REGS)[j]) == 0)
					{
						flagregs = true;
						break;
					}
				}
			}

			if((flaginput == false) && (flagregs == false))
			{
				for(j=0; j<(*wirecount); j++)
				{
					if(strcmp(N[index].input[i], (*WIRES)[j]) == 0)
					{
						flagwires = true;
						break;
					}
				}	
			}
			
			if((flaginput == false) && (flagregs == false) && (flagwires == false))
			{
				cout << "RHS side of node index " << index << " not an input or register or wire variable " << N[index].input[i] << endl;
				exit(0);	
			}		
		}
	}
	return N;
}
