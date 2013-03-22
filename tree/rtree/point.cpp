/*
 * =====================================================================================
 *
 *       Filename:  point.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/21/2013 07:21:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "point.h"

//Point
//constructor
Point::Point() {

	set_xy( 0, 0 );
}

Point::Point( uint64_t x, uint64_t y ) {

	set_xy( x, y );
}

Point::Point( uint64_t hilbert ) {

	set_hilbert( hilbert );
}

//destructor
//private
void Point::point_to_hilbert( uint64_t x, uint64_t y, uint64_t &hilbert ) {
    printf("calculating hilbert value\n");
	/*
		   current_state
		   /  x coord
		  /   / y coord
		 /\  / /
code	0 0 0 0
	*/
	uint64_t code;
	uint64_t hilbert_value;
	uint64_t current_state = 0;

	for( int step = 0; step <= order; ++step ) {

		code  = current_state << 2;
		code |= ( x & ( 1 << (order - step) ) ) ? 2 : 0;
		code |= ( y & ( 1 << (order - step) ) ) ? 1 : 0;

		current_state = hilbert_table[code];

		hilbert_value <<= 2;
		hilbert_value |= current_state;
	}

	hilbert = hilbert_value;

}

void Point::hilbert_to_point( uint64_t hilbert, uint64_t &x, uint64_t &y ) {
    printf("calculating points\n");
	/*
		   old_state
		   /  new_state
		  /   / 
		 /\  /\
code	0 0 0 0
	*/
	uint64_t code = 0;
	uint64_t old_state = 0;
	uint64_t new_state = 0;
	uint64_t num = 0;

	for( int step = 0; step <= order; ++step ) {

		new_state = hilbert & ( 3 << ((order - step) * 2) );
		new_state >>= (step-1) * 2;

		code = old_state;
		code <<= 2;
		code |= new_state;

		num = xy_table[code];

		x <<= 1;
		x |= (num & 2) ? 1 : 0;
		y <<= 1;
		y |= (num & 1) ? 1 : 0;

		old_state = new_state;
	}

}

//public
uint64_t Point::get_x() {

	return this->x;
}

uint64_t Point::get_y() {

	return this->y;
}

uint64_t Point::get_hilbert() {
	if( this->hilbert_current == false ) {
		point_to_hilbert( this->x, this->y, this->hilbert );
		this->hilbert_current = true;
	}
	return this->hilbert;
}


void Point::set_x( uint64_t x ) {

	set_xy( x, this->y );
}

void Point::set_y( uint64_t y ) {

	set_xy( this->x, y );
}

void Point::set_xy( uint64_t x, uint64_t y ) {

	this->x = x;
	this->y = y;
	this->hilbert_current = false;
}

void Point::set_hilbert( uint64_t h ) {

	this->hilbert = h;
	this->hilbert_current = true;
	hilbert_to_point( this->hilbert, this->x, this->y );
}


bool Point::operator>( Point &p ) {

	if( get_hilbert() > p.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Point::operator<( Point &p ) {

	if( get_hilbert() < p.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Point::operator==( Point &p ) {

	if( get_hilbert() == p.get_hilbert() ) {
		return true;
	}
	return false;
}

void Point::operator=( Point &p ) {

	set_xy( p.x, p.y );
}

