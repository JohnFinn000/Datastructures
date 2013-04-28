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

class Shape {

protected:
public:
//variables
	Dynamic_array<Point*> list_points;

//methods
	
public:
//constructor
	Shape();

//inspectors
	Point **get_points( int &size );
	virtual void add_point( uint64_t x, uint64_t y );
	virtual void add_point( Point *p );

	void stretch( uint64_t &min_x, uint64_t &min_y, uint64_t &max_x, uint64_t &max_y );

	intersection_type check_intersection( Point *point );
	intersection_type check_intersection( Shape *shape );
	intersection_type check_intersection( Rectangle *rectangle );

    // complete intersection = the shape encloses this shape in it's entirety
    // partial intersection = the shape is partially inside this shape

//methods
	void rotate( uint64_t x, uint64_t y );
	void move(   uint64_t x, uint64_t y );

//sugar
	void operator=(  Shape &shape );


};

class Rectangle : public Shape {


};

class Bounding_box {

protected:
public:
//variables
	Point *p_ul;
	Point *p_ur;
	Point *p_ll;
	Point *p_lr;
	Point *p_center; // TODO: make this lazy

	uint64_t min_x, max_x;
	uint64_t min_y, max_y;
	uint64_t width;
	uint64_t height;


public:
//constructors
	Bounding_box();
	Bounding_box( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y );

//inspectors
	intersection_type check_intersection( Point *point );
	intersection_type check_intersection( Shape *shape );
	intersection_type check_intersection( Bounding_box *bounding_box );

	uint64_t get_hilbert();

//mutators
	void set( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y );
	void get( uint64_t &min_x, uint64_t &min_y, uint64_t &max_x, uint64_t &max_y );
	void stretch( uint64_t &min_x, uint64_t &min_y, uint64_t &max_x, uint64_t &max_y );

//sugar
	bool operator>(  Bounding_box &rectangle );
	bool operator>(  Bounding_box *rectangle );
	bool operator<(  Bounding_box &rectangle );
	bool operator<(  Bounding_box *rectangle );
	bool operator==( Bounding_box &rectangle );
	bool operator==( Bounding_box *rectangle );
};

#endif

