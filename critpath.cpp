#include<iostream>
#include<string.h>
#include "parse_tech.h"
#include "parse_net.h"
#include "map_net_tech.h"

using namespace std;

int main(int argc, char *argv[])
{
//Check for commandline arguments
	
	if(argc == 4)
	{
		if(strcmp(argv[0], "./critpath") == 0)
		{
			if(strcmp(argv[1], "-cp") == 0)
			{
			}
			else
			{
				cout << "Invalid commandline arguments" <<endl;
				cout << "Usage: critpath -cp techfile netlist" << endl;
			}
		}
		else
		{
			cout << "Invalid commandline arguments" <<endl;
			cout << "Usage: critpath -cp techfile netlist" << endl;
		}
	}
	else
	{
		cout << "Invalid commandline arguments" <<endl;
		cout << "Usage: critpath -cp techfile netlist" << endl;
	}
 
	
	int i;
	tech_data *TECH;
	net_data *NET;
	int len_tech_file, len_net_file;
	char **INPUTS, **OUTPUTS, **REGS, **WIRES;
	int inputcount, outputcount, regcount, wirecount;
	
	TECH = parse_tech(argv[2], &len_tech_file);
		//for(i=0; i<len_tech_file; i++)
		//cout << TECH[i].opname << endl;
	NET = parse_net(argv[3], &len_net_file, &INPUTS, &OUTPUTS, &REGS, &WIRES, &inputcount, &outputcount, &regcount, &wirecount);

	/*cout<< len_net_file << endl;
	cout << "INETPUTS" << endl;	
	for(i=0; i<(inputcount); i++)
		cout << INPUTS[i] << endl;	
	
	cout << "OUTPUTS" << endl;
	for(i=0; i<(outputcount); i++)
		cout << OUTPUTS[i] << endl;	

	cout << "REGS" << endl;
	for(i=0; i<(regcount); i++)
		cout << REGS[i] << endl; 	
	
	cout << "WIRES" << endl;
	for(i=0; i<(wirecount); i++)
		cout << WIRES[i] << endl; 

	for(i=0; i<(len_net_file); i++)
	{
		cout << "Line " << i << endl;
		cout << "OUTPUT " << NET[i].output << endl;
		cout << "NETUM INETPUTS " << NET[i].numinputs << endl;
		if( (NET[i].numinputs == 1) || (NET[i].numinputs == 2) )
			cout << "OPER " << NET[i].oper1 << endl;
		else if(NET[i].numinputs == 3)
		{
			cout << "OPER1 " << NET[i].oper1 << endl;
			cout << "OPER2 " << NET[i].oper2 << endl;
		}
		if(NET[i].numinputs == 1)
			cout << "INETPUT " << NET[i].input[0] << endl;
		else if(NET[i].numinputs == 2)
		{
			cout << "INETPUT1 " << NET[i].input[0] << endl;
			cout << "INETPUT2 " << NET[i].input[1] << endl;
		}	
		else if(NET[i].numinputs == 3)
		{
			cout << "INETPUT1 " << NET[i].input[0] << endl;
			cout << "INETPUT2 " << NET[i].input[1] << endl;
			cout << "INETPUT3 " << NET[i].input[2] << endl;
		}	
		
	}*/
	
	map_net_tech(&TECH, len_tech_file, &NET, len_net_file, &INPUTS, inputcount, &OUTPUTS, outputcount, &REGS, regcount, &WIRES, wirecount);
	//critpath_graph();
	//critpath_calculate();	

	return 0;
} 
