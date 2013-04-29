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
#include <inttypes.h>
#include "../../lazy_eval/lazy_eval.h"
#include "hilbert_tables.h"

const int maximum_order = 16; // should always be a multiple of 8

struct coords_pair {
    uint64_t x;
    uint64_t y;
};

/*
 * =====================================================================================
 *        Class:  Point
 *  Description:  
 * =====================================================================================
 */
class Point {
public:

    /* ====================  LIFECYCLE     ======================================= */
    Point();                             /* constructor */
	Point( uint64_t x, uint64_t y );     /* constructor */
	Point( uint64_t hilbert );           /* constructor */


    /* ====================  ACCESSORS     ======================================= */
	uint64_t get_x();
	uint64_t get_y();
	uint64_t get_hilbert();

    /* ====================  MUTATORS      ======================================= */
	void set_x( uint64_t x );
	void set_y( uint64_t y );
	void set_xy( uint64_t x, uint64_t y );
	void set_hilbert( uint64_t h );

    /* ====================  OPERATORS     ======================================= */
	bool operator>(  Point &p );
	bool operator<(  Point &p );
	bool operator==( Point &p );
	void operator=(  Point &p );

    bool operator==( Point param );
    bool operator!=( Point param );
    bool operator>(  Point param );
    bool operator>=( Point param );
    bool operator<(  Point param );
    bool operator<=( Point param );

    Point operator=(  Point param );
    Point operator+=( Point param );
    Point operator-=( Point param );
    Point operator*=( Point param );
    Point operator/=( Point param );
    Point operator%=( Point param );

    uint64_t operator=(  uint64_t param ); // set to hilbert value
    uint64_t operator+=( uint64_t param );
    uint64_t operator-=( uint64_t param );
    uint64_t operator*=( uint64_t param );
    uint64_t operator/=( uint64_t param );
    uint64_t operator%=( uint64_t param );

    Point operator+( Point param );
    Point operator-( Point param );
    Point operator*( Point param );
    Point operator/( Point param );
    Point operator%( Point param );

    Point operator++( );     //prefix
    Point operator++( int ); //suffix
    Point operator--( );     //prefix
    Point operator--( int ); //suffix

    bool operator!();

    
	static void point_to_hilbert( uint64_t x, uint64_t y, uint64_t &hilbert );
	static void hilbert_to_point( uint64_t hilbert, uint64_t &x, uint64_t &y );

private:

    /* ====================  DATA MEMBERS  ======================================= */

    //forward declarations
    template <class T>
    class Lazy_hilbert;

    template <class T>
    class Lazy_coord : public Lazy<coords_pair> {
        Point::Lazy_hilbert<uint64_t> *hilbert;
        protected: void evaluate() {
            Point::hilbert_to_point( hilbert->get(), this->value.x, this->value.y );
        }
        public: void init( Lazy_hilbert<uint64_t> *h ) {
            hilbert = h;
        }
    };

    template <class T>
    class Lazy_hilbert : public Lazy<uint64_t> {
        Point::Lazy_coord<coords_pair> *coords;
        private: void evaluate() {
            coords_pair xy_coords = coords->get();
            Point::point_to_hilbert( xy_coords.x, xy_coords.y, this->value );
        }
        public: void init( Lazy_coord<coords_pair> *c ) {
            coords = c;
        }
    };

    //variables
    Lazy_coord<coords_pair> coordinates;
    Lazy_hilbert<uint64_t>  hilbert;

    //methods
    void initialize();

}; /* -----  end of class Point  ----- */

