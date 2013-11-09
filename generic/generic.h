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
    virtual T* get( int index = 0 ) = 0;
    virtual T& get_now( int index = 0 ) = 0;

    //sugar 
    void operator+( T param ); // add
    void operator-( T param ); // remove

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

        virtual T* get() = 0;

        /* ====================  MUTATORS      ======================================= */
        virtual void insert( T& val ) = 0;
        virtual T* remove( ) = 0;
        virtual void set( T& val ) = 0;

        /* ====================  OPERATORS     ======================================= */
        iterator& operator=( const iterator &other ); /* assignment operator */
        void operator+( T val ); 
        T operator-(); 
        void operator=( T val ); 
        
    private: 
        /* ====================  DATA MEMBERS  ======================================= */
    }; /* -----  end of class iterator  ----- */

    class forward_iterator: public iterable<T>::iterator {
    public:
        /* ====================  LIFECYCLE     ======================================= */
        forward_iterator() {}                             /* constructor      */
        forward_iterator( const forward_iterator &other );   /* copy constructor */

        ~forward_iterator ();                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */
        virtual T* next() = 0;
        virtual T* next_() = 0;

        /* ====================  MUTATORS      ======================================= */

        /* ====================  OPERATORS     ======================================= */
        forward_iterator& operator=( const forward_iterator &other ); /* assignment operator */

        T operator++();
        T operator++( int ); //suffix
        T forward();
        
    private: 
        /* ====================  DATA MEMBERS  ======================================= */
    }; /* -----  end of class forward_iterator  ----- */

    class reverse_iterator: public iterable<T>::iterator {
    public:
        /* ====================  LIFECYCLE     ======================================= */
        reverse_iterator() {}                             /* constructor      */
        reverse_iterator( const reverse_iterator &other );   /* copy constructor */

        ~reverse_iterator ();                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */
        virtual T* previous() = 0;
        virtual T* previous_() = 0;

        /* ====================  MUTATORS      ======================================= */

        /* ====================  OPERATORS     ======================================= */
        reverse_iterator& operator=( const reverse_iterator &other ); /* assignment operator */

        T operator--(); 
        T operator--( int ); //suffix
        T back();
        
    private: 
        /* ====================  DATA MEMBERS  ======================================= */
    }; /* -----  end of class reverse_iterator  ----- */

    class traverse_iterator: public iterable<T>::forward_iterator, iterable<T>::reverse_iterator {
    public:
        /* ====================  LIFECYCLE     ======================================= */
        traverse_iterator() {}                             /* constructor      */
        traverse_iterator( const traverse_iterator &other );   /* copy constructor */

        ~traverse_iterator();                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */

        /* ====================  OPERATORS     ======================================= */
        traverse_iterator& operator=( const traverse_iterator &other ); /* assignment operator */

        
    private: 
        /* ====================  DATA MEMBERS  ======================================= */
    }; /* -----  end of class iterator  ----- */

    virtual iterable<T>::iterator *begin() = 0;
    virtual iterable<T>::iterator *end() = 0;
    
};

#include "generic.hxx"
#endif

