/*
 * =====================================================================================
 *
 *       Filename:  list.hxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/17/2012 03:56:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (JF), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _LIST_HXX__
#define _LIST_HXX__
#include "list.h"

//List
template<class T>
List<T>::List() {
	head = NULL;
	tail = &head;
}

template<class T> // TODO make this a working copy constructor
List<T>::List( const List &other ) {
	head = NULL;
	tail = &head;
}

template<class T>
List<T>::~List() {

}

template<class T>
void List<T>::add( T node ) {
    add_front( node );
}

template<class T>
void List<T>::add_front( T node ) {
	link *new_node = new link;
	new_node->node = new T( node );
	//(*new_node->node) = node;
	if( head ) {
        new_node->next = head;
        head = new_node;
	} else {
        new_node->next = NULL;
        head = new_node;

	    tail = &(new_node->next);
    }

}

template<class T>
void List<T>::add_back( T node ) {
    link *new_node = new link;
    new_node->node = new T( node );
    new_node->next = NULL;

    (*tail) = new_node;
    tail = &((*tail)->next);

    if( !head ) {
        head = new_node;
    }
}

template<class T>
void List<T>::splice( List splicee ) { //TODO make sure this works correctly
	(*tail) = &(*splicee.get_head());
    tail = splicee.get_tail();
}

template<class T>
T List<T>::remove_front() {
	if( head ) {
	    link *temp = head;
        T* value = head->node;
		head = head->next;
	    free(temp);
        return *value;
	} else {
        return 0;
    }
}

template<class T>
T* List<T>::get( int index __attribute__((unused))) {
	if( head ) {
        return head->node;
	} else {
        return 0;
    }
}

template<class T>
T& List<T>::get_now( int index __attribute__((unused)) ) {
    return *head->node;
}

template<class T>
typename List<T>::link *List<T>::get_head() {
	return head;
}

template<class T>
typename List<T>::link **List<T>::get_tail() {
	return tail;
}

template<class T>
typename List<T>::forward_iterator *List<T>::begin() {
	List::forward_iterator *iter = new List::forward_iterator( this, head );
	return iter;
}

template<class T>
typename List<T>::forward_iterator *List<T>::end() {
	List::forward_iterator *iter = new List::forward_iterator( this, *tail );
	return iter;
}


//sugar
template<class T> //TODO make this the assignment operator
List<T>& List<T>::operator=( const List &other ) {

}

template<class T>
void List<T>::operator+( T node ) {
	add_front( node );
}

template<class T>
void List<T>::operator+( List l ) {
	splice( l );
}

template<class T>
T List<T>::operator--() {
	return remove_front();
}

template<class T>
T List<T>::operator--( int ) {
	return remove_front();
}

#endif
