
/* 
 * File:   NodeList.cpp
 * Author: Govorkova Polina
 * 
 * Created on November 8, 2017, 5:41 PM
 */

#include "NodeList.h"
#include "Node.h"
//constant for accuracy
#define MIN_ITERATION_CHANGE 0.0001

//default constructor 
NodeList::NodeList() {
    head = NULL;
}

//default destructor
NodeList::~NodeList() {
}

//end of program function, deletes the whole network stored
void NodeList :: deleteList() {
     Node *temp = head;
       while (head!= NULL) {
           head = head->next;
           temp->resList.deleteRall();
           delete temp;
           temp = head;
       }  
}

//adds resistor to the nodes and creates them if they don't exist
void NodeList :: addResistor (string name, double resistance, int n1, int n2) {
    Node* temp = head;
    bool h = true;
    int m1, m2;
    //local copies of nodes,
    //m1 always less than m2
    if (n1 > n2) {
        m1 = n2;
        m2 = n1;
    }
    else {
        m1 = n1;
        m2 = n2;
    }
    //if this is the first resistor in the list, the program creates two nodes and adds them to the network in ascending order 
    if (temp == NULL) { 
        Node *plus1 = new Node(m1);
        Node *plus2 = new Node(m2);
        plus2->next = NULL;
        plus1->next = plus2;
        head = plus1;
        plus1->addResistor(name, resistance, n1, n2);
        plus2->addResistor(name, resistance, n1, n2);
    }
    //if network is not empty, the program adds resistors to existing nodes or creates nodes if necessary following ascending order 
    else {
        Node* tempCopy = head;
        //checks if new node m1 has smallest ID, finds the node that should be AFTER the given node, or has the same ID as given node
            while (temp!=NULL) {
                if (temp->ID<m1) { temp = temp->next; h = false; }
                else break;
            }
        //finds the node that is should be PRIOR to the given node m1
            while ((tempCopy->next!=temp)&&(tempCopy!=temp)&&(tempCopy->next!=NULL)) {
                tempCopy = tempCopy->next;
            }
            if (temp == NULL) { //if there m1 is bigger than all node IDs, insert both at the end of the list
                Node *plus1 = new Node(m1);
                Node *plus2 = new Node(m2);
                plus2->next = NULL;
                plus1->next = plus2;
                tempCopy->next = plus1;
                plus1->addResistor(name, resistance, n1, n2);
                plus2->addResistor(name, resistance, n1, n2);
            }
            else {  //if such node already exists add resistor, otherwise create node between tempCopy and temp              
                if (temp->ID==m1) temp->addResistor(name, resistance, n1, n2);
                else {
                    Node *plus1 = new Node(m1);
                    plus1->addResistor(name, resistance, n1, n2);
                    if (h) {
                        head = plus1;
                        plus1->next = temp;
                        tempCopy = plus1;
                    }
                    else {
                        tempCopy->next = plus1;
                        plus1->next = temp;
                        tempCopy = plus1;
                    }
                }
                //finds the node that is should be AFTER the given node m2 or have same ID
                while ((temp!=NULL)&&(temp->ID<m2)) {
                    temp = temp->next;
                }
                //finds the node that is should be AFTER the given node m2
                while ((tempCopy->next!=temp)&&(tempCopy!=temp)) {
                    tempCopy = tempCopy->next;
                }
                if (temp == NULL) { //if there m2 is bigger than all node IDs, insert at the end of the list
                    Node *plus2 = new Node(m2);
                    plus2->next = NULL;
                    tempCopy->next = plus2;
                    plus2->addResistor(name, resistance, n1, n2);
                }
                else { //if such node already exists add resistor, otherwise create node between tempCopy and temp 
                    if (temp->ID==m2) temp->addResistor(name, resistance, n1, n2); 
                    else {
                        Node *plus2 = new Node(m2);
                        tempCopy->next = plus2;
                        plus2->next = temp;
                        plus2->addResistor(name, resistance, n1, n2);
                    }
                }
            }
        }
}

//function responsible for printing certain node
void NodeList :: printNode(int n) {
    Node * temp = this->head;
    while ((temp->ID<n)&&(temp->next!=NULL)) {
    temp = temp->next;
    }
    if (temp->ID==n) temp->printNode();
}

//function responsible for printing all nodes
void NodeList :: printNodes() {
    Node * temp = this->head;
    while (temp!=NULL) {
        if (temp->resList.count!=0) temp->printNode();
    temp = temp->next;
    }
}

//boolean function returning existence of the resistor by its name
bool NodeList :: resSearch(string name){
    bool a = false;
    Node * temp = this->head;
    while (temp!=NULL) {
    if (temp->resList.resSearch(name)) a = true;
    temp = temp->next;
    }
    return a;
}

