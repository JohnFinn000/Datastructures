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

class Rectangle;

class Shape {
private:

public:
//variables
	Rectangle *bounds;
	bool bounds_current;

	int num_points;
	Dynamic_array<Point*> list_points;

//methods
	void fit_bounds();
	

//constructor
	Shape();

//inspectors
	Rectangle *get_bounds();
	uint64_t get_hilbert();

	Point **get_points( int &size );
	void add_point( uint64_t x, uint64_t y );
	void add_point( Point *p );

	bool check_intersection( Point *point );
	bool check_intersection( Shape *shape );
	bool check_intersection( Rectangle *rectangle );

//methods
	void rotate( uint64_t x, uint64_t y );
	void move(   uint64_t x, uint64_t y );

//sugar
	bool operator>(  Shape &shape );
	bool operator<(  Shape &shape );
	bool operator==( Shape &shape );
	void operator=(  Shape &shape );
};


class Rectangle {
private:

public:
//variables
	Point *p_ul;
	Point *p_ur;
	Point *p_ll;
	Point *p_lr;
	Point *p_center;

	uint64_t min_x, max_x;
	uint64_t min_y, max_y;
	uint64_t width;
	uint64_t height;


//constructors
	Rectangle();
	Rectangle( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y );

//inspectors
	bool check_intersection( Point *point );
	bool check_intersection( Shape *shape );
	bool check_intersection( Rectangle *rectangle );

	uint64_t get_hilbert();

//mutators
	void set( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y );

//sugar
	bool operator>( Rectangle &rectangle );
	bool operator<( Rectangle &rectangle );
	bool operator==( Rectangle &rectangle );
	void operator=( Rectangle &rectangle ); // not implemented
};

