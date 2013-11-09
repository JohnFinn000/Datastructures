/*
 * =====================================================================================
 *
 *       Filename:  generic.h
 *
 *    Description:  This is a generic datastructure other's should inherit from and 
 *                  override. So that all of the functions can be in the correct format
 *
 *        Version:  1.0
 *        Created:  10/19/2013 03:02:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _GENERIC_H__
#define _GENERIC_H__

/* 
 * =====================================================================================
 *        Class:  generic
 *  Description:  the parent of all datastructures
 * =====================================================================================
 */
template<class T>
class generic {
public:
    virtual void add( T node ) = 0;
    virtual T get() = 0;

    //sugar 
    void operator+( T param ); // insert
    void operator-( T param ); // subtract

};

/* 
 * =====================================================================================
 *        Class:  sortable
 *  Description:  the parent of all datastructures capable of being sorted
 * =====================================================================================
 */
template<class T>
class sortable {

    virtual void sort() = 0;
    virtual void sort( bool (*compfunc)(T, T) ) = 0;
    virtual void sort_ascending( ) = 0;
    virtual void sort_descending( ) = 0;

    //sort
    void operator+(); // sort_ascending
    void operator-(); // sort_descending
};

/* 
 * =====================================================================================
 *        Class:  iterable
 *  Description:  the parent of all datastructures capable of being iterated
 * =====================================================================================
 */
template<class T>
class iterable {
public:
    class iterator {
    public:
        /* ====================  LIFECYCLE     ======================================= */
        iterator() {}                             /* constructor      */
        iterator( const iterator &other );   /* copy constructor */

        ~iterator ();                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */
        virtual bool end() = 0;
        virtual bool start() = 0;

        T next();
        T previous();
        T get();

        /* ====================  MUTATORS      ======================================= */
        void insert( T val );
        void set( T val );

        /* ====================  OPERATORS     ======================================= */
        iterator& operator=( const iterator &other ); /* assignment operator */

        T operator--(); 
        T operator++(); 
        T forward();
        T back();
        
    private: 
        /* ====================  DATA MEMBERS  ======================================= */
        //Dynamic_array<T> *owner;
        //int current_index;
    }; /* -----  end of class iterator  ----- */

    virtual iterable<T>::iterator *begin() = 0;
    virtual iterable<T>::iterator *end() = 0;
    
};

#include "generic.hxx"
#endif

