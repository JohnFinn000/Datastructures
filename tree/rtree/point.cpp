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

    initialize();

	set_xy( 0, 0 );
}

Point::Point( uint64_t x, uint64_t y ) {

    initialize();

	set_xy( x, y );
}

Point::Point( uint64_t hilbert ) {

    initialize();

	set_hilbert( hilbert );
}

void Point::initialize() {

    this->coordinates.init( &(this->hilbert) );
    this->coordinates.add_dependant( &(this->hilbert) );
    this->hilbert.init( &(this->coordinates) );
    this->hilbert.add_dependant( &(this->coordinates) );
}

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


	for( int step = maximum_order; step >= 0; --step ) {

		code  = current_state << 2;
		code |= ( x & ( 1 << step ) ) ? 2 : 0;
		code |= ( y & ( 1 << step ) ) ? 1 : 0;

		curve_length  = hilbert_table[code];
        current_state = hilbert_state_table[code];

		hilbert_value <<= 2;
		hilbert_value |= curve_length;

	}

	hilbert = hilbert_value;

}

// uses more extended tables to decode hilbert values more quickly
void Point::hilbert_to_point( uint64_t hilbert, uint64_t &x, uint64_t &y ) {
/*
		      old_state
             /               partial hilbert value
        ____/                /
        |   |_______________/
	    |   |               |
code    |0 0|0 0 0 0 0 0 0 0|
        |___|_______________|

*/
	uint64_t code = 0;
    x = 0;
    y = 0;

    int step = (maximum_order * 2) - 8;

	for( ; step >= 0; step -= 8 ) {

		code  &= 0X300;
        code |= (( hilbert >> step ) & 0xFF );

		code = xy_table_256[code];

		x <<= 4;
		x |= (( code >> 4 ) & 0XF );

		y <<= 4;
		y |= ( code & 0XF );
        
	}
/*
    uint64_t num = 0;
    uint64_t state = 0;
	for( ; step >= 0; step -= 8 ) {

        code = (( hilbert >> step ) & 0xFF );

		num = xy_table_256[code] ^ state;
        
        // 0 0X00       
        // 1 0X0F       
        // 2 0XF0       
        // 3 0XFF       
		

		x <<= 4;
		x |= (( code >> 4 ) & 0XF );

		y <<= 4;
		y |= ( code & 0XF );
        
	}
*/
}

//public
uint64_t Point::get_x() {

	return coordinates.get().x;
}

uint64_t Point::get_y() {

	return coordinates.get().y;
}

uint64_t Point::get_hilbert() {

	return hilbert.get();
}


void Point::set_x( uint64_t x ) {

    set_xy( x, get_y() ); // there may be faster ways of doing this
}

void Point::set_y( uint64_t y ) {

    set_xy( get_x(), y ); // there may be faster ways of doing this
}

void Point::set_xy( uint64_t x, uint64_t y ) {

    coords_pair temp;
    temp.x = x;
    temp.y = y;
    
    coordinates.set( temp );
}

void Point::set_hilbert( uint64_t h ) {

	this->hilbert.set( h );
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

	set_xy( p.get_x(), p.get_y() );
}

