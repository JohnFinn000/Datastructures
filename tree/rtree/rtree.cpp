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
    type = node_trunk_t;
	num_children = 0;
	parent = NULL;

	for( int i = 0; i < max_children; ++i ) {
		children[i] = NULL;
	}

	bounds = new Rectangle( 0,0,0,0 );
    bounds_current = false;

}

//destructor
//private
//public
RTree::Node *RTree::Node::get_closest_child( uint64_t hilbert ) {

	for( int i = 0; i < num_children; ++i ) {
		if( hilbert < children[i]->get_hilbert() ) {
            return children[i];
		}
	}
    return NULL;
}

void RTree::Node::insert( Shape *shape ) {

    Leaf *new_child = new Leaf( shape );
    insert( new_child );

}

void RTree::Node::insert( Node *node ) {

    if( type == node_root_t ) {
        if( num_children == 0 ) {
            children[0] = node;
            num_children = 1;
            node->parent = this;
            return;
        } else {
            Node *new_branch = new Node();
            if( num_children > 0 ) {
                new_branch->insert( children[0] );
            }
            children[0] = new_branch;
            num_children = 1;
            new_branch->parent = this;
            new_branch->children[0]->insert( node );
            return;
        }
    }

    if( num_children == max_children ) {
        if( parent->type == node_root_t ) {
            parent->insert( node ); // TODO: FIX this
        } else {
            parent->overflow( node );
        }
        return;
    }

    // insert the new shape in the proper place according to it's hilbert value
    int k;
    for( k = 0; k < num_children; ++k ) { // find the proper place
        if( node->bounds > children[k]->bounds ) {
            break;
        }
    }
    for( int i = num_children+1; i > k; --i ) { // shift the children to make room
        children[i] = children[i-1];
    }
    children[k] = node;
    node->parent = this;
    bounds_current = false;

    ++num_children;
}

RTree::Node **RTree::Node::adopt_children( int &size ) {
    size = num_children;
    Node **children_list = new Node *[size];

    for( int i = 0; i < size; ++i ) {
        children_list[i] = children[i];
        children[i] = NULL;
    }
    num_children = 0;
    bounds_current = false;
    return children_list;
}

void RTree::Node::overflow( Node *new_node ) {

    Dynamic_array<RTree::Node*> cousin_nodes;

    // gather up a list of all the grandchildren
    int children_list_size;
    for( int i = 0; i < num_children; ++i ) {
        Node **adopted_children = children[i]->adopt_children( children_list_size );
        cousin_nodes.add( adopted_children, children_list_size ); 
    };

    // add in the shape causing the overflow
    cousin_nodes.add( new_node );

    // check if there is enough room available to just shift the leaves around
    if( num_children * max_children < cousin_nodes.get_size() ) { // make more room
        Node *new_child = new Node();
        new_child->type = children[0]->type;

        // add the leaves all into the children and the new node
        int size = cousin_nodes.get_size();
        int leaves_per = !size % (num_children+1) ? size / (num_children + 1) : (size / (num_children + 1))+1;
        int i = 0;
        int k = 0;
        for( ; k < (num_children * leaves_per); ) { // add most of the leaves into the children
            children[i]->insert( cousin_nodes[k] );
            ++k;
            if( k % leaves_per == 0 ) {
                ++i;
            }
        }
        for( ; k < size; ++k ) { // add the rest into the new node
            new_child->insert( cousin_nodes[k] );
        }

        // if this node is full this insert will just propogate the overflow
        insert( new_child );

        return;

    }

    // no split was needed so just redistribute the leaves
    // add the leaves all into the children
    int size = cousin_nodes.get_size();
    int leaves_per = size / num_children;
    int i = 0;
    for( int k = 0; k < size; ) {
        children[i]->insert( cousin_nodes[k] );
        ++k;
        if( k % leaves_per == 0 ) {
            ++i;
        }
    }
    bounds_current = false;
	
}

List<RTree::Node*> *RTree::Node::search( Rectangle *query_window ) {

    List<RTree::Node*> *results = new List<RTree::Node*>;

	switch( num_children ) {
	case 3:
		results->splice( children[2]->search( query_window ) ); 
	case 2:
		results->splice( children[1]->search( query_window ) );
	case 1:
		results->splice( children[0]->search( query_window ) );
		break;
	case 0:
        if( bounds->check_intersection( query_window ) ) {
		    results->add_front( this );
        }
		break;
	};

    return results;
}

