/*
 * =====================================================================================
 *
 *       Filename:  linkedlist_ut.cpp
 *
 *    Description:  unit testing for the linked list class
 *
 *        Version:  1.0
 *        Created:  10/19/2013 03:26:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "../list.h"
#include "../../unittests/test_data.h"
#include "gtest/gtest.h"

template <typename T>
class linkedlist_test : public testing::Test {
public:
    linkedlist_test() { }

    void SetUp() { }

    void TearDown() { }

    ~linkedlist_test() { }

    List<T> list;
};

TYPED_TEST_CASE_P( linkedlist_test );

TYPED_TEST_P( linkedlist_test, add_front ) {
    TypeParam *asc_data;
    TypeParam *des_data;
    test_data::get_ascending_data( &asc_data );
    test_data::get_descending_data( &des_data );
    
    int num = 10;
    for( int i = 0; i < num; ++i ) {
	    this->list.add_front( asc_data[i] );
    }
    for( int i = 0; i < num; ++i ) {
        EXPECT_EQ( des_data[i], this->list.remove_front() );
    }
    EXPECT_EQ( 0, this->list.remove_front() );
}

TYPED_TEST_P( linkedlist_test, add_back ) {
    TypeParam *asc_data;
    TypeParam *des_data;
    test_data::get_ascending_data( &asc_data );
    test_data::get_descending_data( &des_data );
    
    int num = 10;
    for( int i = 0; i < num; ++i ) {
	    this->list.add_back( asc_data[i] );
    }
    for( int i = 0; i < num; ++i ) {
        EXPECT_EQ( asc_data[i], this->list.remove_front() );
    }
    EXPECT_EQ( 0, this->list.remove_front() );
}

TYPED_TEST_P( linkedlist_test, iterator ) {
/*
    TypeParam *asc_data;
    TypeParam *des_data;
    test_data::get_ascending_data( &asc_data );
    test_data::get_descending_data( &des_data );
    
    int num = 10;
    for( int i = 0; i < num; ++i ) {
	    this->list.add_front( asc_data[i] );
    }

    typename List<TypeParam>::iterator *iter = this->list.begin();
    typename List<TypeParam>::iterator *end = this->list.end();
    for( int i = 0; !iter->end(); iter->next(), ++i ) {
        EXPECT_EQ( des_data[i], iter->get() );
    }
*/
}

REGISTER_TYPED_TEST_CASE_P( linkedlist_test, add_front, add_back, iterator );

typedef ::testing::Types<int, unsigned int> ListTypes;
INSTANTIATE_TYPED_TEST_CASE_P( My, linkedlist_test, ListTypes );

GTEST_API_ int main( int argc, char **argv ) {
    printf("Running main() from datastructures/linkedlist/unittests/main.cpp\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

