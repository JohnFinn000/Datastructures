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

class Bounding_box;

class Shape {

protected:
//variables
	Dynamic_array<Point*> list_points;

//methods
	
public:
//constructor
	Shape();

//inspectors
	uint64_t get_hilbert();

	Point **get_points( int &size );
	virtual void add_point( uint64_t x, uint64_t y );
	virtual void add_point( Point *p );

	virtual bool check_intersection( Point *point );
	virtual bool check_intersection( Shape *shape );
	virtual bool check_intersection( Rectangle *rectangle );

    // full intersection = the shape encloses this shape in it's entirety
    // partial intersection = the shape is partially inside this shape

//methods
	void rotate( uint64_t x, uint64_t y );
	void move(   uint64_t x, uint64_t y );

//sugar
	bool operator>(  Shape &shape );
	bool operator<(  Shape &shape );
	bool operator==( Shape &shape );
	void operator=(  Shape &shape );


};

class Bounded_shape {

protected:
//variables

    template <class Bounding_box>
    class Lazy_bounds : public Lazy<Bounding_box> {
        Dynamic_array<Point*> *points;
        protected:
        void evaluate() {
            uint64_t min_x;
            uint64_t min_y;
            uint64_t max_x;
            uint64_t max_y;

            Dynamic_array<Point*>::iterator *iter = points.begin();

            min_x = max_x = iter->get()->get_x();
            min_y = max_y = iter->get()->get_y();

            for( ; !iter->end(); iter->next() ) { 
                iter->get()->get_x() > max_x ? max_x = iter->get()->get_x() : 
                iter->get()->get_x() < min_x ? min_x = iter->get()->get_x() : 0;

                iter->get()->get_y() > max_y ? max_y = iter->get()->get_y() : 
                iter->get()->get_y() < min_y ? min_y = iter->get()->get_y() : 0;
            }   

            value.set( min_x, min_y, max_x, max_y );

        }
        public:
        void init( Dynamic_array<Point*> *p ) {
            points = p;
        }
    }

	Lazy_bounds<Bounding_box> bounds;

public:
//constructor
	Bounded_shape();

//inspectors
	Bounding_box *get_bounds();
	uint64_t get_hilbert();

	void add_point( uint64_t x, uint64_t y );
	void add_point( Point *p );

	bool check_intersection( Point *point );
	bool check_intersection( Shape *shape );
	bool check_intersection( Rectangle *rectangle );

//methods
	void rotate( uint64_t x, uint64_t y );
	void move(   uint64_t x, uint64_t y );


};

class Bounding_box : public Shape {

protected:
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
	//bool check_intersection( Point *point );
	//bool check_intersection( Shape *shape );
	//bool check_intersection( Bounding_box *bounding_box );

	uint64_t get_hilbert();

//mutators
	void set( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y );

//sugar
	//bool operator>( Rectangle &rectangle );
	//bool operator<( Rectangle &rectangle );
	//bool operator==( Rectangle &rectangle );
	//void operator=( Rectangle &rectangle ); // not implemented
};

#endif

