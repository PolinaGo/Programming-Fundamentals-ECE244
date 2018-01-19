/* 
 * File:   TreeDB.cpp
 * Author: Govorkova Polina
 * 
 * Created on November 16, 2017, 4:58 PM
 */

#include "TreeDB.h"
#include "TreeNode.h"
#include "DBentry.h"

//Insert recursion function. 
//using recursion finds the place for new element based on its name, 
//inserts new element in the given place, 
//returns false if element not found
bool TreeDB::insertRec(TreeNode* temp, DBentry* newEntry) {
    if (temp->getEntry()->getName() == newEntry->getName()) return true;
    else {
        if (temp->getEntry()->getName() > newEntry->getName()) {
            if (temp->getLeft()==NULL) {
                TreeNode * plus = new TreeNode(newEntry);
                probesCount ++;
                if (newEntry->getActive() == true) countactive ++;
                temp->setLeft(plus);
                plus = NULL;
                return false;
            }
            else {
                return (insertRec(temp->getLeft(), newEntry));
            }
        }
        else { //the needed node is on the right side
            if (temp->getRight()==NULL) {
                TreeNode * plus = new TreeNode(newEntry);
                probesCount ++;
                if (newEntry->getActive() == true) countactive ++;
                temp->setRight(plus);
                plus = NULL;
                return false;
            }
            else {
                return (insertRec(temp->getRight(), newEntry));
            }
        }
    }
}

//Find recursion function. Using recursion finds element given by its name. 
//depending on update input performs following:
//update = 1: sets found node "active", returns true when found, false when not found
//update = -1: sets found node "inactive", returns true when found, false when not found
//update = 0: returns true when found, false when not found
bool TreeDB::findRec(TreeNode* root, string name, int update) {
    if (!root) return false;
    else {
        if (root->getEntry()->getName()==name) {
            if (update == 0){
                if (root->getEntry()->getActive() == true) cout << name << " : " << root->getEntry()->getIPaddress() << " : active" << endl;
                else cout << name << " : " << root->getEntry()->getIPaddress() << " : inactive" <<endl;
            }
            else {
                if (update == -1) {
                    if (root->getEntry()->getActive() == true) {
                        root->getEntry()->setActive(false);
                        countactive --;
                    }
                    cout << "Success" << endl;                    
                }
                else if (update == 1) {
                    if (root->getEntry()->getActive() == false) {
                    root->getEntry()->setActive(true);      
                    countactive ++;
                    }
                    cout << "Success" << endl;
                }
            }
            return true;
        }
        else {
            if (root->getEntry()->getName() > name) {
                if (root->getLeft()!=NULL) return (findRec(root->getLeft(), name, update));
            }
            else {
                if (root->getRight()!=NULL) return (findRec(root->getRight(), name, update));  
            }
        }
    }
}

//Helpful to remove the node function that finds the most right node in given tree and returns pointer to it
TreeNode* TreeDB::mostRight(TreeNode* root) {
    while(root->getRight() != NULL) {
        root = root->getRight();
    }
    return root;
}

//Remove recursion function. Traverses the tree until finds node with given name, delete in 4 possible cases:
//1: no subtrees, simply deleted
//2, 3: one subtree either left or right, the root of subtree replaces the deleted node
//4: two subtrees, the biggest node in left subtree replaces deleted node
TreeNode* TreeDB::removeRec(TreeNode* root, string name) {
        
        if (name == root->getEntry()->getName()) {

           if (root->getLeft() == NULL && root->getRight() == NULL) { //1: no subtrees
              delete root; 
              root = NULL;
           }

           else if (root->getLeft() == NULL) { //2: right subtree only
              TreeNode *deleted = root;
              root = root->getRight();
              delete deleted;
           }

           else if (root->getRight() == NULL) { //3: left subtree only
              TreeNode *deleted = root;
              root = root->getLeft();
              delete deleted;
           }
           else {//4: two subtrees
                TreeNode *deleted = mostRight(root->getLeft()); 
                root->getEntry()->setActive(deleted->getEntry()->getActive());
                root->getEntry()->setIPaddress(deleted->getEntry()->getIPaddress());
                root->getEntry()->setName(deleted->getEntry()->getName());
                
                if ((root->getLeft()->getRight()==NULL)&&(root->getLeft()->getLeft()==NULL)) {
                    removeRec(root->getLeft(), deleted->getEntry()->getName());
                    root->setLeft(NULL);
                }
                else removeRec(root->getLeft(), deleted->getEntry()->getName()); 
                deleted = NULL;
           }
        }
        else if (name < root->getEntry()->getName()) { 
            root->setLeft(removeRec(root->getLeft(), name));
        } 
        else if (name > root->getEntry()->getName()) {
            root->setRight(removeRec(root->getRight(), name));
        } 
    return root;
}

