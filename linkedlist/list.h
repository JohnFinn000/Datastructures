/*
 * =====================================================================================
 *
 *       Filename:  list.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/17/2012 03:53:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (JF), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

template<class T>
class List {
private:

	struct link {
		T    *node;
		link *next;
	};

	link *head;
	link **tail;

public:

	class iterator {
	private:

		link *current;

	public:

		iterator();
		iterator( link *start );
		
		T next();
		T get();

		void insert( T *node ); // not implemented
		void set( T *node );    // not implemented

        bool end();
        bool start();

		//sugar
		T *operator+( T node );
		T *operator-( T node );
		T *operator++();      // prefix
		T *operator++( int ); // suffix
		bool operator==( T node );
		bool operator==( List l );
		bool operator==( iterator *iter );
		bool operator!=( iterator *iter );

	};

//constructor
	List();

//destructor
	~List();

//mutators
	void add_front( T node );
	void add_back( T node );
	void splice( List *splicee );
	void remove_front();

//inspectors
	link *get_head();	

	List<T>::iterator *begin();
	List<T>::iterator *end();

//sugar
	void operator+( T node ); // same as add
	void operator+( List l ); // same as splice
	void operator--();        // same as remove front

};

