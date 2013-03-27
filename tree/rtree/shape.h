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
#include <stdio>

enum shape_names {
	dot_e,
	line_e,
	triangle_e,
	rectangle_e,
};

class Shape {
private:

//variables
	Rectangle *bounds;
	bool bounds_current;

	int num_points;
	Point *list_point;

//methods
	void fit_bounds();
	
public:

//constructor
	Shape();

//inspectors
	Rectangle *get_bounds();
	int get_hilbert();

	void add_point();

	bool check_intersection( Point *point );
	bool check_intersection( Shape *shape );
	bool check_intersection( Rectangle *rectangle );

//methods
	void rotate();
	void move();

//sugar
	bool operator>( Shape &shape );
	bool operator<( Shape &shape );
	bool operator==( Shape &shape );
	void operator=( Shape &shape );
};


class Rectangle {
private:

//variables
	Point p_ul;
	Point p_ur;
	Point p_ll;
	Point p_lr;
	Point p_center;

	int min_x, max_x;
	int min_y, max_y;
	int width;
	int height;

public:

//constructors
	Rectangle();
	Rectangle( int min_x, int min_y, int max_x, int max_y );

//inspectors
	bool check_intersection( Point *point );
	bool check_intersection( Shape *shape );
	bool check_intersection( Rectangle *rectangle );

	int get_hilbert();

//mutators
	void set( int min_x, int min_y, int max_x, int max_y );

//sugar
	bool operator>( Rectangle &rectangle );
	bool operator<( Rectangle &rectangle );
	bool operator==( Rectangle &rectangle );
	void operator=( Rectangle &rectangle ); // not implemented
};