//Print recursion function.
//prints all the nodes from left to right
int TreeDB::printRec(TreeNode* root) {
    int k;
    if (!root) return 0;
    else {
        if (root->getLeft()==NULL) {
            if (root->getEntry()->getActive() == true) cout << root->getEntry()->getName() << " : " << root->getEntry()->getIPaddress() << " : active" << endl;
            else cout << root->getEntry()->getName() << " : " << root->getEntry()->getIPaddress() << " : inactive" <<endl;
            if (root->getRight()!= NULL) k = printRec(root->getRight());
        }
        else {
            k = printRec(root->getLeft());
            if (root->getEntry()->getActive() == true) cout << root->getEntry()->getName() << " : " << root->getEntry()->getIPaddress() << " : active" << endl;
            else cout << root->getEntry()->getName() << " : " << root->getEntry()->getIPaddress() << " : inactive" <<endl;
            if (root->getRight()!= NULL) k = printRec(root->getRight());
        }
    }
}

//Probes count recursion function.
//returns amount of probes needed to examine to find given node
int TreeDB::probesRec(TreeNode* temp, string name, int sum) {
    if (temp->getEntry()->getName() == name) {
        sum ++;
        return sum;
    }
    else {
        if (temp->getEntry()->getName() > name) {
            sum ++;
            return (probesRec(temp->getLeft(), name, sum));
        }
        else { //the needed node is on the right side
            sum ++;
            return (probesRec(temp->getRight(), name, sum));
        }
    }
}

//Clear recursion function.
//Deletes all the elements in the tree
void TreeDB::clearRec(TreeNode* temp) {
    if (!temp) {}
    else if ((temp->getLeft()==NULL)&&(temp->getRight()==NULL)) delete temp;
    else {
        if (temp->getLeft()!=NULL) clearRec(temp->getLeft());
        if (temp->getRight()!=NULL) clearRec(temp->getRight());
        delete temp;
    }
}

//constructor
TreeDB::TreeDB() {
    root = NULL;
    countactive = 0;
}

//destructor
TreeDB::~TreeDB() {
}

// inserts the entry into the database. 
// If an entry with the same key exists in the database, 
//it returns false. Otherwise, it returns true.
bool TreeDB::insert(string name, int index, bool status) {
    DBentry * newEntry = new DBentry(name, index, status);
    if (!root) {
        root = new TreeNode(newEntry);
        probesCount ++;
        if (newEntry->getActive() == true) countactive ++;
        return false;
    }
    else return insertRec(root, newEntry);
}

// searches the database for an entry with a key equal to name.
// If the entry is found, true is returned.
// If the entry is not found, false is returned.
// Also changes status of entry if status is given as 1(to active) or -1(inactive)
//If no change is required status should be 0
bool TreeDB::find(string name, int status) {
    return findRec(root, name, status);
}

// deletes the entry with the specified name (key) from the database.
// The following removal method used (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
bool TreeDB::remove(string name) {
        cout << "Success" << endl;
        probesCount--;
        root = removeRec(root, name);
        return true;
}

// deletes all the entries in the database.
void TreeDB::clear() {
    clearRec(root);
    root = NULL;
}

// prints information about all probes stored
//prints amount of probes in the tree if a = 0,
//amount of probes examined to find given node if a != 0
int TreeDB::printProbes(string name, int a) {
    int sum = 0;
    if (a == 0) {
        if (!root) {}
        else sum = printRec(root);
    }
    else sum = probesRec(root, name, sum);
    return sum;
}

// prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const {
    cout << countactive << endl;
}