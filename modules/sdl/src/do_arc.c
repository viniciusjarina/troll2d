/* Original arc routine from allegro (allegro.cc) gfx.c

  Authors: By Shawn Hargreaves.
  Romano Signorelli. 
*/

#define INTERNAL_MIN(x,y)     (((x) < (y)) ? (x) : (y))
#define MATH_PI        3.14159265358979323846

#include <math.h>

static void get_point_on_arc(int r, long a, int *out_x, int *out_y)
{
	double s, c;
	
	double double_a = a * (MATH_PI * 2 / (1 << 24));
	s = sin(double_a);
	c = cos(double_a);
	s = -s * r;
	c = c * r;
	*out_x = (int)((c < 0) ? (c - 0.5) : (c + 0.5));
	*out_y = (int)((s < 0) ? (s - 0.5) : (s + 0.5));
}



/* do_arc:
*  Helper function for the arc function. Calculates the points in an arc
*  of radius r around point x, y, going anticlockwise from fixed point
*  binary angle ang1 to ang2, and calls the specified routine for each one. 
*  The output proc will be passed first a copy of the bmp parameter, then 
*  the x, y point, then a copy of the d parameter (so putpixel() can be 
*  used as the callback).
*/
void do_arc(void * bmp, short x, short y,short start,short end, int r, void * d, void (*proc)(void* bmp,int x,int y,void * data))
{
	long ang1;
	long ang2;
	
	/* start position */
	int sx, sy;
	/* current position */
	int px, py;
	/* end position */
	int ex, ey;
	/* square of radius of circle */
	long rr;
	/* difference between main radius squared and radius squared of three
	potential next points */
	long rr1, rr2, rr3;
	/* square of x and of y */
	unsigned long xx, yy, xx_new, yy_new;
	/* start quadrant, current quadrant and end quadrant */
	int sq, q, qe;
	/* direction of movement */
	int dx, dy;
	/* temporary variable for determining if we have reached end point */
	int det;
	
	ang1 = (long)(start << 16);
	ang2 = (long)(end << 16);
	
	/* Calculate the start point and the end point. */
	/* We have to flip y because bitmaps count y coordinates downwards. */
	get_point_on_arc(r, ang1, &sx, &sy);
	px = sx;
	py = sy;
	get_point_on_arc(r, ang2, &ex, &ey);
	
	rr = r*r;
	xx = px*px;
	yy = py*py - rr;
	
	/* Find start quadrant. */
	if (px >= 0) {
		if (py <= 0)
			q = 0;                           /* quadrant 0 */
		else
			q = 3;                           /* quadrant 3 */
	}
	else {
		if (py < 0)
			q = 1;                           /* quadrant 1 */
		else
			q = 2;                           /* quadrant 2 */
	}
	sq = q;
	
	/* Find end quadrant. */
	if (ex >= 0) {
		if (ey <= 0)
			qe = 0;                          /* quadrant 0 */
		else
			qe = 3;                          /* quadrant 3 */
	}
	else {
		if (ey < 0)
			qe = 1;                          /* quadrant 1 */
		else
			qe = 2;                          /* quadrant 2 */
	}
	
	if (q > qe) {
		/* qe must come after q. */
		qe += 4;
	}
	else if (q == qe) {
	/* If q==qe but the beginning comes after the end, make qe be
	* strictly after q.
		*/
		if (((ang2&0xffffff) < (ang1&0xffffff)) ||
			(((ang1&0xffffff) < 0x400000) && ((ang2&0xffffff) >= 0xc00000)))
			qe += 4;
	}
	
	/* initial direction of movement */
	if (((q+1)&2) == 0)
		dy = -1;
	else
		dy = 1;
	if ((q&2) == 0)
		dx = -1;
	else
		dx = 1;
	
	while (1) {
	/* Change quadrant when needed.
	* dx and dy determine the possible directions to go in this
	* quadrant, so they must be updated when we change quadrant.
		*/
		if ((q&1) == 0) {
			if (px == 0) {
				if (qe == q)
					break;
				q++;
				dy = -dy;
			}
		}
		else {
			if (py == 0) {
				if (qe == q)
					break;
				q++;
				dx = -dx;
			}
		}
		
		/* Are we in the final quadrant? */
		if (qe == q) {
			/* Have we reached (or passed) the end point both in x and y? */
			det = 0;
			
			if (dy > 0) {
				if (py >= ey)
					det++;
			}
			else {
				if (py <= ey)
					det++;
			}
			if (dx > 0) {
				if (px >= ex)
					det++;
			}
			else {
				if (px <= ex)
					det++;
			}
			
			if (det == 2)
				break;
		}
		
		proc(bmp, x+px, y+py, d);
		
		/* From here, we have only 3 possible directions of movement, eg.
		* for the first quadrant:
		*
		*    .........
		*    .........
		*    ......21.
		*    ......3*.
		*
		* These are reached by adding dx to px and/or adding dy to py.
		* We need to find which of these points gives the best
		* approximation of the (square of the) radius.
		*/
		
		xx_new = (px+dx) * (px+dx);
		yy_new = (py+dy) * (py+dy) - rr;
		rr1 = xx_new + yy;
		rr2 = xx_new + yy_new;
		rr3 = xx     + yy_new;
		
		/* Set rr1, rr2, rr3 to be the difference from the main radius of the
		* three points.
		*/
		if (rr1 < 0)
			rr1 = -rr1;
		if (rr2 < 0)
			rr2 = -rr2;
		if (rr3 < 0)
			rr3 = -rr3;
		
		if (rr3 >= INTERNAL_MIN(rr1, rr2)) {
			px += dx;
			xx = xx_new;
		}
		if (rr1 > INTERNAL_MIN(rr2, rr3)) {
			py += dy;
			yy = yy_new;
		}
	}
	/* Only draw last point if it doesn't overlap with first one. */
	if ((px != sx) || (py != sy) || (sq == qe))
		proc(bmp, x+px, y+py, d);
}
