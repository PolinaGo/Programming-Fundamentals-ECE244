/* 
 * File:   Rectangle.cpp
 * Author: Govorkova Polina
 * 
 * Created on December 3, 2017, 11:40 PM
 */

#include "Rectangle.h"

#include <iostream>
#include <cmath>
#include "easygl.h"

using namespace std;


// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.
Rectangle::Rectangle (string _name, string _colour, float _xcen, float _ycen,
            float xcoords[4], float ycoords[4]) 
              : Shape (_name, _colour, _xcen, _ycen) {
   for (int i = 0; i < 4; i++) {
      relVertex[i].x = xcoords[i];
      relVertex[i].y = ycoords[i];
   }
}


Rectangle::~Rectangle () {
   // No dynamic memory to delete
}

//prints rectangle
void Rectangle::print () const {
   Shape::print();
   cout << "rectangle";
   cout << " width: " << (relVertex[1].x - relVertex[0].x) << " height: " << (relVertex[3].y - relVertex[0].y);
   cout << endl;
}

//scales vectors to vertices from center
void Rectangle::scale (float scaleFac) {
   for (int i = 0; i < 4; i++) {
      relVertex[i].x *= scaleFac;
      relVertex[i].y *= scaleFac;
   }
}
   
//computes area
float Rectangle::computeArea () const {
   // width * height
   float area;
   
   area = ((relVertex[1].x - relVertex[0].x)*(relVertex[3].y - relVertex[0].y));
   return area;
}

//computes perimeter
float Rectangle::computePerimeter () const {
   //width*2+height*2
   float perimeter;
   
      perimeter = (relVertex[1].x - relVertex[0].x)*2 + (relVertex[3].y - relVertex[0].y)*2;

   return perimeter;
}

//draws rectangle
void Rectangle::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw the triangle
   // using the easygl::draw_polygon call.
   t_point coords[4];  // This data type is in easygl_constants.h
   for (int i = 0; i < 4; i++) {
      coords[i].x = getXcen() + relVertex[i].x;
      coords[i].y = getYcen() + relVertex[i].y;
   }
   window->gl_setcolor(getColour());
   window->gl_fillpoly(coords, 4);
}

//checks whether point is inside - inside boarders
bool Rectangle::pointInside (float x, float y) const {

   t_point click;
   click.x = x - getXcen();
   click.y = y - getYcen();
   
   bool check = ((click.x <= relVertex[2].x)&&(click.x >= relVertex[3].x)&&(click.y <= relVertex[3].y) && (click.y >= relVertex[1].y));
   return check;
}


// Private helper functions below.  Working out triangle area etc. 
// requires some vector math, so these helper functions are useful.

// Return the (x,y) vector between start and end points.
t_point Rectangle::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}