#ifndef MAP_NET_TECH_H
#define MAP_NET_TECH_H

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "parse_tech.h"
#include "parse_net.h"

void map_net_tech(tech_data **TECH, int len_tech, net_data **NET, int len_net, char ***INPUTS, int inputcount, char ***OUTPUTS, int outputcount, char ***REGS, int regcount, char ***WIRES, int wirecount);

#endif
