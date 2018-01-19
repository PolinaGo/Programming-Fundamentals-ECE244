/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Circle.h
 * Author: govorkov
 *
 * Created on December 4, 2017, 12:35 AM
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include "easygl.h"

class Circle : public Shape {
private:
    //radius
   float rad;
   
public:
   Circle (string _name, string _colour, float _xcen, float _ycen,
            float _rad);
   
   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtual. But it is good 
   // practice to repeat it again here, for clarity.
   virtual ~Circle();
   
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};

#endif /* CIRCLE_H */

