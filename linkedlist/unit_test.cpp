/*
 * =====================================================================================
 *
 *       Filename:  unit_test.cpp
 *
 *    Description:  tests to verify that the list does what it should properly
 *
 *        Version:  1.0
 *        Created:  07/17/2012 08:57:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "list.cpp" 

void list_test();

int main() {

	list_test();
}

void list_test() {
	List<int> list;
	list.add_front( 1 );
	list.add_front( 2 );
	list.add_front( 3 );
	list.add_front( 4 );
	list.add_front( 5 );
	list.add_front( 6 );

	List<int>::iterator *iter = list.begin();

	for( ; !iter->end(); iter->next() ) {
		printf("%d\n", iter->get() );
	}

}


