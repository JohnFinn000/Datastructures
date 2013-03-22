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

//Point
//constructor
Point::Point() {

	set_xy( 0, 0 );
}

Point::Point( int x, int y ) {

	set_xy( x, y );
}

Point::Point( int hilbert ) {

	set_hilbert( hilbert );
}

//destructor
//private
void Point::point_to_hilbert( int x, int y, int &hilbert ) {
	/*
		   current_state
		   /  x coord
		  /   / y coord
		 /\  / /
code	0 0 0 0
	*/
	unsigned int code;
	unsigned int hilbert_value;
	unsigned int current_state = 0;

	for( int step = 0; step <= order; ++step ) {

		code  = current_state << 2;
		code |= ( x & ( 1 << (order - step) ) ) ? 2 : 0;
		code |= ( y & ( 1 << (order - step) ) ) ? 1 : 0;

		current_state = hilbert_table[code];

		hilbert_value <<= 2;
		hilbert_value |= current_state;
	}

	hilbert = hilbert_value;

}

void Point::hilbert_to_point( int hilbert, int &x, int &y ) {
	/*
		   old_state
		   /  new_state
		  /   / 
		 /\  /\
code	0 0 0 0
	*/
	unsigned int code = 0;
	unsigned int old_state = 0;
	unsigned int new_state = 0;
	unsigned int num = 0;

	for( int step = 0; step <= order; ++step ) {

		new_state = hilbert & ( 3 << ((order - step) * 2) );
		new_state >>= (step-1) * 2;

		code = old_state;
		code <<= 2;
		code |= new_state;

		num = xy_table[code];

		x <<= 1;
		x |= (num & 2) ? 1 : 0;
		y <<= 1;
		y |= (num & 1) ? 1 : 0;

		old_state = new_state;
	}

}

//public
int Point::x() {

	return this.x;
}

int Point::y() {

	return this.y;
}

int Point::get_hilbert() {
	if( this.hilbert_current == false ) {
		point_to_hilbert( this.x, this.y, this.hilbert );
		this.hilbert_current = true;
	}
	return this.hilbert;
}


void Point::set_x( int x ) {

	set_xy( x, this,y );
}

void Point::set_y( int y ) {

	set_xy( this.x, y );
}

void Point::set_xy( int x, int y ) {

	this.x = x;
	this.y = y;
	this.hilbert_current = false;
}

void Point::set_hilbert( int h ) {

	this.hilbert = h;
	this.hilbert_current = true;
	hilbert_to_point( this.hilbert, this.x, this.y );
}


