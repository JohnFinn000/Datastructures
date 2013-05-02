/*
 * =====================================================================================
 *
 *       Filename:  shape.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/26/2013 03:49:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _SHAPE_H__
#define _SHAPE_H__

#include <stdlib.h>
#include <stdint.h>
#include "point.h"
#include "../../dynamic_array/dynamic_array.hh"

enum shape_names {
	dot_e,
	line_e,
	triangle_e,
	rectangle_e,
};

enum intersection_type {
	no_intersection_e,
	partial_intersection_e,
	complete_intersection_e,
};

class Bounding_box;
class Rectangle;


/*
 * =====================================================================================
 *        Class:  Shape
 *  Description:  
 * =====================================================================================
 */
class Shape {
public:
    /* ====================  LIFECYCLE     ======================================= */
    Shape();                             /* constructor */
    ~Shape();                             /* destructor */

    /* ====================  ACCESSORS     ======================================= */
	Point **get_points( int &size );

	void stretch( uint64_t &min_x, uint64_t &min_y, uint64_t &max_x, uint64_t &max_y );

	intersection_type check_intersection( Point *point );
	intersection_type check_intersection( Shape *shape );
	intersection_type check_intersection( Rectangle *rectangle );

    // complete intersection = the shape encloses this shape in it's entirety
    // partial intersection = the shape is partially inside this shape

    /* ====================  MUTATORS      ======================================= */
	virtual void add_point( uint64_t x, uint64_t y );
	virtual void add_point( Point *p );

    //methods
	void rotate( uint64_t x, uint64_t y );
	void move(   uint64_t x, uint64_t y );

    /* ====================  OPERATORS     ======================================= */
	void operator=(  Shape &shape );

protected:
public:
    /* ====================  DATA MEMBERS  ======================================= */
	Dynamic_array<Point*> list_points;

}; /* -----  end of class Shape  ----- */

class Rectangle : public Shape {


};


/*
 * =====================================================================================
 *        Class:  Bounding_box
 *  Description:  A bounding box is just an axis aligned rectangle
 * =====================================================================================
 */
class Bounding_box {
public:
    /* ====================  LIFECYCLE     ======================================= */
	Bounding_box();                             /* constructor */
	Bounding_box( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y );
	~Bounding_box();                            /* destructor */

    /* ====================  ACCESSORS     ======================================= */
	intersection_type check_intersection( Point *point );
	intersection_type check_intersection( Shape *shape );
	intersection_type check_intersection( Bounding_box *bounding_box );

	void get( uint64_t &min_x, uint64_t &min_y, uint64_t &max_x, uint64_t &max_y );
	void stretch( uint64_t &min_x, uint64_t &min_y, uint64_t &max_x, uint64_t &max_y );
	uint64_t get_hilbert();

    /* ====================  MUTATORS      ======================================= */
	void set( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y );

    /* ====================  OPERATORS     ======================================= */
	bool operator>(  Bounding_box &rectangle );
	bool operator>(  Bounding_box *rectangle );
	bool operator<(  Bounding_box &rectangle );
	bool operator<(  Bounding_box *rectangle );
	bool operator==( Bounding_box &rectangle );
	bool operator==( Bounding_box *rectangle );

protected:
public:
    /* ====================  DATA MEMBERS  ======================================= */
	Point *p_ul;
	Point *p_ur;
	Point *p_ll;
	Point *p_lr;
	Point *p_center; // TODO: make this lazy

	uint64_t min_x, max_x;
	uint64_t min_y, max_y;
	uint64_t width;
	uint64_t height;


}; /* -----  end of class Bounding_box  ----- */

#endif

