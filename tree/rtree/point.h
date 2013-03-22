/*
 * =====================================================================================
 *
 *       Filename:  point.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/21/2013 07:19:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

	const int order = 7;
	const uint64_t hilbert_table[] = {
	0, 1, 3, 2,
	2, 1, 3, 0,
	2, 3, 1, 0,
	0, 3, 1, 2,
	};

	const uint64_t xy_table[] = {
	0, 1, 3, 2,
	3, 1, 0, 2,
	3, 2, 0, 1,
	0, 2, 3, 1,
	};

class Point {
private:

//constants

//variables
	uint64_t x;
	uint64_t y;
	uint64_t hilbert;
	bool hilbert_current;
	
//methods
	void point_to_hilbert( uint64_t x, uint64_t y, uint64_t &hilbert );
	void hilbert_to_point( uint64_t hilbert, uint64_t &x, uint64_t &y );

public:

//constructor
	Point();
	Point( uint64_t x, uint64_t y );
	Point( uint64_t hilbert );

//inspectors
	uint64_t get_x();
	uint64_t get_y();
	uint64_t get_hilbert();

//mutators
	void set_x( uint64_t x );
	void set_y( uint64_t y );
	void set_xy( uint64_t x, uint64_t y );
	void set_hilbert( uint64_t h );

//sugar
	bool operator>( Point &p );
	bool operator<( Point &p );
	bool operator==( Point &p );
	void operator=( Point &p );

};

