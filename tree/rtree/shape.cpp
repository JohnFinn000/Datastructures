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

}


uint64_t Shape::get_hilbert() {

}

Point **Shape::get_points( int &size ) {


}

void Shape::add_point( uint64_t x, uint64_t y ) {
    Point *new_point = new Point( x, y );

    list_points.add( new_point );
    ++num_points;
}

void Shape::add_point( Point *p ) {

    list_points.add( p );
    ++num_points;
}

bool Shape::check_intersection( Point *point ) {

}

bool Shape::check_intersection( Rectangle *rectangle ) {

}

bool Shape::check_intersection( Shape *shape ) {

}

void Shape::rotate( uint64_t x, uint64_t y ) {

}

void Shape::move( uint64_t x, uint64_t y ) {
	Dynamic_array<Point*>::iterator *iter = list_points.begin();

	for( ; !iter->end(); iter->next() ) {
        iter->get()->set_x( iter->get()->get_x() + x );
        iter->get()->set_y( iter->get()->get_y() + y );
    }

    // instead it would be possible to just move each of the bounds points
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

//Shape
//constructor
Shape::Shape() {
	num_points = 0;
    bounds = new Rectangle( 0,0,0,0 );
	bounds_current = false;

    bounds.init( list_points );
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
Bounding_box *Shape::get_bounds() {

	return bounds.get();

}

uint64_t Shape::get_hilbert() {
	return bounds.get().get_hilbert();
}

void Shape::add_point( uint64_t x, uint64_t y ) {
    Point *new_point = new Point( x, y );

    list_points.add( new_point );
    ++num_points;

    bounds.invalidate();
}

void Shape::add_point( Point *p ) {

    list_points.add( p );
    ++num_points;

    bounds.invalidate();
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

    bounds.invalidate();
    // instead it would be possible to just move each of the bounds points
}


//Rectangle
//constructor
Bounding_box::Bounding_box() {

	set( 0, 0, 0, 0 );
}

Bounding_box::Bounding_box( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y ) {

	set( min_x, min_y, max_x, max_y );
}

//destructor
//private

//public

void Bounding_box::set( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y ) {

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
/*
bool Bounding_box::check_intersection( Point *point ) {

	if( p_ul < point && p_lr > point ) {
		return true;
	}
	return false;

}

bool Bounding_box::check_intersection( Bounding_box *rectangle ) {

    if( ( max_x > rectangle->min_x && min_x < rectangle->max_x ) &&
        ( max_y > rectangle->min_y && min_y < rectangle->max_y ) ) {
		return true;
	}
	return false;

}

uint64_t Bounding_box::get_hilbert() {
	return p_center->get_hilbert();
}

bool Bounding_box::operator>( Bounding_box &rectangle ) {
	if( get_hilbert() > rectangle.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Bounding_box::operator<( Bounding_box &rectangle ) {
	if( get_hilbert() < rectangle.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Bounding_box::operator==( Bounding_box &rectangle ) {
	if( get_hilbert() == rectangle.get_hilbert() ) {
		return true;
	}
	return false;
}

void Bounding_box::operator=( Bounding_box &rectangle ) {

}
*/
