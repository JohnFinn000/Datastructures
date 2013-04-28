/*
 * =====================================================================================
 *
 *       Filename:  rtree.cpp
 *
 *    Description:  This contains the implementation for methods in the RTree class
 *                      for the implementation of any rtree nodes look in rtree_node.cpp
 *
 *        Version:  1.0
 *        Created:  01/19/2013 06:01:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "rtree.h"

//RTree
//constructor
RTree::RTree() {
    tree_root = new Root();
}

//public

List<Shape*> *RTree::search( Rectangle *query_window ) {
    return tree_root->search( query_window );   
}

void RTree::print_tree() {

    tree_root->print();
}

// puts a shape in the rtree
void RTree::insert( Shape *shape ) {
    
    try {
        tree_root->insert( new Leaf( shape ) );
    } catch( char *e ) {
        printf("%s\n", e );
    }
}

void RTree::insert( Shape *arr[], int size ) {
    
    // sort the Shapes to insert
    //insertion_sort( arr, size );
}

void RTree::insert( Dynamic_array<Shape*> arr ) {
    
    // sort the dynamic array
}

void RTree::insert( List<Shape*> list ) {
    
    // sort the list
}

void RTree::remove() {
    
    


}




