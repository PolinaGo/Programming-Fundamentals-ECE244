/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rparser.h
 * Author: govorkov
 *
 * Created on November 8, 2017, 5:31 PM
 */

#ifndef RPARSER_H
#define RPARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"
#include "ResistorList.h"

//list of functions used in Rparser.cpp
int Rparser(void);
void error1_noVoltageSet();
void error2_resNotFound(string name);
void error3(string name);
void error4(int n1);

#endif /* RPARSER_H */

