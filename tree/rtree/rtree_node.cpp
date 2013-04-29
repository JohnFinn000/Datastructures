/*
 * =====================================================================================
 *
 *       Filename:  rtree_node.cpp
 *
 *    Description:  rtree node implementations
 *
 *        Version:  1.0
 *        Created:  04/18/2013 07:14:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "rtree.h"

//Lazy_bounds
// Lazy bounds only calculates the bounds when they are actually needed 
// it then saves the calculated bounds and will only recalculate if it or any of
// the variables it depends on are invalidated
template <>
void RTree::Node::Lazy_bounds<Bounding_box*>::evaluate() {
    value = new Bounding_box( 0, 0, 0, 0 );
    owner->fit_bounds( (*value) );
}

template <>
void RTree::Node::Lazy_bounds<Bounding_box*>::init( RTree::Node *o ) {
    owner = o;
}

//Node
// Nodes are anything in the tree
// Trunk, Branch, Root, and Leaf all inherit from Node
// not all of the methods in Node should be used in it's children though
// it would be good to look into a better inheritance heiarchy to remedy this
// however any changes should make the heirchy simpler I don't want to add another type
// of node it's already complicated enough as is.

/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree::Node
 *      Method:  Node
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
RTree::Node::Node() {

	parent = NULL;
    this->bounds.init( this );
}  /* -----  end of method RTree::Node::Node  (constructor)  ----- */

RTree::Node::Node( RTree::Trunk *parent ) {

	this->parent = parent;
    this->bounds.init( this );
    parent->bounds.add_dependant( &(this->bounds) );
}  /* -----  end of method RTree::Node::Node  (constructor)  ----- */

void RTree::Node::print( int indent ) {

    Bounding_box *b = bounds.get();
    uint64_t min_x, min_y, max_x, max_y;

    b->get( min_x, min_y, max_x, max_y );
    printf("%*sbounds( %lu, %lu, %lu, %lu, %lu )\n", indent, "", min_x, min_y, max_x, max_y, get_hilbert() );
}

RTree::node_type RTree::Node::check_type() {
	return type;
}

uint64_t RTree::Node::get_hilbert() {
    return bounds.get()->get_hilbert();	
}

Bounding_box *RTree::Node::get_bounds() {

    return bounds.get();
}

bool RTree::Node::less_than( Node* a, Node *b ) {

    return a->get_hilbert() < b->get_hilbert();
}

bool RTree::Node::greater_than( Node* a, Node *b ) {

    return a->get_hilbert() > b->get_hilbert();
}

void RTree::Node::adopt( RTree::Trunk *parent ) {
    this->parent = parent;
    parent->bounds.add_dependant( &(this->bounds) );

}

