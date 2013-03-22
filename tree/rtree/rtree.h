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

enum shape_names {
	dot_e,
	line_e,
	triangle_e,
	rectangle_e,
};

class Shape {
private:

//variables
	Rectangle *bounds;
	bool bounds_current;

	int num_points;
	Point *list_point;

//methods
	void fit_bounds();
	
public:

//constructor
	Shape();

//inspectors
	Rectangle *get_bounds();
	int get_hilbert();

	void add_point();

	bool check_intersection( Point *point );
	bool check_intersection( Shape *shape );
	bool check_intersection( Rectangle *rectangle );

//methods
	void rotate();
	void move();

//sugar
	bool operator>( Shape &shape );
	bool operator<( Shape &shape );
	bool operator==( Shape &shape );
	void operator=( Shape &shape );
};


class Rectangle {
private:

//variables
	Point p_ul;
	Point p_ur;
	Point p_ll;
	Point p_lr;
	Point p_center;

	int min_x, max_x;
	int min_y, max_y;
	int width;
	int height;

public:

//constructors
	Rectangle();
	Rectangle( int min_x, int min_y, int max_x, int max_y );

//inspectors
	bool check_intersection( Point *point );
	bool check_intersection( Shape *shape );
	bool check_intersection( Rectangle *rectangle );

	int get_hilbert();

//mutators
	void set( int min_x, int min_y, int max_x, int max_y );

//sugar
	bool operator>( Rectangle &rectangle );
	bool operator<( Rectangle &rectangle );
	bool operator==( Rectangle &rectangle );
	void operator=( Rectangle &rectangle ); // not implemented
};


class Node {
private:

//constants
	const int max_children = 3;
	const int min_children = 0;

//variables
	bool is_leaf;
	int num_children;
	Node *parent;
	Node *node[3];
	Rectangle *bounds;

	Shape *shape[3];
public:

//constructors
	Node()

//inspectors
	Node *get_closest_child( unsigned int hilbert );
	void insert( Shape *shape );

	bool is_leaf();
	bool is_full();
	bool is_empty();
	unsigned int get_hilbert();
	
//mutators
	void fit_bounds();
	
};

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

//variables
	Node *root;

//methods
	void overflow( Node *node, Shape *shape );
	void underflow();
	void adjust_tree(); // not implemented
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

