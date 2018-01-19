/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rectangle.h
 * Author: govorkov
 *
 * Created on December 3, 2017, 11:40 PM
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "easygl.h"

class Rectangle : public Shape {
private:
   // t_point is a structure defined in easygl.h.  It has two members,
   // .x and .y, storing a 2D point.  We store 4 points in relVertex; 
   // each is the (x,y) offset of one rectangle vertex from the shape 
   // center.
   t_point relVertex[4];   
   
   // Private helper functions.
   t_point getVecBetweenPoints (t_point start, t_point end) const;
   
public:
   Rectangle (string _name, string _colour, float _xcen, float _ycen,
            float _xcoords[4], float _ycoords[4]);
   
   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtual. But it is good 
   // practice to repeat it again here, for clarity.
   virtual ~Rectangle();
   
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};

#endif /* RECTANGLE_H */

