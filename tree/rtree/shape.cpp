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


Point **Shape::get_points( int &size ) {

    
}

void Shape::add_point( uint64_t x, uint64_t y ) {

    Point *new_point = new Point( x, y );
    list_points.add( new_point );
}

void Shape::add_point( Point *p ) {
    list_points.add( p );
}

void Shape::stretch( uint64_t &min_x, uint64_t &min_y, uint64_t &max_x, uint64_t &max_y ) {

    int size = list_points.get_size();
    if( size > 0 ) {
        uint64_t p_x = list_points[0]->get_x();
        uint64_t p_y = list_points[0]->get_y();
        min_x = max_x = p_x;
        min_y = max_y = p_y;
        for( int i = 0; i < size; ++i ) {
            p_x = list_points[i]->get_x();
            p_y = list_points[i]->get_y();
            p_x < min_x ? min_x = p_x : 
            p_x > max_x ? max_x = p_x : 0;
            p_y < min_y ? min_y = p_y : 
            p_y > max_y ? max_y = p_y : 0;
        }
    }
}


intersection_type Shape::check_intersection( Point *point ) {

    Dynamic_array<Point*>::iterator *iter = list_points.begin();
    uint64_t p_x = point->get_x();
    uint64_t p_y = point->get_y();

    uint64_t a_x;
    uint64_t a_y;

    uint64_t b_x;
    uint64_t b_y;

    int intersection_count = 0;

    a_x = iter->get()->get_x();
    a_y = iter->get()->get_y();
    for( ; !iter->end(); iter->next() ) {
        
        a_x = b_x;
        a_y = b_y;
        b_x = iter->get()->get_x();
        b_y = iter->get()->get_y();


        if( p_y > a_y && p_y < b_y ) {
            // if b_x and a_x are positive or
            // they are kitty corner to each other
            //  and pass through the positive x axis
            if( a_x > p_x ) {
                if( b_x > p_x ) {
                    ++intersection_count;
                } else {
                    
                    // increase intersection count if the slope is correct
                }
            } else {
                if( b_x > p_x ) {
                    
                    // increase intersection count if the slope is correct
                }
            }
        }
            
    }

    if( intersection_count & 1 ) { // if it's odd it's inside
        return partial_intersection_e;
    } else { // if it's even it's outside
        return no_intersection_e;
    }
}

intersection_type Shape::check_intersection( Rectangle *rectangle ) {
    return no_intersection_e;
}

intersection_type Shape::check_intersection( Shape *shape ) {
    
    // Shape intersections are a little more complicated than this
    // TODO better shape intersection testing
    Dynamic_array<Point*>::iterator *iter = list_points.begin();
    for( ; !iter->end(); iter->next() ) {
        if( shape->check_intersection( iter->get() ) == partial_intersection_e ) {
            return partial_intersection_e;
        }
    }
    return no_intersection_e;
}

void Shape::rotate( uint64_t x, uint64_t y ) {

}

void Shape::move( uint64_t x, uint64_t y ) {
	Dynamic_array<Point*>::iterator *iter = list_points.begin();

	for( ; !iter->end(); iter->next() ) {
        iter->get()->set_x( iter->get()->get_x() + x );
        iter->get()->set_y( iter->get()->get_y() + y );
    }
}

void Shape::operator=( Shape &shape ) {

}



/*
 *--------------------------------------------------------------------------------------
 *       Class:  Bounding_box
 *      Method:  Bounding_box
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Bounding_box::Bounding_box() {

	set( 0, 0, 0, 0 );
}  /* -----  end of method Bounding_box::Bounding_box  (constructor)  ----- */


Bounding_box::Bounding_box( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y ) {

	set( min_x, min_y, max_x, max_y );
}  /* -----  end of method Bounding_box::Bounding_box  (constructor)  ----- */


intersection_type Bounding_box::check_intersection( Point *point ) {

    uint64_t p_x = point->get_x();
    uint64_t p_y = point->get_y();

    // something to note is a bounding box can possibly be completely intersected by a point
    // however this is rare enough it doesn't merit extra calculations to check so points will
    // never completely intersect a bounding box
    if( ( min_x > p_x || max_x < p_x ) ||
        ( min_y > p_y || max_y < p_y ) ) {

        return no_intersection_e;
    } else {
        return partial_intersection_e;
    }
}

intersection_type Bounding_box::check_intersection( Bounding_box *rectangle ) {

    if( ((min_x > rectangle->max_x) || (max_x < rectangle->min_x)) ||
        ((min_y > rectangle->max_y) || (max_y < rectangle->min_y)) ) {
        return no_intersection_e;
    } else if( ( max_x <= rectangle->max_x && min_x >= rectangle->min_x ) &&
               ( max_y <= rectangle->max_y && min_y >= rectangle->min_y ) ) {
		return complete_intersection_e; // if the rectangle completely surrounds this box it is a complete intersection
    } else {
        return partial_intersection_e;
    }
}

intersection_type Bounding_box::check_intersection( Shape *shape ) {

    return no_intersection_e;
}

uint64_t Bounding_box::get_hilbert() {
	return p_center->get_hilbert();
}

void Bounding_box::set( uint64_t min_x, uint64_t min_y, uint64_t max_x, uint64_t max_y ) {

    p_ul = new Point( min_x, min_y );
    p_ur = new Point( max_x, min_y );
    p_ll = new Point( min_x, max_y );
    p_lr = new Point( max_x, max_y );

    this->min_x = min_x;
    this->min_y = min_y;
    this->max_x = max_x;
    this->max_y = max_y;

    this->width = max_x - min_x;
    this->height = max_y - min_y;

    p_center = new Point( min_x + (width/2), min_y + (height/2) );
}

void Bounding_box::get( uint64_t &min_x, uint64_t &min_y, uint64_t &max_x, uint64_t &max_y ) {

	min_x = this->min_x;
	min_y = this->min_y;
	max_x = this->max_x;
	max_y = this->max_y;
}

void Bounding_box::stretch( uint64_t &min_x, uint64_t &min_y, uint64_t &max_x, uint64_t &max_y ) {

	this->min_x < min_x ? min_x = this->min_x : 0;
	this->min_y < min_y ? min_y = this->min_y : 0;
	this->max_x > max_x ? max_x = this->max_x : 0;
	this->max_y > max_y ? max_y = this->max_y : 0;
}

bool Bounding_box::operator>( Bounding_box &rectangle ) {

	if( get_hilbert() > rectangle.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Bounding_box::operator>( Bounding_box *rectangle ) {

	if( get_hilbert() > rectangle->get_hilbert() ) {
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

bool Bounding_box::operator<( Bounding_box *rectangle ) {

	if( get_hilbert() < rectangle->get_hilbert() ) {
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

bool Bounding_box::operator==( Bounding_box *rectangle ) {

	if( get_hilbert() == rectangle->get_hilbert() ) {
		return true;
	}
	return false;
}

