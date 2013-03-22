/*
 * =====================================================================================
 *
 *       Filename:  hash_table.h
 *
 *    Description:  hash table implementation
 *
 *        Version:  1.0
 *        Created:  03/19/2013 05:47:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */



// universal hash functions
class Hash_table {
private:
    int size;
    int current_loading;

    List **data;
    

    int num_elements_added;
    int num_elements_deleted;
    int num_collisions;

    int *collisions; // use frequency
                    
    int hash();
public:

    Hash_table();

    int find( );
    int insert();
    int remove();


};






