/*
 * =====================================================================================
 *
 *       Filename:  rtree.cpp
 *
 *    Description:  
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

//Node
//constructor
RTree::Node::Node() {

    // initialize all of the variables
	is_leaf = false;
	num_children = 0;
	parent = NULL;

	for( int i = 0; i < max_children; ++i ) {
		node[i] = NULL;
	}

	bounds = NULL;

	for( int i = 0; i < max_children; ++i ) {
		shape[i] = NULL;
	}

}

//destructor
//private
//public
Node *RTree::Node::get_closest_child( uint64_t hilbert ) {

/*
    int k = 0;
    uint64_t diff;
    uint64_t new_diff;

    if( num_children >= 1 ) {
        diff = hilbert - children[i]->get_hilbert();
        diff < 0 ? diff *= -1 : 0; // diff should always be positive
    } else {
        return NULL;
    }
    
	for( int i = 1; i < num_children; ++i ) {
        new_diff = hilbert - children[i]->get_hilbert();
        new_diff < 0 ? new_diff *= -1 : 0; // new_diff should always be positive

		if( diff > new_diff ) {
            diff = new_diff;
            k = i;
		}
	}
	return node+k;
*/

	for( int i = 0; i < num_children; ++i ) {
		if( hilbert < children[i]->get_hilbert() ) {
            return children[i];
		}
	}
    return NULL;
}

void RTree::Node::insert( Shape *shape ) {

}

bool RTree::Node::is_leaf() {
	return is_leaf;
}

bool RTree::Node::is_full() {
	if( children == max_children ) {
		return true;
	} else {
	    return false;
    }
}

bool RTree::Node::is_empty() {
	if( children == min_children ) {
		return true;
	} else {
	    return false;
    }
}

unsigned int RTree::Node::get_hilbert() {
    if( bounds ) {
	    return bounds->get_hilbert();	
    } else {
        return 0;
    }
}

void RTree::Node::fit_bounds() {


}

//RTree
//constructor
RTree:RTree() {
    root = NULL;

}

//destructor
//private
// there are too many sub nodes in the current node
void RTree::overflow( Node *node, Shape *shape ) {

    Dynamic_array<Node> cousin_nodes;
	
	for( int i = 0; i < node->num_children; ++i ) {
        cousin_nodes.add( node->children[i] );
	}

	int num_nodes = 1;
	for( int i = 0; i < node->num_children; ++i ) {
		num_nodes += node->node[i]->num_children;
	}

	// if everythings already full then split
	if( node->num_children * node->max_children > num_nodes ) {
		// create a new node
	} else {
		

	}

	if( num_nodes );

}

// there are too few subnodes in the current node
void RTree::underflow( ) {

}

void RTree::adjust_tree( Node *parent, Dynamic_array<Node> cousin_nodes ) {
    if( parent->parent == NULL ) {
        // parent is root
    } else {
        

    }


}

// picks the best leaf for the shape being inserted
Node *RTree::choose_leaf( Shape *shape ) {

	Node *current_node = root;
	unsigned int shape_hilbert = shape->get_hilbert();

	for(;;) {
		if( current_node->is_leaf() ) {
			return current_node;
		} else {
			current_node = current_node->get_closest_child( shape_hilbert );
		}
	}

    // never reached
    return NULL;

}

//public
List *RTree::search( Rectangle *query_window ) {

	Node *current_node = root;
    List<Shape> *results = new List<Shape>();

	switch( current_node->num_children ) {
	case 3:
		results->splice( node[2]->search( query_window ) ); 
	case 2:
		results->splice( node[1]->search( query_window ) );
	case 1:
		results->splice( node[0]->search( query_window ) );
		break;
	case 0:
		results->add( shape->check_intersection( query_window ) );
		break;
	};

    return results;
}

// puts a shape in the rtree
void RTree::insert( Shape *shape ) {

	Node *node = choose_leaf( shape );

	if( !node->is_full() ) {
		node->insert( shape );

	} else {
        Dynamic_array<Node> cousin_nodes;

        Node *ancestor = node->parent;
        for( int i = 0; i < ancestor->num_children; ++i ) {
            cousin_nodes.add( ancestor->children[i] );
        }

		cousin_nodes.add( overflow( node, shape ) );

        adjust_tree( ancestor, cousin_nodes );
        
	}
}

void RTree::delete_node() {
    
    


}




