#ifndef RESISTOR_H
#define	RESISTOR_H

#include <string>
#include <iostream>
using namespace std;

//class resistor declaration
class Resistor 
{
    
private:
   double resistance=0.0; // resistance (in Ohms)
   string name; // C++ string holding the label
   int endpointNodeIDs[2]; // IDs of nodes it attaches to
   int rindex; //index of each resistor used in storage in node array
 
public:
   Resistor(int rIndex_,string name_,double resistance_,int endpoint1_, int endpoint2_);
   // rIndex_ is the index of this resistor in the resistor array
   // endpoints_ holds the node indices to which this resistor connects
   
    ~Resistor();
    
    int getIndex() const;
    int getEndpoint1() const;    
    int getEndpoint2() const;    
    
    string getName() const; // returns the name
    double getResistance() const; // returns the resistance
    void setResistance(double resistance_); // set the value of resistance

    void print(); //prints resistor

};

ostream& operator << (ostream&, const Resistor&);


#endif	/* RESISTOR_H */