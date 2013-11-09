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

/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree
 *      Method:  RTree
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
RTree::RTree () {
    tree_root = new Root();
}  /* -----  end of method RTree::RTree  (constructor)  ----- */

RTree::~RTree () {
    delete( tree_root );
}  /* -----  end of method RTree::RTree  (destructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree
 *      Method:  RTree :: search
 * Description:  
 *--------------------------------------------------------------------------------------
 */
List<Shape*> *RTree::search( Rectangle *query_window ) {
    return tree_root->search( query_window );   
}

List<Shape*> *RTree::search( Point *query_point ) {
    return tree_root->search( query_point );   
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree
 *      Method:  RTree :: print_tree
 * Description:  recursively prints the tree from root
 *--------------------------------------------------------------------------------------
 */
void RTree::print_tree() {

    tree_root->print();
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree
 *      Method:  RTree :: insert
 * Description:  wraps the specified shape in a leaf node and inserts the leaf
 *                  into the tree.
 *--------------------------------------------------------------------------------------
 */
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


/* TODO implement remove
 *--------------------------------------------------------------------------------------
 *       Class:  RTree
 *      Method:  RTree :: remove
 * Description:  removes the specified shape
 *--------------------------------------------------------------------------------------
 */
void RTree::remove() {

}

/* TODO implement clear
 *--------------------------------------------------------------------------------------
 *       Class:  RTree
 *      Method:  RTree :: clear
 * Description:  clears the RTree of all shapes
 *--------------------------------------------------------------------------------------
 */
void RTree::clear() {

}






