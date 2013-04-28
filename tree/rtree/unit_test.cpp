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
#include "rtree.h"
//#include "utils.cpp"

//RTree *t;

void verify_rtree() {

    RTree *t;
    t = new RTree();

    char p;
    Shape shape_list[200];
    for( int i = 0; i < 20; ++i ) {
        shape_list[i].add_point(5*i,i*10);
        shape_list[i].add_point(5*(i+1),(i+1)*10);
        shape_list[i].add_point(5*(i+1),(i+1)*10);
        t->insert( (shape_list+i) );
        scanf("%c\n",&p );
        
        t->print_tree();
    }

    t->print_tree();

}
/*
int verify_point() {

    Point a;
    a.set_xy( 0, 0 );
    printf("%lu\n", a.get_hilbert() );

    return 1;

}
*/

int main() {

    verify_rtree();

   //Point::generate_hilbert_to_point_table();
   /*
    uint64_t x;
    uint64_t y;
    for( uint64_t h = 0; h < 100; ++h ) {
        hilbert_to_point_base( h, x, y );
        printf("%lu %lu\n", x, y );
    }
*/
    
/*
    Point a;
    for( uint64_t h = 0; h < 100; ++h ) {
        a.set_hilbert( h );
        printf("%lu %lu\n", a.get_x(), a.get_y() );
    }
*/

}





