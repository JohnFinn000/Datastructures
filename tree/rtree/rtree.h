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
#ifndef _RTREE_H__
#define _RTREE_H__

#include <stdio.h>
#include "../../linkedlist/list.h"
#include "shape.h"
#include "../../dynamic_array/dynamic_array.hh"


class RTree {
protected:

    enum node_type {
        node_root_t,
        node_trunk_t,
        node_branch_t,
        node_leaf_t
    };

    class Node {
    public:

    //constants
        static const int max_children = 3;
        static const int min_children = 0;

    //variables
        node_type type;
        int  num_children;
        Node *parent;
        Node *children[max_children];
        Rectangle *bounds;
        bool bounds_current;

	    void overflow( Node *node );

    public:

    //constructors
        Node();

    //inspectors
        virtual Node *get_closest_child( uint64_t hilbert );
        virtual void insert( Shape *shape );
        void insert( Node *node ); // not implemented
        Node **adopt_children( int &size );
	    virtual List<Node*> *search( Rectangle *query_window );
        virtual void print();

        virtual node_type check_type();
        virtual bool is_full();
        virtual bool is_empty();
        uint64_t get_hilbert();

        static bool compare( Node *a, Node *b );
        
    //mutators
        Rectangle *get_bounds();
        virtual void fit_bounds();

        friend class RTree;
        
    };

    class Leaf : public Node {
    public:

    //variables
        Shape *shape;

    public:

    //constructors
        Leaf();
        Leaf( Shape *shape );

    //inspectors
        Node *get_closest_child( uint64_t hilbert );
        void insert( Shape *shape );
        //void add( Node *node ); // not implemented
	    List<Node*> *search( Rectangle *query_window );
        void print();

        node_type check_type();
        bool is_full();
        bool is_empty();
        uint64_t get_hilbert();
        
    //mutators
        void fit_bounds();

        friend class RTree;
        
    };

    friend class Node;
    friend class Leaf;

//variables
	Node *tree_root;

//methods
	void adjust_tree( Node *parent, Dynamic_array<RTree::Node*> cousin_nodes ); // not implemented
	Node *choose_leaf( Shape *shape );

public:

//constructors
	RTree(); 

//inspectors
	List<Node*> *search( Rectangle *query_window );
    void print_tree();

//mutators
	void insert( Shape *shape );
	void delete_node();

};

extern RTree *t;

#endif
