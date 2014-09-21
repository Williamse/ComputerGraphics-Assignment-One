//
//  Rasterizer.cpp
//  
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//

#include "Rasterizer.h"
#include "simpleCanvas.h"
#include <iostream>
#include <cmath>

/**
 *
 * Simple class that performs rasterization algorithms
 *
 */

/**
 * Constructor
 *
 * @param n number of scanlines
 *
 */
Rasterizer::Rasterizer (int n) : n_scanlines (n)
{
}

/**
*Swaps what a and b are pointing to
*@param p0 - pointer to first point to swap
* @param p1 - pointer to second point to swap
*/
void Rasterizer::swapPoints(int* p0, int* p1)
{
    int tempLoc = *p0;
    *p0 = *p1;
    *p1 = tempLoc;
}

/**
 * Draw a line from (x0,y0) to (x1, y1) on the simpleCanvas C.
 *
 * Implementation should be using the Midpoint Method
 *
 * You are to add the implementation here using only calls
 * to C.setPixel()
 *
 * @param x0 x coord of first endpoint
 * @param y0 y coord of first endpoint
 * @param x1 x coord of second endpoint
 * @param y1 y coord of second endpoint
 * @param C  The canvas on which to apply the draw command.
 */
void Rasterizer::drawLine (int x0, int y0, int x1, int y1, simpleCanvas &C)
{
  
    //Make sure our first x is on the left always
    if(x0 > x1)
    {
        swapPoints(&x0,&x1);
        swapPoints(&y0,&y1);
    }


    int dE,dNE,x,y,d;
    int dy = (y1 - y0),dx = (x1-x0);

    bool largestSlope = std::abs(y1 - y0) > std::abs(x1 - x0); 
  
    //If positive slope
    if(dy >= 0 && dy <= dx) // slope is 0 ,1
    {
        d = 2 * dy - dx;
        x = x0;
        y = y0;
        dE = 2 * dy;
        dNE = 2 * (dy - dx);
	

        while(x < x1)
        {
           if(d <=0) {
             std::cout << "here" << std::endl;
             d = d + dE;
           }
           else
           {
              std::cout << "here1" <<std::endl;
               y =  y + 1;
               d = d + dNE;
           } 
           x++;
           std::cout << "Writing Pixel (" << x << "," << y << ")" << std::endl;
           C.setPixel(x,y);
           
     //   C.setPixel (0,1, 3.0, 4.0, 2.0);
        }
    }
    if(dy >= 0 && dy > dx) //steep
    {
        d = 2 * dx - dy;
        x = x0;
        y = y0;
        dE = 2 * dx;
        dNE = 2 * (dx - dy);


        while(x < x1)
        {
           if(d <=0) {
             d = d + dE;
           }
           else
           {
              x++;
              d = d + dNE;
           }
           y++;
           std::cout << "Writing Pixel (" << x << "," << y << ")" << std::endl;
           C.setPixel(x,y);

     //   C.setPixel (0,1, 3.0, 4.0, 2.0);
        }
    }
    //Negative non steep slope
    if( dy < 0 && std::abs(dy) < dx) 
    {
       dy = std::abs(dy);
       dx = std::abs(dx);
        x = x0;
        y = y0;
        dE = 2 * dy;
        dNE = 2 * (dy - dx);
        d = 2*dy - dx;
        
        while( x < x1)
        {
             if(d <= 0)
             {
                 d = d + dE;
             }
             else
             {
                 d = d + dNE;
                 y = y -1;
             }
             x++;
        
            std::cout << "Writing Pixel (" << x << "," << y << ")" << std::endl;
            C.setPixel(x,y);
       }
    }     
}
