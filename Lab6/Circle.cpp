/* 
 * File:   Circle.cpp
 * Author: Govorkova Polina
 * 
 * Created on December 3, 2017, 11:40 PM
 */

#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Circle.h"
using namespace std;


// Constructor. First set up base class (Shape), then store the 
//radius
Circle::Circle (string _name, string _colour, float _xcen, float _ycen,
             float _rad) 
              : Shape (_name, _colour, _xcen, _ycen) {
    rad = _rad;
}

Circle::~Circle () {
   // No dynamic memory to delete
}
//prints the figure
void Circle::print () const {
   Shape::print();
   cout << "circle";
   cout << " radius: " << rad;
   cout << endl;
}
//scales the vectors
void Circle::scale (float scaleFac) {
    rad *= scaleFac;
}
//computes area   
float Circle::computeArea () const {
   // area = pi*r^2
   float area;
   area = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651*rad*rad;
   return area;
}
//computes perimeter
float Circle::computePerimeter () const {
    // perimeter = 2 * pi* r
   float perimeter;
   perimeter = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651*2*rad;
   return perimeter;
}

//draws circle
void Circle::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw

   window->gl_setcolor(getColour());
   window->gl_fillarc (getXcen(), getYcen(), rad, 0, 360);
}

//checks whether point is inside - checks whether distance to center is greater than radius
bool Circle::pointInside (float x, float y) const {
   // Check whether point is inside
   t_point click;
   float distance;
   click.x = x - getXcen();
   click.y = y - getYcen();
   distance = sqrt(click.x*click.x + click.y*click.y);
   return (distance <= rad);
}