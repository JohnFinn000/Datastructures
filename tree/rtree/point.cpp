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

char *int_to_binary( uint64_t num, int precision ) {
    
    char *arr = (char*) malloc( sizeof(char) * (precision + 1) );
    arr[precision] = '\0';

    for( uint64_t i = precision; i > 0; --i ) {
        arr[precision-i] = (num & (1 << (i-1))) ? '1' : '0';
    }
    
    return arr;

}


//destructor
//private
void Point::point_to_hilbert( uint64_t x, uint64_t y, uint64_t &hilbert ) {
	/*
		   current_state
		   /  x coord
		  /   / y coord
		 /\  / /
code	0 0 0 0
	*/
	uint64_t code;
	uint64_t hilbert_value = 0;
	uint64_t curve_length  = 0;
	uint64_t current_state = 0;


	for( int step = order; step >= 0; --step ) {

		code  = current_state << 2;
		code |= ( x & ( 1 << step ) ) ? 2 : 0;
		code |= ( y & ( 1 << step ) ) ? 1 : 0;

		curve_length  = hilbert_table[0][code];
        current_state = hilbert_table[1][code];

		hilbert_value <<= 2;
		hilbert_value |= curve_length;

	}

	hilbert = hilbert_value;

}

void Point::hilbert_to_point( uint64_t hilbert, uint64_t &x, uint64_t &y ) {
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
    uint64_t hil = 0;
	uint64_t num = 0;
    x = 0;
    y = 0;

	for( int step = order; step >= 0; --step ) {

        new_state = 0;
        code = 0;
        hil = 0;

		hil |= ( hilbert & ( 2 << (step * 2) ) ) ? 2 : 0;
		hil |= ( hilbert & ( 1 << (step * 2) ) ) ? 1 : 0;

		code |= ( old_state << 2 );
		code |= hil;

        new_state = state_table[code];

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

