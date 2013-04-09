/*
 * =====================================================================================
 *
 *       Filename:  dynamic_array.hh
 *
 *    Description:  a generic dynamic array implementation
 *
 *        Version:  1.0
 *        Created:  03/12/2013 11:57:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _DYNAMIC_ARRAY_HH__
#define _DYNAMIC_ARRAY_HH__
#include <stdlib.h>
#include <math.h>
#include "../linkedlist/list.h"

template<class T>
class Dynamic_array {
private:
    int capacity;
    int size;

    T *data;

public:
    class iterator {
    public:
        iterator();
        iterator( Dynamic_array<T> *o );
        iterator( Dynamic_array<T> *o, int start );

        T next();
        T previous();
        T get();

        void insert( T num );
        void set( T num );

        bool end();
        bool start();

        //sugar
        T operator--(); 
        T operator++(); 
        T forward();
        T back();
        
    private: 
        Dynamic_array<T> *owner;
        int current_index;
    };

/*  
 *  These do operations in an APL esque manner
 *  each operation is done on the whole mass group
 *
 *  logic operators will return a new mass with only elements
 *  fulfilling that condition
 *  
 *  m += 7 will add 7 to every element of the mass
 *
 *  sorting a mass will NOT sort the actual information
 *
 *  to use comparisons or sorts on information other than numbers
 *  input a comparison function to handle that sort of thing
 *
 *  it is important to note that changes to the array should not
 *  be made at the same time a mass is in use
 *
 *  */
    class mass {
    private:
        Dynamic_array<T> *owner;
        int *indices;
        int num_indices;
        int size;

    public:
        //constructors
        mass();
        mass( Dynamic_array<T> *o );

        //logic functions
        mass &equal(         T param );
        mass &not_equal(     T param );
        mass &greater(       T param );
        mass &greater_equal( T param );
        mass &less(          T param );
        mass &less_equal(    T param );
        mass &between(       T param1, T param2 );

        mass &and_op( T param );
        mass &or_op(  T param );

        //arithmetic functions
        mass &add(      T param );
        mass &subtract( T param );
        mass &multiply( T param );
        mass &divide(   T param );
        mass &modulo(   T param );

        mass &pow( int param );

        void sort_ascending( );
        void sort_descending( );

        T *get( int &size ); // not implemented
        mass &duplicate();
        int get_size();

        //sugar 
        
        //logic operators 
        mass &operator==( T param );            // equal
        mass &operator!=( T param );            // not_equal
        mass &operator>(  T param );            // greater
        mass &operator>=( T param );            // greater_equal
        mass &operator<(  T param );            // less
        mass &operator<=( T param );            // less_equal
        mass &operator()( T param1, T param2 ); // between

        mass &operator&&( mass param );
        mass &operator||( mass param );


        T operator+=( T param ); // add
        T operator-=( T param ); // subtract
        T operator*=( T param ); // multiply
        T operator/=( T param ); // divide
        T operator%=( T param ); // modulo

        mass &operator+( T param ); 
        mass &operator-( T param ); 
        mass &operator*( T param ); 
        mass &operator/( T param ); 
        mass &operator%( T param ); 

        //misc
        T operator++(int); // suffix 

        // sort
        void operator+(); // sort_ascending
        void operator-(); // sort_descending

        bool operator!( );

    };

    friend class iterator;
    friend class mass;

//constructor
    Dynamic_array();
    Dynamic_array( int initial_size );
    Dynamic_array( T arr[], int array_size, int initial_size );

//destructor
    ~Dynamic_array();

//mutators
    void add( T num );
    void add( T arr[], int arr_size );
    void add( Dynamic_array<T> *d_arr );
    void add( List<T> *list );

    void insert( T num, int index );

//inspectors
    T& get( int index );     // bounds checking
    T& get_now( int index ); // no bounds checking

    int get_size();
    int get_capacity();

//methods
    void resize( int new_size );
    void fit();
    void sort(); // needs comparison function

    Dynamic_array<T>::iterator *begin();
    Dynamic_array<T>::iterator *end();

    Dynamic_array<T>::mass *mass_op();

//sugar
    T& operator[]( int index ); // does not do bounds checking (get_now)
    void operator+( T num );    // same as add
    
};

#include "dynamic_array.hxx"
#endif