void RTree::Node::consolidate( ) {
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree::Trunk
 *      Method:  Trunk
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */

RTree::Trunk::Trunk() {

    // initialize all of the variables
    type = node_trunk_t;
    num_children = 0;
    parent = NULL;

    for( int i = 0; i < max_children; ++i ) { 
        children[i] = NULL;
    }   

}  /* -----  end of method RTree::Trunk::Trunk  (constructor)  ----- */

RTree::Trunk::Trunk( RTree::Trunk *parent ) {

    // initialize all of the variables
    type = node_trunk_t;
    num_children = 0;
    this->parent = parent;
    parent->bounds.add_dependant( &(this->bounds) );

    for( int i = 0; i < max_children; ++i ) { 
        children[i] = NULL;
    }   

}  /* -----  end of method RTree::Trunk::Trunk  (constructor)  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree::Trunk
 *      Method:  RTree::Trunk :: fit_bounds
 * Description:  This is called by lazy_bounds when the bounds need to be evaluated
 *                  it finds the minimum y, maximum y, minimum x, and maximum x
 *                  of it's children and those are set to be the bounds of this node
 *
 *        Note:  This should never be called except by lazy_bounds
 *
 *--------------------------------------------------------------------------------------
 */
void RTree::Trunk::fit_bounds( Bounding_box &bounds ) {
    uint64_t min_x; // only actually needs to check new points
    uint64_t min_y;
    uint64_t max_x;
    uint64_t max_y;

    if( num_children > 0 ) {
        Bounding_box *bounds_iter = children[0]->get_bounds();

        bounds_iter->get( min_x, min_y, max_x, max_y );

        for( int i = 1; i < num_children; ++i ) { 
            bounds_iter = children[i]->get_bounds();
            bounds_iter->stretch( min_x, min_y, max_x, max_y );
        }

        bounds.set( min_x, min_y, max_x, max_y );
    }
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree::Trunk
 *      Method:  RTree::Trunk :: overflow
 * Description:  
 *     when a node has too many children it calls it call's it's parent's overflow function
 *     the parent then redistributes it's grand children amoungst it's children and if there are
 *     too many grandchildren it spawns a new child and inserts it into itself
 *     if the parent has too many children it will then propogate the overflow
 *
 *--------------------------------------------------------------------------------------
 */
void RTree::Trunk::overflow( Node *new_node ) {
    Dynamic_array<RTree::Node*> cousin_nodes;

    // gather up a list of all the grandchildren
    int children_list_size;
    for( int i = 0; i < num_children; ++i ) {
        Node **adopted_children = children[i]->adopt_children( children_list_size );
        cousin_nodes.add( adopted_children, children_list_size ); 
    };

    // add in the shape causing the overflow
    cousin_nodes.add( new_node );

    // sort them according to their hilbert values
    cousin_nodes.sort( less_than );

    int size = cousin_nodes.get_size();

    // check if there is enough room available to just shift the leaves around
    if( num_children * max_children < size ) { // if there is not then make more room
        Node *new_child;
        switch( children[0]->check_type() ) {
        case node_leaf_t:
            new_child = new Branch();
            break;
        case node_branch_t:
            new_child = new Branch();
            break;
        case node_trunk_t:
            new_child = new Trunk();
            break;
        default:
            return;
        }

        // add the leaves all into the children and the new node
        int leaves_per;
        if( size % (num_children+1) == 0 ) {            // if the nodes can now be split in evenly ex) 9 amoungst 3
            leaves_per = (size / (num_children + 1));   // then do so
        } else {                                        // otherwise we need to add 1 to account for the remainder
            leaves_per = (size / (num_children+1)) + 1; // ex) 8 amoungst 3 results in 3 leaves per for the first 2
        }                                               //     and 2 for the newly added child

        //leaves_per = (size + (num_children)) / (num_children+1); // TODO this might be a better alternative

        int i = 0;
        int k = 0;
        for( ; k < (num_children * leaves_per); ) {     // add most of the leaves into the children
            children[i]->insert( cousin_nodes[k] );
            ++k;
            if( k % leaves_per == 0 ) {
                ++i;
            }
        }

        for( ; k < size; ++k ) {                        // add the remainder into the new node
            new_child->insert( cousin_nodes[k] );
        }

        // if the current node is full this insert will propogate the overflow
        // TODO there is a problem with propogating the overflow
        this->insert( new_child );

    } else {

        // no split was needed so just redistribute the leaves
        // add the leaves all into the children
        //int leaves_per = size / num_children;
        int leaves_per = (size + (num_children-1)) / (num_children); // this might be a better alternative
        int i = 0;
        for( int k = 0; k < size; ) {
            children[i]->insert( cousin_nodes[k] );
            ++k;
            if( k % leaves_per == 0 ) {
                ++i;
            }
        }

        bounds.invalidate();

        for( int i = 0; i < num_children; ++i ) {
            children[i]->consolidate();
        }
	}
}		/* -----  end of method RTree::Trunk::overflow  ----- */


void RTree::Trunk::consolidate( ) {
    for( int i = 0; i < num_children; ++i ) {
        children[i]->consolidate();
    }

    Dynamic_array<RTree::Node*> cousin_nodes;

    // gather up a list of all the grandchildren
    int children_list_size;
    for( int i = 0; i < num_children; ++i ) {
        Node **adopted_children = children[i]->adopt_children( children_list_size );
        cousin_nodes.add( adopted_children, children_list_size ); 
    };

    int size = cousin_nodes.get_size();

    // set the number of children to the actual number we need
    num_children = (size + (max_children-1)) / max_children;

    // place the grand children into the children
    
    //int leaves_per = size / num_children;
    int leaves_per = (size + (num_children-1)) / (num_children); // this might be a better alternative
    int i = 0;
    for( int k = 0; k < size; ) {
        children[i]->insert( cousin_nodes[k] );
        ++k;
        if( k % leaves_per == 0 ) {
            ++i;
        }
    }
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree::Trunk
 *      Method:  RTree::Trunk :: get_hilbert
 * Description:  This returns the largest hilbert value from amoungst it's children
 *                  if there are no children 0 is returned.
 *
 *--------------------------------------------------------------------------------------
 */
uint64_t RTree::Trunk::get_hilbert() {
    
    return num_children > 0 ? children[0]->get_hilbert() : 0;
}

void RTree::Trunk::print( int indent ) {

    Bounding_box *b = bounds.get();
    uint64_t min_x, min_y, max_x, max_y;
    b->get( min_x, min_y, max_x, max_y );

    printf("%*sbounds( %lu, %lu, %lu, %lu, %lu, %d ) {\n", indent, "", min_x, min_y, max_x, max_y, get_hilbert(), num_children );

    for( int i = 0; i < num_children; ++i ) {
		children[i]->print( indent + 3 ); 
    }

    printf("%*s}\n", indent, "" );
}

RTree::Node **RTree::Trunk::adopt_children( int &size ) {

    size = num_children;
    Node **children_list = new Node *[size];

    for( int i = 0; i < size; ++i ) {
        children_list[i] = children[i];
        children[i] = NULL;
    }
    num_children = 0;
    bounds.invalidate();

    return children_list;
}

// Rectangle and Point require the same search code but are not inherited 
// This could possibly be solved with iheritance of a number of other ways
// TODO find a better solution for this
// TODO when query is null no further intersection checks need to be done
#define SEARCH_IMPLEMENTATION( query )                                 \
    switch( this->bounds.get()->check_intersection( query ) ) {        \
    case complete_intersection_e:                                      \
        query = NULL;                                                  \
    case partial_intersection_e:                                       \
    {                                                                  \
        List<Shape*> *results = new List<Shape*>;                      \
        for( int i = 0; i < num_children; ++i ) {                      \
            results->splice( *children[i]->search( query ) );          \
        };                                                             \
        return results;                                                \
    }                                                                  \
    case no_intersection_e:                                            \
        return NULL;                                                   \
    }                                                                  \
    return NULL;

// if query window is NULL then retreive all of the leaves
List<Shape*> *RTree::Trunk::search( Rectangle *query_window ) {
    SEARCH_IMPLEMENTATION( query_window );
}

// if query point is NULL then retreive all of the leaves
List<Shape*> *RTree::Trunk::search( Point *query_point ) {
    SEARCH_IMPLEMENTATION( query_point );
}

#undef SEARCH_IMPLEMENTATION

bool RTree::Trunk::is_full() {
    return num_children == max_children ? true : false;
}

bool RTree::Trunk::is_empty() {
    return num_children == min_children ? true : false;
}

void RTree::Trunk::insert( Leaf *leaf ) {

    int i;
    for( i = 1; i < num_children; ++i ) {
        if( greater_than( leaf, children[i] ) ) {
            break;
        }
    }
    children[i-1]->insert( leaf );
}

void RTree::Trunk::insert( Trunk *new_node ) {

    if( num_children >= max_children ) {
        parent->overflow( new_node );
    } else {
        // insert the new shape in the proper place according to it's hilbert value
        int k;
        uint64_t node_hilbert = new_node->get_hilbert();
        for( k = 0; k < num_children; ++k ) { // find the proper place
            if( node_hilbert > children[k]->get_hilbert() ) {
                break;
            }
        }
        for( int i = num_children+1; i > k; --i ) { // shift the children to make room
            children[i] = children[i-1];
        }
        children[k] = new_node;
        new_node->adopt( this );

        this->bounds.invalidate();

        ++num_children;
    }
}

// TODO consider switching this to double dispatch
void RTree::Trunk::insert( Node *new_node ) {
    switch( new_node->check_type() ) {
    case node_leaf_t:
        this->insert( (Leaf*) new_node );
        break;
    default:
        this->insert( (Trunk*) new_node );
        break;
    }
}




/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree::Root
 *      Method:  Root
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
RTree::Root::Root() {

    type = node_root_t;
    parent = NULL;
}  /* -----  end of method RTree::Root::Root  (constructor)  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree::Root
 *      Method:  RTree::Root :: insert
 * Description:  Root inserts leaves by sending it to the correct child to be inserted
 *                  into the first branch that it hits.
 *--------------------------------------------------------------------------------------
 */
void RTree::Root::insert( RTree::Leaf *leaf ) {

    if( num_children == 0 ) {
        // Root should never have any leaves as children so a Branch is created
        // if there isn't one already
        children[0]  = new Branch();
        children[0]->adopt( this );
        num_children = 1;
        children[0]->insert( leaf );

    } else {
        //if( num_children == 1 ) {
        int i;
        for( i = 1; i < num_children; ++i ) {
            if( greater_than( leaf, children[i] ) ) {
                break;
            }
        }
        children[i-1]->insert( leaf );
    }
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree::Root
 *      Method:  RTree::Root :: insert
 * Description:  non-leaf nodes are inserted into the correct place according to their
 *                  greatest hilbert value. If there are too many children already
 *                  root splits itself (as opposed to overflowing which is what Trunk
 *                  would normally do).
 *--------------------------------------------------------------------------------------
 */
void RTree::Root::insert( RTree::Trunk *new_node ) {

    if( num_children >= max_children ) {
        // Root doesn't have a parent to overflow so it splits
        Dynamic_array<RTree::Node*> children_nodes;

        // gather up a list of all the children notice it is adopting it's own children
        int children_list_size;
        Node **adopted_children = adopt_children( children_list_size );
        children_nodes.add( adopted_children, children_list_size ); 

        // add in the node causing the overflow
        children_nodes.add( new_node );


        // sort them according to their hilbert values
        children_nodes.sort( less_than );

        // 
        children[0] = new Trunk( this );
        children[1] = new Trunk( this );
        num_children = 2;

        // add the leaves all into the children and the new node
        int size = children_nodes.get_size();
        int leaves_per = size/2;

        int k = 0;

        for( ; k < leaves_per; ++k ) {     // add most of the leaves into the children
            children[0]->insert( children_nodes[k] );
        }

        for( ; k < size; ++k ) {           // add the remainder into the new node
            children[1]->insert( children_nodes[k] );
        }

    } else { // There is enough room to insert the node

        // insert the new shape in the proper place according to it's hilbert value
        int k;
        uint64_t node_hilbert = new_node->get_hilbert();
        for( k = 0; k < num_children; ++k ) { // find the proper place
            if( node_hilbert > children[k]->get_hilbert() ) {
                break;
            }
        }
        for( int i = num_children+1; i > k; --i ) { // shift the children to make room
            children[i] = children[i-1];
        }
        children[k] = new_node;
        children[k]->adopt( this );

        this->bounds.invalidate();

        ++num_children;
    }
}  /* -----  end of method RTree::Root::insert  ----- */



/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree::Branch
 *      Method:  Branch
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */

RTree::Branch::Branch() {

    type = node_branch_t;
}  /* -----  end of method RTree::Branch::Branch  (constructor)  ----- */

void RTree::Branch::overflow( RTree::Node *new_node ) {
    
    // there is no reason a branch would overflow so if somehow it's attempted
    // it is obviously a problem that should be addressed
    printf("IllegalOverflow\n\n");
    throw "IllegalOverflow";
}

void RTree::Branch::insert( RTree::Leaf *leaf ) {

    if( num_children == max_children ) {
        parent->overflow( leaf );
    } else {
        // insert the new shape in the proper place according to it's hilbert value
        int k;
        Bounding_box *node_bounds = leaf->get_bounds();
        for( k = 0; k < num_children; ++k ) { // find the proper place
            if( (*node_bounds) > children[k]->get_bounds() ) {
                break;
            }
        }
        for( int i = num_children+1; i > k; --i ) { // shift the children to make room
            children[i] = children[i-1];
        }
        children[k] = leaf;
        leaf->adopt( this );

        bounds.invalidate();

        ++num_children;
    }
}

void RTree::Branch::insert( Trunk *new_node ) {

    // the only thing that can be inserted into branch is leaf nodes
    throw "IllegalInsertion";
}

void RTree::Branch::consolidate( ) {

}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree::Leaf
 *      Method:  Leaf
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */

RTree::Leaf::Leaf() {

    type = node_leaf_t;
}  /* -----  end of method RTree::Leaf::Leaf  (constructor)  ----- */

RTree::Leaf::Leaf( Shape *shape ) {

    type = node_leaf_t;
    set( shape );
}  /* -----  end of method RTree::Leaf::Leaf  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree::Leaf
 *      Method:  RTree::Leaf :: fit_bounds
 * Description:  This is called by Lazy_bounds evaluate function when the bounds for a
 *                  leaf need to be calculated. It sets the bounds as the 
 *                  largest x,y and smallest x,y of any of the points in the shape
 *
 *--------------------------------------------------------------------------------------
 */
void RTree::Leaf::fit_bounds( Bounding_box &bounds ) {

    // look through shape and find the bounds
    uint64_t min_x;
    uint64_t min_y;
    uint64_t max_x;
    uint64_t max_y;

    if( shape ) {
        shape->stretch( min_x, min_y, max_x, max_y );
        bounds.set( min_x, min_y, max_x, max_y );
    } else {

        bounds.set( 0, 0, 0, 0 );
    }
}

//inspectors
List<Shape*> *RTree::Leaf::search( Rectangle *query_window ) {

    if( shape->check_intersection( query_window ) ) {
        List<Shape*> *results = new List<Shape*>;
        results->add_front( shape );
        return results;
    } else {
        return NULL;
    }
}

List<Shape*> *RTree::Leaf::search( Point *query_point ) {

    if( shape->check_intersection( query_point ) ) {
        List<Shape*> *results = new List<Shape*>;
        results->add_front( shape );
        return results;
    } else {
        return NULL;
    }
}

bool RTree::Leaf::is_full() {
	return shape  ? true : false;
}

bool RTree::Leaf::is_empty() {
	return !shape ? true : false;
}

//mutators
void RTree::Leaf::set( Shape *shape ) {

    this->bounds.invalidate();
    this->bounds.clear_dependancies();
    this->shape = shape;
    // TODO set the bounds dependancies to be all of the points
    
}

RTree::Node **RTree::Leaf::adopt_children( int &size ) {
    size = 0;

    return NULL;
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  RTree::Leaf
 *      Method:  RTree::Leaf :: insert
 * Description:  it is illegal to insert into a leaf node so an exception will be thrown
 *                  if any of these methods are used.
 *
 *--------------------------------------------------------------------------------------
 */
void RTree::Leaf::insert( RTree::Leaf *leaf ) {
    throw "IllegalInsertion";
}

void RTree::Leaf::insert( RTree::Trunk *new_node ) {
    throw "IllegalInsertion";
}

void RTree::Leaf::insert( RTree::Node *new_node ) {
    throw "IllegalInsertion";
}




