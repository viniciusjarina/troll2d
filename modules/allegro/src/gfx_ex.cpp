
#include <allegro.h>

#include "gfx_ex.h"

// Compute the total of points in a arc
static void compute_arc_total_points(BITMAP *bmp, int x, int y, int d)
{
	int * p_total_points = (int*)d;
	(*p_total_points)++;
}

// Store each point of arc
static void compute_arc_points(BITMAP *bmp, int x, int y, int  d)
{
	int * *p_arr_points = (int * *)d;
	
	*(*p_arr_points) = x;
	(*p_arr_points)++;
	*(*p_arr_points) = y;
	(*p_arr_points)++;
}

// draw a filled arc (missing in allegro, I did the mine)

void arc_fill(BITMAP *bmp, int x,int y, fixed ang1,fixed ang2, int r, int color)
{
	int total_points = 1;
	
	do_arc(bmp,x,y,ang1,ang2,r,(int)&total_points,compute_arc_total_points);
	
	if(total_points < 2)
		return;
	
	int * points = new int[2 * total_points];
	int * point2 = points;
	
	*point2 = x;
	point2++;
	*point2 = y;
	point2++;
	
	do_arc(bmp,x,y,ang1,ang2,r,(int)&point2,compute_arc_points);
	
	polygon(bmp,total_points,points,color);
	
	delete [] points;		
}

void round_rectfill(BITMAP * bmp, int x, int y, int w, int h,int r,int color)
{
	int total_points = 0;
	
	do_arc(NULL,0,0,itofix(0),itofix(64),r,(int)&total_points,compute_arc_total_points);
	do_arc(NULL,0,0,itofix(64),itofix(128),r,(int)&total_points,compute_arc_total_points);
	do_arc(NULL,0,0,itofix(128),itofix(192),r,(int)&total_points,compute_arc_total_points);
	do_arc(NULL,0,0,itofix(192),itofix(255),r,(int)&total_points,compute_arc_total_points);
	
	if(total_points < 2)
		return;
	
	int * points = new int[2 * total_points];
	int * point2 = points;
	
	
	do_arc(NULL,x + w - r,y + r,itofix(0),itofix(64),r,(int)&point2,compute_arc_points);
	do_arc(NULL,x + r,y + r,itofix(64),itofix(128),r,(int)&point2,compute_arc_points);
	do_arc(NULL,x + r,y + h - r,itofix(128),itofix(192),r,(int)&point2,compute_arc_points);
	do_arc(NULL,x + w - r,y + h - r,itofix(192),itofix(255),r,(int)&point2,compute_arc_points);
	
	polygon(bmp,total_points,points,color);
	
	delete [] points;
}