void RTree::Node::print() {

    get_bounds();
    if( type == node_root_t ) {
        printf("bounds( %lu, %lu, %lu, %lu ) {\n", bounds->min_x, bounds->min_y, bounds->max_x, bounds->max_y );
    } else if( type == node_trunk_t ) {
        printf("    bounds trunk( %lu, %lu, %lu, %lu ) {\n", bounds->min_x, bounds->min_y, bounds->max_x, bounds->max_y );
    } else if( type == node_branch_t ) {
        printf("        bounds branch( %lu, %lu, %lu, %lu ) {\n", bounds->min_x, bounds->min_y, bounds->max_x, bounds->max_y );
    }

    for( int i = 0; i < num_children; ++i ) {
		children[i]->print(); 
    }

    printf("}\n");

}

RTree::node_type RTree::Node::check_type() {
	return type;
}

bool RTree::Node::is_full() {
    return num_children == max_children ? true : false;
}

bool RTree::Node::is_empty() {
    return num_children == min_children ? true : false;
}

uint64_t RTree::Node::get_hilbert() {
    get_bounds();
    return bounds->get_hilbert();	
}

Rectangle *RTree::Node::get_bounds() {

    if( !bounds_current ) {
        fit_bounds();
    }

    return bounds;
}

void RTree::Node::fit_bounds() {
    uint64_t min_x; // only actually needs to check new points
    uint64_t min_y;
    uint64_t max_x;
    uint64_t max_y;

    Rectangle *bounds_iter = children[0]->get_bounds();

    max_x = bounds_iter->max_x;
    min_x = bounds_iter->min_x;
    max_y = bounds_iter->max_y;
    min_y = bounds_iter->min_y;

    for( int i = 1; i < num_children; ++i ) { 
        bounds_iter = children[i]->get_bounds();
        bounds_iter->max_x > max_x ? max_x = bounds_iter->max_x : 
        bounds_iter->min_x < min_x ? min_x = bounds_iter->min_x : 0;

        bounds_iter->max_y > max_y ? max_y = bounds_iter->max_y : 
        bounds_iter->min_y < min_y ? min_y = bounds_iter->min_y : 0;
    }   
    if( !bounds ) {
        bounds = new Rectangle( min_x, min_y, max_x, max_y );
    } else {
        bounds->set( min_x, min_y, max_x, max_y );
    }

    bounds_current = true;

}

// LEAF

RTree::Leaf::Leaf() {

    // initialize all of the variables
    type = node_leaf_t;

}

RTree::Leaf::Leaf( Shape *shape ) {

    // initialize all of the variables
    type = node_leaf_t;

    insert( shape );

}

RTree::Node *RTree::Leaf::get_closest_child( uint64_t hilbert ) {
    return this;
}


void RTree::Leaf::insert( Shape *shape ) {
    bounds_current = false;
    this->shape = shape;
    
}

List<RTree::Node*> *RTree::Leaf::search( Rectangle *query_window ) {

    List<RTree::Node*> *results = new List<RTree::Node*>;

    if( shape->check_intersection( query_window ) ) {
        results->add_front( this );
    }

    return results;
}

void RTree::Leaf::print() {

    get_bounds();
    printf("            bounds leaf( %lu, %lu, %lu, %lu );\n", bounds->min_x, bounds->min_y, bounds->max_x, bounds->max_y );

}

RTree::node_type RTree::Leaf::check_type() {
	return node_leaf_t;
}

bool RTree::Leaf::is_full() {
	if( shape ) {
		return true;
	} else {
	    return false;
    }
}

bool RTree::Leaf::is_empty() {
	if( !shape ) {
		return true;
	} else {
	    return false;
    }
}

void RTree::Leaf::fit_bounds() {

    bounds = shape->get_bounds();

}

//RTree
//constructor
RTree::RTree() {
    tree_root = new Node();
    tree_root->type = node_root_t;
    Node *branch = new Node();
    branch->type = node_branch_t;
    tree_root->insert( branch );

}

//destructor
//private
void RTree::adjust_tree( Node *parent, Dynamic_array<RTree::Node*> cousin_nodes ) {
    if( parent->parent == NULL ) {
        // parent is root
    } else {
        

    }


}

// picks the best leaf for the shape being inserted
RTree::Node *RTree::choose_leaf( Shape *shape ) {

	Node *current_node = tree_root->children[0];
	unsigned int shape_hilbert = shape->get_hilbert();

	for(;;) {
		if( current_node->check_type() == node_branch_t ) {
			return current_node;
		} else {
			current_node = current_node->get_closest_child( shape_hilbert );
		}
	}

    // never reached
    return NULL;

}

//public

List<RTree::Node*> *RTree::search( Rectangle *query_window ) {
    return tree_root->search( query_window );   
}

void RTree::print_tree() {

    tree_root->print();

}

// puts a shape in the rtree
void RTree::insert( Shape *shape ) {

	Node *node = choose_leaf( shape );

    node->insert( shape );

}

void RTree::delete_node() {
    
    


}




