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

RTree *t;

int main() {

    t = new RTree();

    Shape shape_list[200];
    for( int i = 0; i < 200; ++i ) {
        shape_list[i].add_point(5*i,i*10);
        shape_list[i].add_point(5*(i+1),(i+1)*10);
        shape_list[i].add_point(5*(i+1),(i+1)*10);
        t->insert( (shape_list+i) );
    }


    t->print_tree();

}
