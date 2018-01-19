#ifndef RPARSER_H
#define	RPARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include "Node.h"
#include "Resistor.h"

//declaration of external variables - storage arrays
extern Node * NodeArray;
extern Resistor ** ResistorArray;

//declaration of functions used in resistor parser

int Rparser(void);

void error1_maxVal();
	
void error2_resNotFound(string);

void error3_notInRange(int, int);

void error4_resFull();

void error5_nodeFull();

void error6(string);

void error7(int);

int resSearch(string, int);


#endif	/* RPARSER_H */