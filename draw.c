#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  if(points -> cols == points -> lastcol){
    grow_matrix(points, points -> lastcol + 1);
  }
  points -> m[0][points -> lastcol] = x;
  points -> m[1][points -> lastcol] = y;
  points -> m[2][points -> lastcol] = z;
  points -> m[3][points -> lastcol] = 1;
  points -> lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
int i;
for (i = 0; i < points -> lastcol - 1; i+=2){
  draw_line(points -> m[0][i], points -> m[1][i], points -> m[0][i + 1], points -> m[1][i + 1], s, c);
  }
}

int octant(int x0, int y0, int x1, int y1){
  int deltax = x1 - x0;
  int deltay = y1 - y0;

  //octant 1 with bound 0 to 1
  if (deltay >= 0 && deltax >= deltay){
    return 1;
  }
  //octant 2 could tend to 1
  else if (deltay >= 0 && deltax <= deltay){
    return 2;
  }
  //octant 7 with bound of -1 to 0
  else if (deltay < 0 && deltax <= -1 * deltay){
    return 7;
  }
  //octant 8 could tend to -1
  else if (deltay < 0 && deltax >= -1 * deltay){
    return 8;
  }
  //error
  else {

  return -1;

  }
}

void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  if (x1 < x0){
    int temp = x0;
    x0 = x1;
    x1 = temp;  
    temp = y0;
    y1 = y0;
    y1 = temp;
  }

  int A = y1 - y0;
  int B = x0 - x1;
  int d;
  int add_octant = octant(x0, y0, x1, y1);
  int x = x0;
  int y = y0;

  if (add_octant == 1){
    d = 2 * A + B;
    while (x <= x1){
      plot(s, c, x, y);
      if (d > 0){
        y++;
        d += 2 * B;
      }
      x++;
      d += 2 * A;
    }
  }

  else if (add_octant == 2){
    d = A + 2 * B;
    while (y <= y1){
      plot(s, c, x, y);
      if (d < 0){
        x++;
        d += 2 * A;
      }
      y++;
      d += 2 * B;
    }
  }

  else if (add_octant == 7){
    d = A - 2 * B;
    while (y >= y1){
      plot(s, c, x, y);
      if (d > 0){
        x++;
        d += 2 * A;
      }
      y--;
      d -= 2 * B;
    }
  }

  else{

    d = 2 * A - B;
    while (x <= x1){
      plot(s, c, x, y);
      if (d < 0){
        y--;
        d -= 2 * B;
      }
      x++;
      d += 2 * B;
    }
  }
}