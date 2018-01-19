/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TreeDB.h
 * Author: govorkov
 *
 * Created on November 16, 2017, 4:58 PM
 */

#ifndef _TREEDB_H
#define _TREEDB_H

#include "TreeNode.h"
#include "DBentry.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdio.h>

class TreeDB {

private:
   TreeNode * root;
   int probesCount;
   int countactive;
   
//HELPFUL PRIVATE RECURSION FUCTIONS ALLOW TO TRAVERSE THE TREE
   //Detailed description of each in .cpp file
   bool insertRec(TreeNode* root, DBentry* newEntry);
   bool findRec(TreeNode* root, string name, int status);
   int printRec(TreeNode* root);
   int probesRec(TreeNode*root, string name, int sum);
   void clearRec(TreeNode*root);
   TreeNode* mostRight(TreeNode*root);
   TreeNode* removeRec(TreeNode*root, string name);
   
public:
   // the default constructor, creates an empty database.
   TreeDB();

   // the destructor, deletes empty database.
   ~TreeDB();

// inserts the entry into the database. 
// If an entry with the same key exists in the database, 
//it returns false. Otherwise, it returns true.
   bool insert(string name, int index, bool status); 

// searches the database for an entry with a key equal to name.
// If the entry is found, true is returned.
// If the entry is not found, false is returned.
// Also changes status of entry if status is given as 1(to active) or -1(inactive)
//If no change is required status should be 0
   bool find(string name, int status);

// deletes the entry with the specified name (key) from the database.
// The following removal method used (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
   bool remove(string name);
	
// deletes all the entries in the database.
   void clear();
    
// prints information about all probes stored
//prints amount of probes in the tree if a = 0,
//amount of probes examined to find given node if a != 0
   int printProbes(string name, int a);
   
// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
   void countActive () const;
};  
   
#endif 