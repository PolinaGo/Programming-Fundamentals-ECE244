#ifndef NODE_H
#define	NODE_H
#define MAX_RESISTORS_PER_NODE 5

#include <iostream>
using namespace std;

//class node declaration
class Node {

private: 
    int numRes; // number of resistors currently connected
    int resIDArray[MAX_RESISTORS_PER_NODE]; // stores the index of each resistor connected
    int nodeIndex;
    
public:
    Node();
    ~Node();
    
    bool canAddResistor();
    void addResistor(int rIndex);
    
    void print(int nodeIndex);
    int numres() const;
    void del();
};

#endif	/* NODE_H */