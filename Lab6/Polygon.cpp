/* 
 * File:   Polygon.cpp
 * Author: Govorkova Polina
 * 
 * Created on December 3, 2017, 11:40 PM
 */

#include "Polygon.h"

#include <iostream>
#include <cmath>
#include "easygl.h"
using namespace std;


// Constructor. First set up base class (Shape), then store the 
// vertices, which are 4 (x,y) points giving offsets from the Shape center 
// to each vertex.
Polygon::Polygon (string _name, string _colour, float _xcen, float _ycen,
            float xcoords[100], float ycoords[100], int _number) 
              : Shape (_name, _colour, _xcen, _ycen) {
   vertNumber = _number;
   for (int i = 0; i < _number; i++) {
      relVertex[i].x = xcoords[i];
      relVertex[i].y = ycoords[i];
   }
}


Polygon::~Polygon () {
   // No dynamic memory to delete
}

//prints polygon
void Polygon::print () const {
   Shape::print();
   cout << "polygon";
   for (int i = 0; i < vertNumber; i++) {
      cout << " (" << getXcen() + relVertex[i].x << "," 
              << getYcen() + relVertex[i].y << ")";
   }
   cout << endl;
}

//scales vectors from center
void Polygon::scale (float scaleFac) {
   for (int i = 0; i < vertNumber; i++) {
      relVertex[i].x *= scaleFac;
      relVertex[i].y *= scaleFac;
   }
}
   
//area
float Polygon::computeArea () const {
   // formula provided in the link
   float area;
   area = 0;         // Accumulates area in the loop
   int j = vertNumber-1;  // The last vertex is the 'previous' one to the first

   for (int i=0; i<vertNumber; i++)
    { area = area + ((relVertex[j].x+relVertex[i].x) * (relVertex[j].y-relVertex[i].y)); 
      j = i;  //j is previous vertex to i
    }
   return abs(area/2);
}

//perimeter, sum of all the sides
float Polygon::computePerimeter () const {
   float perimeter = 0;
   float sideLength;
   int endIndex;
   t_point dist;
   
   for (int i = 0; i < vertNumber; i++) {
      endIndex = (i + 1) % vertNumber;
      dist = getVecBetweenPoints (relVertex[i], relVertex[endIndex]);
      sideLength = sqrt (dist.x * dist.x + dist.y * dist.y);
      perimeter += sideLength;
   }
   return perimeter;
}

//draw command
void Polygon::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw the triangle
   // using the easygl::draw_polygon call.
   t_point coords[100];  // This data type is in easygl_constants.h
   for (int i = 0; i < vertNumber; i++) {
      coords[i].x = getXcen() + relVertex[i].x;
      coords[i].y = getYcen() + relVertex[i].y;
   }
   window->gl_setcolor(getColour());
   window->gl_fillpoly(coords, vertNumber);
}

//checks whether point is inside
bool Polygon::pointInside (float x, float y) const {
   // Make a point that corresponds to where you clicked. Since all my
   // vertices are relative to the  center, it is more convenient
   // to also shift the click point so it is an offset from the 
   // center.
   t_point click;
   click.x = x - getXcen();
   click.y = y - getYcen();
   
   t_point vecOfSide;
   float distanceAlongVector, yDistance;
   int endIndex;
   int sidesToLeft = 0;
   
   for (int istart = 0; istart < vertNumber; istart++) {
      endIndex = (istart + 1) % vertNumber; // Next vertex after istart
      vecOfSide = getVecBetweenPoints (relVertex[istart], relVertex[endIndex]);
      yDistance = (click.y - relVertex[istart].y);
      if (vecOfSide.y != 0) {
          distanceAlongVector = yDistance / vecOfSide.y;
      }
      else if (yDistance == 0) {
          distanceAlongVector = 0;
      }
      else {
          distanceAlongVector = 1e10; // Really infinity, but this is big enough
      }
      
      // We intersect this side if the distance (scaling) along the side vector to 
      // get to our "click" y point is between 0 and 1.  Count the first 
      // endpoint of the side as being part of the line (distanceAlongVector = 0)
      // but don't count the second endPoint; we'll intersect that point later 
      // when we check the next side.
      if (distanceAlongVector >= 0 && distanceAlongVector < 1) {
         float xIntersection = relVertex[istart].x + vecOfSide.x * distanceAlongVector;
         if (xIntersection <= click.x ) 
             sidesToLeft++;
      }
   }
   
   return (sidesToLeft == 1);
}


// Private helper functions below.  Working out triangle area etc. 
// requires some vector math, so these helper functions are useful.

// Return the (x,y) vector between start and end points.
t_point Polygon::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}

