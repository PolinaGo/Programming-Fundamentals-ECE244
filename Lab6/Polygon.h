/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Polygon.h
 * Author: govorkov
 *
 * Created on December 4, 2017, 12:32 AM
 */

#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"
#include "easygl.h"

class Polygon : public Shape {
private:
   // t_point is a structure defined in easygl.h.  It has two members,
   // .x and .y, storing a 2D point.  We store 3 points in relVertex; 
   // each is the (x,y) offset of one triangle vertex from the shape 
   // center.
   t_point relVertex[100];  
   int vertNumber; //counts the amount of vertices
   
   // Private helper functions.
   t_point getVecBetweenPoints (t_point start, t_point end) const;
   
public:
   Polygon (string _name, string _colour, float _xcen, float _ycen,
            float _xcoords[100], float _ycoords[100], int _number);
   
   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtual. But it is good 
   // practice to repeat it again here, for clarity.
   virtual ~Polygon();
  
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};

#endif /* POLYGON_H */

