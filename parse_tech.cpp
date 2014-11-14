#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <iostream>
#include "parse_tech.h"

#define NUM_COMPONENTS 10

using namespace std;

tech_data* parse_tech(char *techfilename, int *linecount)
{	
	char techline[500], duptechline[500];
	char tmp;
	char *temp;
	FILE *techfile;
	techfile = fopen(techfilename, "r");
	tech_data *T;
	int count = 0;
	int index = 0;
	int i = 0, j = 0;	
	char COMPONENTS[NUM_COMPONENTS][7] = {"REG", "ADD32", "SUB32", "MUL32", "COMPGT", "COMPLT", "COMPEQ", "MUX2x1", "SHR", "SHL"};
	bool case_sens_flag;

	*linecount = 0;
	if(techfile != NULL)
	{
		while (fgets(techline, sizeof(techline), techfile) != NULL)
		{
			if(strlen(techline) == 1)
			{}
			else if((techline[0] == '/') && (techline[1] == '/'))
			{}
			else if((techline[0] == '/') && (techline[1] != '/'))
			{
				cout << "Invalid line in tech file" << endl;
				exit(0);
			}
			else
			(*linecount)++;
		}
		
	}
	fclose(techfile);
	T = (tech_data *)malloc((*linecount)*sizeof(tech_data));

	for(i=0; i<(*linecount); i++)
	{
		T[index].numinputs = 10;
		T[index].delay = 5.0;
	}
	
	techfile = fopen(techfilename, "r");
	
	if(techfile != NULL) 
	{
		while (fgets(techline, sizeof(techline), techfile) != NULL)
		{
			if(strlen(techline) == 1)
				continue;
			if((techline[0] == '/') && (techline[1] == '/'))
				continue;
			strcpy(duptechline, techline);
			temp = strtok(duptechline," ");
			T[index].opname = (char *)malloc(strlen(temp)*sizeof(char));

			sscanf(techline, "%s %c %d %f", T[index].opname, &tmp, &T[index].numinputs, &T[index].delay);
			index++;
		}

	} 
	else 
	{
		cout<<"Unable to open the techfile"<< endl;
	}
	
	fclose(techfile);

	for(i=0; i<(*linecount); i++)
	{
		for(j=0; j<(*linecount); j++)
		{
			if(strcmp(T[i].opname, T[j].opname) == 0)
			{
				if(i != j)
				{
					cout << "Multiple component declaration lines" << endl;
					exit(0); 
				}
			}
		}
	}
	
	// check all the number on inputs are non-zero
	for(i=0; i<*linecount; i++)
	{
		if(T[i].numinputs <= 0)
		{
			cout << "Error in tech file: component with zero or less number of inputs" << endl;
			exit(0);
		}
	}

	// check for non-zero delay
	for(i=0; i<*linecount; i++)
	{
		if(T[i].delay <= 0.0)
		{
			cout << "Error in tech file: component with zero or less delay value" << endl;
			exit(0);	
		}
	}
	
	// check for case-sensitivity of component names
	for(i=0; i<*linecount; i++)
	{
		case_sens_flag = false;
		for(j=0; j<NUM_COMPONENTS; j++)
		{
			if(strcmp(T[i].opname,COMPONENTS[j]) == 0)
			{
				if(j == 0)
				{
					if(T[i].numinputs != 1)
					{
						cout << "Error: REG component has more than one inputs" << endl;
						exit(0);
					}
				}
				case_sens_flag = true;
				break;
			}			
		}
		if(case_sens_flag == false)
		{
			cout << "Error in tech file: component not recognized" << endl;
			exit(0);
		}
	}
	
	return T;
}
