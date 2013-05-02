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
#include "shape.h"
#include "../../linkedlist/list.h"
#include "../../dynamic_array/dynamic_array.hh"

/*
 * =====================================================================================
 *        Class:  RTree
 *  Description:  This is a hilbert curve RTree implementation
 *                  briefly what this does is it takes shapes and organizes them into
 *                  groups that allow searches to be executed much more quickly
 *                  than searching every single shape.
 * =====================================================================================
 */

class RTree {
public:

    /* ====================  LIFECYCLE     ======================================= */
    RTree();                             /* constructor */
    ~RTree();                            /* destructor */

    /* ====================  ACCESSORS     ======================================= */
	List<Shape*> *search( Rectangle *query_window );
	List<Shape*> *search( Point     *query_point );

    //Scope allows a search starting from somewhere lower in the tree than root
    //Scope *retreive_scope( Rectangle *query_window );

    void print_tree();

    /* ====================  MUTATORS      ======================================= */
	void insert( Shape *shape );
	void insert( Shape *arr[], int size );
	void insert( Dynamic_array<Shape*> arr );
	void insert( List<Shape*> list );

	void remove();
	void clear();
protected:
public:
    /* ====================  DATA MEMBERS  ======================================= */

    enum node_type {
        node_root_t,
        node_trunk_t,
        node_branch_t,
        node_leaf_t
    };

    // forward declarations
    class Trunk;
    class Leaf;
    class Node;
    class Branch;
    class Root;

    friend class Node;
    friend class Trunk;
    friend class Root;
    friend class Branch;
    friend class Leaf;

    /*
     * =====================================================================================
     *        Class:  Node
     *  Description:  Nodes are anything that exists in the RTree
     * =====================================================================================
     */
    class Node {
    protected:
    public:

        //variables
        node_type type;
        Trunk *parent;

        template <class T>
        class Lazy_bounds : public Lazy<Bounding_box*> {
            RTree::Node *owner;
            private: void evaluate();
            public:  void init( RTree::Node *owner );
            ~Lazy_bounds();
        }; /* -----  end of class Lazy_bounds  ----- */

        Lazy_bounds<Bounding_box*> bounds;

        template <class T>
        friend class Lazy_bounds;

        //methods
        virtual void fit_bounds( Bounding_box &bounds ) = 0;
        virtual void consolidate();

    public:
        //constructors
        Node();
        Node( Trunk *parent );
        ~Node();

        //inspectors
	    virtual List<Shape*> *search( Rectangle *query_window ) = 0;
	    virtual List<Shape*> *search( Point     *query_point  ) = 0;

        virtual void print( int indent = 0 );

        node_type check_type();
        virtual uint64_t get_hilbert();
        Bounding_box *get_bounds();

        static bool less_than(    Node *a, Node *b );
        static bool greater_than( Node *a, Node *b );
        
        //mutators
        virtual Node **adopt_children( int &size ) = 0;
        void adopt( Trunk *parent );

        virtual void insert( Leaf  *leaf )     = 0;
        virtual void insert( Trunk *new_node ) = 0;
        virtual void insert( Node  *new_node ) = 0;

        friend class RTree;
        
    }; /* -----  end of class Node  ----- */


    template <class T>
    friend class Node::Lazy_bounds;

    /*
     * =====================================================================================
     *        Class:  Trunk
     *  Description:  Trunk is anything that has children. Which is just all nodes
     *                  excluding leaf nodes.
     * =====================================================================================
     */
    class Trunk : public Node {
    protected:
    public:
        //constants
        static const int max_children = 3;
        static const int min_children = 2; // min_children should be 1 for branch

        //variables
        int  num_children;
        Node *children[max_children];

        //methods
        void fit_bounds( Bounding_box &bounds );
	    virtual void overflow( Node *node );
        virtual void consolidate();

    public:
        //constructors
        Trunk();
        Trunk( Trunk *parent );
        ~Trunk();

        //inspectors
        virtual uint64_t get_hilbert();
        void print( int indent = 0 );

	    virtual List<Shape*> *search( Rectangle *query_window );
	    virtual List<Shape*> *search( Point     *query_point );

        virtual bool is_full();
        virtual bool is_empty();

        //mutators
        Node **adopt_children( int &size );

        virtual void insert( Leaf  *leaf );
        virtual void insert( Trunk *new_node );
        virtual void insert( Node  *new_node );

        friend class RTree;
    }; /* -----  end of class Trunk  ----- */



    /*
     * =====================================================================================
     *        Class:  Root
     *  Description:  Root is a node with no parent's it operates nearly identically to 
     *                  Trunk nodes except it splits itself instead of attempting to
     *                  overflow into non-existant sibling nodes
     * =====================================================================================
     */
    class Root : public Trunk {
    public:
        //constructors
        Root();
        ~Root();

        //mutators
        void insert( Leaf  *leaf );
        void insert( Trunk *node );
        void print( int indent = 0 );

        friend class RTree;
    }; /* -----  end of class Root  ----- */



    /*
     * =====================================================================================
     *        Class:  Branch
     *  Description:  Branches are nearly identical to Trunk except instead of passing
     *                  Leaf insertions onto their children they will insert them into
     *                  their children list.
     *                It is invalid to insert a Trunk node into a Branch node because
     *                  a Branch's children can only be leaves.
     * =====================================================================================
     */
    class Branch : public Trunk {
    protected:
    public:
        //methods
        void overflow( Node *node );
        void consolidate();

    public:
        //constructors
        Branch();
        ~Branch();

        //mutators
        void insert( Leaf  *leaf );
        void insert( Trunk *node );
        void print( int indent = 0 );

        friend class RTree;
    }; /* -----  end of class Branch  ----- */


    
    /*
     * =====================================================================================
     *        Class:  Leaf
     *  Description:  Leaves hold the bounds for their shape and a pointer to the shape
     *                  Many of the methods it inherits from Node are invalid to call
     *                  this is something that should most likely be fixed but since only
     *                  RTree can directly interact with Nodes rearranging the inheritance
     *                  heiarchy won't be visible outside of RTree and I can put it off
     *                  for a little while.
     * =====================================================================================
     */
    class Leaf : public Node {
    protected:
    public:
        //variables
        Shape *shape;

        //methods
        void fit_bounds( Bounding_box &bounds );
    public:
        //constructors
        Leaf();
        Leaf( Shape *shape );
        ~Leaf();

        //inspectors
	    List<Shape*> *search( Rectangle *query_window );
	    List<Shape*> *search( Point     *query_point );

        bool is_full();
        bool is_empty();
        void print( int indent = 0 );
        
        //mutators
        void set( Shape *shape );
        
        Node **adopt_children( int &size );

        //illegal methods
        void insert( Leaf  *leaf );     // this is illegal
        void insert( Trunk *new_node ); // this is illegal
        void insert( Node  *new_node ); // this is illegal

        friend class RTree;
    }; /* -----  end of class Leaf  ----- */

    //variables
	Root *tree_root;

}; /* -----  end of class RTree  ----- */

#endif
