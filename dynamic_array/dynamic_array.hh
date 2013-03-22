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
 *
 *
 *  */
    class mass {
    public:
        mass();

        bool equal( T param );
        bool not_equal( T param );
        bool greater( T param );
        bool greater_equal( T param );
        bool less( T param );
        bool less_equal( T param );
        bool between( T param1, T param2 );

        void add( T param );
        void subtract( T param );
        void multiply( T param );
        void divide( T param );
        void modulo( T param );

        void pow( int param );

        void sort_ascending();
        void sort_descending();


        //sugar 
        
        //logic operators 
        bool operator==( T param );          // equal
        bool operator!=( T param );          // not_equal
        bool operator>(  T param );          // greater
        bool operator>=( T param );          // greater_equal
        bool operator<(  T param );          // less
        bool operator<=( T param );          // less_equal
        bool operator()( T param, T param ); // between


        // use threads if possible       
        void operator+=( T param ); 
        void operator-=( T param ); 
        void operator*=( T param ); 
        void operator/=( T param ); 
        void operator%=( T param ); 

        // don't thread
        void operator+( T param ); 
        void operator-( T param ); 
        void operator*( T param ); 
        void operator/( T param ); 
        void operator%( T param ); 

        //misc
        T operator++(int); // suffix 

        // sort
        void operator+(); // sort_ascending
        void operator-(); // sort_descending
        

    private:
        Dynamic_array<T> *owner;
        int indices[];
        int num_indices;

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

//sugar
    T& operator[]( int index ); // does not do bounds checking (get_now)
    void operator+( T num );    // same as add
    
};

#include "dynamic_array.hxx"
#endif