bool Point::operator>( Point &p ) {

	if( get_hilbert() > p.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Point::operator<( Point &p ) {

	if( get_hilbert() < p.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Point::operator==( Point &p ) {

	if( get_hilbert() == p.get_hilbert() ) {
		return true;
	}
	return false;
}

void Point::operator=( Point &p ) {

	set_xy( p->x, p->y );
}



//Shape
//constructor
Shape::Shape() {
	num_points = 0;
	list_points = NULL;
	bounds_current = false;
}

//destructor
//private
void Shape::fit_bounds() {
	int min_x;
	int min_y;
	int max_x;
	int max_y;
	Point iter;

	min_x = max_x = iter->x();
	min_y = max_y = iter->y();

	for( int i = 0; i < num_points; ++i ) {
		iter->x() > max_x ? max_x = iter->x() : 
		iter->x() < min_x ? min_x = iter->x() : 0;

		iter->y() > max_y ? max_y = iter->y() : 
		iter->y() < min_y ? min_y = iter->y() : 0;
	}

	bounds_current = true;
}

//public
Rectangle *Shape::get_bounds() {

	if( !bounds_current ) {
	 	fit_bounds();
	}

	return bounds;

}

void Shape::add_point() {

}

bool Shape::check_intersection( Point *point ) {
	bounds->check_intersection( point );

}

bool Shape::check_intersection( Rectangle *rectangle ) {
	bounds->check_intersection( rectangle );

}

bool Shape::check_intersection( Shape *shape ) {
	bounds->check_intersection( shape );

}

void Shape::rotate() {

}

void Shape::move() {

}

int Shape::get_hilbert() {
	return p_center.get_hilbert();
}

bool Shape::operator>( Shape &shape ) {
	if( this.p_center.get_hilbert() > rectangle.p_center.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Shape::operator<( Shape &shape ) {
	if( this.p_center.get_hilbert() < rectangle.p_center.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Shape::operator==( Shape &shape ) {
	if( this.p_center.get_hilbert() == rectangle.p_center.get_hilbert() ) {
		return true;
	}
	return false;
}

void Shape::operator=( Shape &shape ) {

}

//Rectangle
//constructor
Rectangle::Rectangle() {

	set( 0, 0, 0, 0 );
}

Rectangle::Rectangle( int min_x, int min_y, int max_x, int max_y ) {

	set( min_x, min_y, max_x, max_y );
}

//destructor
//private

//public

void Rectangle::set( int min_x, int min_y, int max_x, int max_y ) {

	p_ul = new Point( min_x, min_y );
	p_ur = new Point( max_x, min_y );
	p_ll = new Point( min_x, max_y );
	p_lr = new Point( max_x, max_y );

	this.min_x = min_x;
	this.min_y = min_y;
	this.max_x = max_x;
	this.max_y = max_y;

	this.width  = max_x - min_x;
	this.height = max_y - min_y;

	p_center = new Point( min_x + (width/2), min_y + (height/2) );

}

bool Rectangle::check_intersection( Point *point ) {

	if( p_ul < point && p_lr > point ) {
		return true;
	}
	return false;

}

bool Rectangle::check_intersection( Rectangle *rectangle ) {

	if( ( this.x_max > rectangle->x_min || rectangle->x_max > this.x_min ) &&
            ( this.y_max > rectangle->y_min || rectangle->y_max > this.y_min ) ) {
		return true;
	}
	return false;

}

int Rectangle::get_hilbert() {
	return p_center.get_hilbert();
}

bool Rectangle::operator>( Rectangle &rectangle ) {
	if( this.p_center.get_hilbert() > rectangle.p_center.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Rectangle::operator<( Rectangle &rectangle ) {
	if( this.p_center.get_hilbert() < rectangle.p_center.get_hilbert() ) {
		return true;
	}
	return false;
}

bool Rectangle::operator==( Rectangle &rectangle ) {
	if( this.p_center.get_hilbert() == rectangle.p_center.get_hilbert() ) {
		return true;
	}
	return false;
}

void Rectangle::operator=( Rectangle &rectangle ) {

}

//Node
//constructor

Node::Node() {
	is_leaf = false;
	num_children = 0;
	parent = NULL;
	for( int i = 0; i < max_children; ++i ) {
		node[i] = NULL;
	}
	bounds = NULL;
	shape  = NULL;

}

//destructor
//private
//public
Node *Node::get_child( unsigned int hilbert ) {

	int i;
	for( i = 0; i < num_children; ++i ) {
		if( hilbert < node[i]->get_hilbert() ) {
			return node[i];
		}
	}
	return NULL;
}

void Node::insert( Shape *shape ) {
	if( !is_full() ) {
		this.shape[num_children] = shape;
		++num_children;
	}

	// recalculate bounds


}

bool Node::is_leaf() {
	return is_leaf;
}

bool Node::is_full() {
	if( children == max_children ) {
		return true;
	}
	return false;
}

bool Node::is_empty() {
	if( children == min_children ) {
		return true;
	}
	return false;
}

unsigned int Node::get_hilbert() {
	return bounds->get_hilbert();	
}


//RTree
//constructor
RTree:RTree() {
	children = 0;
	parent   = NULL;
	node[0]  = NULL;
	node[1]  = NULL;
	node[2]  = NULL;
	bounds   = NULL;
	shape    = NULL;

}

//destructor
//private
// there are too many sub nodes in the current node
void RTree::overflow( Node *node, Shape *shape ) {

    Dynamic_array<Node> cousin_nodes;
	
	for( int i = 0; i < node->num_children; ++i ) {

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

void RTree::adjust_tree() {


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
		overflow( node, shape );
	}
}

void RTree::delete_node() {
    
    


}
































