/*
 * =====================================================================================
 *
 *       Filename:  rtree.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/19/2013 05:42:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio>
#include "../../linkedlist/list.h"
#include "../../dynamic_array/dynamic_array.hh"
#include "shape.h"


/*
class Leaf : public Node {
private:

//constants
	const int max_children = 3;
	const int min_children = 0;

//variables
	bool is_leaf;
	int num_children;
	Node *parent;
	Shape *shape[3];
	Rectangle *bounds;

public:

};
*/

class RTree {
private:

    class Node {
    private:

    //constants
        const int max_children = 3;
        const int min_children = 0;

    //variables
        bool is_leaf;
        int num_children;
        Node *parent;
        Node *children[3];
        Rectangle *bounds;

        Shape *shape[3];

    public:

    //constructors
        Node()

    //inspectors
        Node *get_closest_child( uint64_t hilbert );
        void insert( Shape *shape ); // not implemented
        void add( Node *node ); // not implemented

        bool is_leaf();
        bool is_full();
        bool is_empty();
        uint64_t get_hilbert();
        
    //mutators
        void fit_bounds(); // not implemented
        
    };

//variables
	Node *root;

//methods
	Node *overflow( Node *node, Shape *shape );
	void underflow();
	void adjust_tree( Node *parent, Dynamic_array<Node> cousin_nodes ); // not implemented
	RTree *choose_leaf( Shape *shape );

public:

//constructors
	RTree(); 

//inspectors
	List *search( Rectangle *query_window );

//mutators
	void insert( Shape *shape );
	void delete_node();

};