//function modifies resistance of  resistor given it exists
void NodeList :: modify(string name, double resistance) {
    double old;
    Node * temp = this->head;
    while (temp!=NULL) {
        bool a = temp->resList.resSearch(name);
    if (a) { old = temp->resList.modify(name, resistance);}
    temp = temp->next;
    }
    cout << "Modified: resistor " << name << " from " << fixed << setprecision(2) <<  old << " Ohms to " << fixed << setprecision(2) << resistance << " Ohms" << endl;
}

//void NodeList :: printNodeIDS() {
//    Node * temp = this->head;
//    while (temp!=NULL) {
//    cout << temp->ID << " " << temp->voltageUnknown << endl;
//    temp = temp->next;
//    }
//}

//boolean function that returns existence of node
bool NodeList :: findNode(int n) {
    bool a;
    Node * temp = this->head;
    while (temp!=NULL) {
    if (temp->ID == n) a = true; 
    temp = temp->next;
    }
    return a;
}

//function sets voltage of given node
void NodeList :: setV(int n, double voltage) {
    Node * temp = this->head;
    while (temp!=NULL) {
    if (temp->ID == n) temp->setV(voltage); 
    temp = temp->next;
    }
}

//function unsets voltage of given node
void NodeList :: unsetV(int n) {
    Node * temp = this->head;
    while (temp!=NULL) {
    if (temp->ID == n) temp->unsetV(); 
    temp = temp->next;
    }
}

//function responsible for printing information about given resistor
void NodeList :: printR(string name) {
    Node * temp = this->head;
    bool a = false;
    while ((temp!=NULL)&&(a==false)) {
    a = temp->resList.resSearch(name);
    if (a) temp->resList.printResistor(name); 
    temp = temp->next;
    }
}

//function responsible for deleting given resistor
void NodeList :: deleteResistor(string name) {
    Node * temp = this->head;
    while (temp!=NULL) {
        if (temp->resList.resSearch(name)) {
            temp->resList.deleteR(name);
        }
            temp = temp->next;

    }
}

//function responsible for deleting all resistors
void NodeList :: deleteRall () {
    Node * temp = this->head;
    while (temp!=NULL) {
        temp->resList.deleteRall();
        temp = temp->next;
    }
}

//boolean function checking for existence of voltage sources
bool NodeList :: areAllSet() {
    Node * temp = this->head;
    bool is = false;
    while (temp!=NULL) {
        if (temp->set == 1) {
            is = true;
        }
            temp = temp->next;

    }
    return is;
}

//function responsible for solving the network given voltage source exists
void NodeList :: solve() {
    Node * temp = this->head;
    Node * temp2 = this->head;
    setTo0(); //sets all unset voltages to 0 from their previous values
    int nodes, n;
    double term1 = 0;
    double term2 = 0;
    double change = 10;
    double volt = 0;
    double delta;
    while (change > MIN_ITERATION_CHANGE) {
        change = 0;
        while (temp!=NULL) {
            if (temp->set == 0) {
                term1 = term11(temp);
                term2 = temp->resList.term2();

                volt = term1/term2;      
                delta = (volt - temp->voltageUnknown);
                
                if (delta < 0) delta = delta*(-1);
                if (delta > change) change  = delta; 
                //change - maximum difference between old voltage and new among nodes in one cycle
                temp->voltageUnknown = volt;
            }
        temp = temp->next;
        }
        temp = head;
    }
    Node * print = this->head;
    while (print!=NULL) {
        cout << "  Node "<< print->ID << ": "<< print->voltageUnknown << " V"<<endl;
        print = print->next;
    }
}

//assistant to solve function, finds sum of Vi/Ri for every ith node connected to given node
double NodeList :: term11(Node * temp) {
      Resistor *temp2 = temp->resList.head;
       int n = temp->ID;
       int another;
       double term1 = 0;
       
       while (temp2 != NULL) {
            another = temp2->getEndpoint1();
            //checks for different node
            if (another == n) another = temp2->getEndpoint2();
            term1 = getVoltage(another)/temp2->getResistance() + term1;
            temp2 = temp2->getNext();
        }
       return term1;
}

//assistant to solve function, returns voltage of node
double NodeList :: getVoltage(int n) {
    Node * temp = this->head;
    while (temp->ID != n) {
            temp = temp->next;
    }
    return temp->voltageUnknown;
}

//assistant to solve function, equals all unset voltages to zero
void NodeList :: setTo0 () {
    Node * temp = this->head;
    while (temp!=NULL) {
        if (temp->set==0) { temp->voltageUnknown = 0; }
        temp = temp->next;
    }
}

//sets all the nodes to initial condition : unset, v = 0
void NodeList :: unsetAndZero () {
    Node * temp = this->head;
    while (temp != NULL) {
        temp->set = 0;
        temp->voltageUnknown = 0;        
            temp = temp->next;
    }
}