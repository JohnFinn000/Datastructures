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
#include <shape.h>

//Shape
//constructor
Shape::Shape() {
	num_points = 0;
	list_points = NULL;
	bounds_current = false;
}

//destructor
//private
void Shape::fit_bounds() {
	int min_x;
	int min_y;
	int max_x;
	int max_y;
	Point iter;

	min_x = max_x = iter->x();
	min_y = max_y = iter->y();

	for( int i = 0; i < num_points; ++i ) {
		iter->x() > max_x ? max_x = iter->x() : 
		iter->x() < min_x ? min_x = iter->x() : 0;

		iter->y() > max_y ? max_y = iter->y() : 
		iter->y() < min_y ? min_y = iter->y() : 0;
	}

	bounds_current = true;
}

//public
Rectangle *Shape::get_bounds() {

	if( !bounds_current ) {
	 	fit_bounds();
	}

	return bounds;

}

void Shape::add_point() {

}

bool Shape::check_intersection( Point *point ) {
	bounds->check_intersection( point );

}

bool Shape::check_intersection( Rectangle *rectangle ) {
	bounds->check_intersection( rectangle );

}

bool Shape::check_intersection( Shape *shape ) {
	bounds->check_intersection( shape );

}

void Shape::rotate() {

}

void Shape::move() {

}

int Shape::get_hilbert() {
	return p_center.get_hilbert();
}

bool Shape::operator>( Shape &shape ) {
	if( this.p_center.get_hilbert() > rectangle.p_center.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Shape::operator<( Shape &shape ) {
	if( this.p_center.get_hilbert() < rectangle.p_center.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Shape::operator==( Shape &shape ) {
	if( this.p_center.get_hilbert() == rectangle.p_center.get_hilbert() ) {
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

Rectangle::Rectangle( int min_x, int min_y, int max_x, int max_y ) {

	set( min_x, min_y, max_x, max_y );
}

//destructor
//private

//public

void Rectangle::set( int min_x, int min_y, int max_x, int max_y ) {

	p_ul = new Point( min_x, min_y );
	p_ur = new Point( max_x, min_y );
	p_ll = new Point( min_x, max_y );
	p_lr = new Point( max_x, max_y );

	this.min_x = min_x;
	this.min_y = min_y;
	this.max_x = max_x;
	this.max_y = max_y;

	this.width  = max_x - min_x;
	this.height = max_y - min_y;

	p_center = new Point( min_x + (width/2), min_y + (height/2) );

}

bool Rectangle::check_intersection( Point *point ) {

	if( p_ul < point && p_lr > point ) {
		return true;
	}
	return false;

}

bool Rectangle::check_intersection( Rectangle *rectangle ) {

	if( ( this.x_max > rectangle->x_min || rectangle->x_max > this.x_min ) &&
            ( this.y_max > rectangle->y_min || rectangle->y_max > this.y_min ) ) {
		return true;
	}
	return false;

}

int Rectangle::get_hilbert() {
	return p_center.get_hilbert();
}

bool Rectangle::operator>( Rectangle &rectangle ) {
	if( this.p_center.get_hilbert() > rectangle.p_center.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Rectangle::operator<( Rectangle &rectangle ) {
	if( this.p_center.get_hilbert() < rectangle.p_center.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Rectangle::operator==( Rectangle &rectangle ) {
	if( this.p_center.get_hilbert() == rectangle.p_center.get_hilbert() ) {
		return true;
	}
	return false;
}

void Rectangle::operator=( Rectangle &rectangle ) {

}

