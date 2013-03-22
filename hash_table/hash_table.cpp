/*
 * =====================================================================================
 *
 *       Filename:  hash_table.cpp
 *
 *    Description:  hash table implementation
 *
 *        Version:  1.0
 *        Created:  03/21/2013 03:00:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

Hash_table::Hash_table() {

    num_elements_added = 0;
    num_elements_deleted = 0;
    num_collisions = 0;
    collisions = NULL;
    
    size = 64;
    current_loading = 0;

}

int Hash_table::hash( int new_element ) {

    return new_element % size;
}


int Hash_table::find() {

}

int Hash_table::insert() {

}

int Hash_table::remove() {

}

