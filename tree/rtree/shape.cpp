/*
 * =====================================================================================
 *
 *       Filename:  shape.cpp
 *
 *    Description:  shape classes
 *
 *        Version:  1.0
 *        Created:  03/26/2013 03:48:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "shape.h"

//Shape
//constructor
Shape::Shape() {
	num_points = 0;
    bounds = new Rectangle( 0,0,0,0 );
	bounds_current = false;
}

//destructor
//private
void Shape::fit_bounds() {
	uint64_t min_x; // only actually needs to check new points
	uint64_t min_y;
	uint64_t max_x;
	uint64_t max_y;

	Dynamic_array<Point*>::iterator *iter = list_points.begin();

	min_x = max_x = iter->get()->get_x();
	min_y = max_y = iter->get()->get_y();

	for( ; !iter->end(); iter->next() ) {
		iter->get()->get_x() > max_x ? max_x = iter->get()->get_x() : 
		iter->get()->get_x() < min_x ? min_x = iter->get()->get_x() : 0;

		iter->get()->get_y() > max_y ? max_y = iter->get()->get_y() : 
		iter->get()->get_y() < min_y ? min_y = iter->get()->get_y() : 0;
	}

    bounds->set( min_x, min_y, max_x, max_y );

	bounds_current = true;
}

//public
Rectangle *Shape::get_bounds() {

	if( !bounds_current ) {
	 	fit_bounds();
	}

	return bounds;

}

uint64_t Shape::get_hilbert() {
	return bounds->get_hilbert();
}

Point **Shape::get_points( int &size ) {


}

void Shape::add_point( uint64_t x, uint64_t y ) {
    Point *new_point = new Point( x, y );

    list_points.add( new_point );
    ++num_points;

    bounds_current = false;
}

void Shape::add_point( Point *p ) {

    list_points.add( p );
    ++num_points;

    bounds_current = false;
}

bool Shape::check_intersection( Point *point ) {
	return bounds->check_intersection( point );
}

bool Shape::check_intersection( Rectangle *rectangle ) {
	return bounds->check_intersection( rectangle );
}

bool Shape::check_intersection( Shape *shape ) {
	return bounds->check_intersection( shape->bounds );
}

void Shape::rotate( uint64_t x, uint64_t y ) {

}

void Shape::move( uint64_t x, uint64_t y ) {
	Dynamic_array<Point*>::iterator *iter = list_points.begin();

	for( ; !iter->end(); iter->next() ) {
        iter->get()->set_x( iter->get()->get_x() + x );
        iter->get()->set_y( iter->get()->get_y() + y );
    }

    bounds_current = false;
}

bool Shape::operator>( Shape &shape ) {
	if( get_hilbert() > shape.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Shape::operator<( Shape &shape ) {
	if( get_hilbert() < shape.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Shape::operator==( Shape &shape ) {
	if( get_hilbert() == shape.get_hilbert() ) {
		return true;
	}
	return false;
}

void Shape::operator=( Shape &shape ) {

}

//Rectangle
//constructor
Rectangle::Rectangle() {

	set( 0, 0, 0, 0 );
}

Rectangle::Rectangle( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y ) {

	set( min_x, min_y, max_x, max_y );
}

//destructor
//private

//public

void Rectangle::set( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y ) {

	p_ul = new Point( min_x, min_y );
	p_ur = new Point( max_x, min_y );
	p_ll = new Point( min_x, max_y );
	p_lr = new Point( max_x, max_y );

	this->min_x = min_x;
	this->min_y = min_y;
	this->max_x = max_x;
	this->max_y = max_y;

	this->width  = max_x - min_x;
	this->height = max_y - min_y;

	p_center = new Point( min_x + (width/2), min_y + (height/2) );

}

bool Rectangle::check_intersection( Point *point ) {

	if( p_ul < point && p_lr > point ) {
		return true;
	}
	return false;

}

bool Rectangle::check_intersection( Rectangle *rectangle ) {

    if( ( max_x > rectangle->min_x && min_x < rectangle->max_x ) &&
        ( max_y > rectangle->min_y && min_y < rectangle->max_y ) ) {
		return true;
	}
	return false;

}

uint64_t Rectangle::get_hilbert() {
	return p_center->get_hilbert();
}

bool Rectangle::operator>( Rectangle &rectangle ) {
	if( get_hilbert() > rectangle.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Rectangle::operator<( Rectangle &rectangle ) {
	if( get_hilbert() < rectangle.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Rectangle::operator==( Rectangle &rectangle ) {
	if( get_hilbert() == rectangle.get_hilbert() ) {
		return true;
	}
	return false;
}

void Rectangle::operator=( Rectangle &rectangle ) {

}

