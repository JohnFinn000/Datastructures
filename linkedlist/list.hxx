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

template<class T>
List<T>::~List() {

}

template<class T>
typename List<T>::link *List<T>::get_head() {
	return head;
}

template<class T>
void List<T>::add_front( T node ) {
	link *new_node = new link;
	new_node->node = new T;
	(*new_node->node) = node;
	new_node->next = head;
	head = new_node;
}


template<class T>
void List<T>::remove_front() {
	link *temp = head;
	if( head ) {
		head = head->next;
	}
	free(temp);
}

template<class T>
void List<T>::add_back( T node ) {
	link *new_node = new link;
	new_node->node = node;
	new_node->next = NULL;

	(*tail) = new_node;
	tail = &((*tail)->next);
	
}

template<class T>
void List<T>::splice( List *splicee ) {
	(*tail) = splicee->get_head();
}

template<class T>
typename List<T>::iterator *List<T>::begin() {
	List::iterator *iter = new List::iterator( head );
	return iter;
}

template<class T>
typename List<T>::iterator *List<T>::end() {
	List::iterator *iter = new List::iterator( *tail );
	return iter;
}


//sugar
template<class T>
void List<T>::operator+( T node ) {
	add_front( node );
}

template<class T>
void List<T>::operator+( List l ) {
	splice( l );
}

template<class T>
void List<T>::operator--() {
	remove_front();
}

#endif
