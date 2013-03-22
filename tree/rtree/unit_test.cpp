/*
 * =====================================================================================
 *
 *       Filename:  unit_test.cpp
 *
 *    Description:  unit test for rtree
 *
 *        Version:  1.0
 *        Created:  03/21/2013 07:22:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "point.h"

int main() {

    Point pointa;
    for( int i = 0; i <= 10; ++i ) {
        printf("pointa) x: %d, y: %d, hilbert: %d\n", pointa.get_x(), pointa.get_y(), pointa.get_hilbert() );
        pointa.set_x( i );

    }

    Point pointb( 5, 6 );
    printf("\npointb) x: %d, y: %d, hilbert: %d\n", pointb.get_x(), pointb.get_y(), pointb.get_hilbert() );

    Point pointc( 0 );
    for( int i = 0; i <= 10; ++i ) {
    printf("pointc) x: %d, y: %d, hilbert: %d\n", pointc.get_x(), pointc.get_y(), pointc.get_hilbert() );
        pointc.set_hilbert( pointc.get_hilbert() + 1 );

    }
    pointc.set_hilbert( 12 );
    printf("pointc) x: %d, y: %d, hilbert: %d\n", pointc.get_x(), pointc.get_y(), pointc.get_hilbert() );
    pointc.set_hilbert( 13 );
    printf("pointc) x: %d, y: %d, hilbert: %d\n", pointc.get_x(), pointc.get_y(), pointc.get_hilbert() );



}
