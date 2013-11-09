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
#include "../sort.h"
#include "../../unittests/test_data.h"
#include "gtest/gtest.h"

template <typename T>
class sort_test : public testing::Test {
public:
    sort_test() { }

    void SetUp() { }

    void TearDown() { }

    ~sort_test() { }
};

TYPED_TEST_CASE_P( sort_test );

TYPED_TEST_P( sort_test, bubble_sort_ut ) {
    TypeParam *rand_data;
    TypeParam *asc_data;
    test_data::get_random_data( &rand_data );
    test_data::get_ascending_data( &asc_data );
    int size = 10;
    
    bubble_sort( rand_data, size );

    for( int i = 0; i < size; ++i ) {
        //EXPECT_EQ( asc_data[i], rand_data[i] );
    }
}

TYPED_TEST_P( sort_test, insertion_sort_ut ) {
    TypeParam *rand_data;
    TypeParam *asc_data;
    test_data::get_random_data( &rand_data );
    test_data::get_ascending_data( &asc_data );
    int size = 10;
    
    insertion_sort( rand_data, size );

    for( int i = 0; i < size; ++i ) {
        EXPECT_EQ( asc_data[i], rand_data[i] );
    }
}

TYPED_TEST_P( sort_test, selection_sort_ut ) {
    TypeParam *rand_data;
    TypeParam *asc_data;
    test_data::get_random_data( &rand_data );
    test_data::get_ascending_data( &asc_data );
    int size = 10;
    
    selection_sort( rand_data, size );

    for( int i = 0; i < size; ++i ) {
        EXPECT_EQ( asc_data[i], rand_data[i] );
    }
}

/*
TYPED_TEST_P( sort_test, merge_sort ) {
    TypeParam *rand_data;
    TypeParam *asc_data;
    test_data::get_random_data( &rand_data );
    test_data::get_ascending_data( &asc_data );
    int size = 10;
    
    merge_sort( rand_data, size );

    for( int i = 0; i < size; ++i ) {
        EXPECT_EQ( asc_data[i], rand_data[i] );
    }
}
*/

REGISTER_TYPED_TEST_CASE_P( sort_test, bubble_sort_ut, insertion_sort_ut, selection_sort_ut );

typedef ::testing::Types<char, int, unsigned int> ListTypes;
INSTANTIATE_TYPED_TEST_CASE_P( My, sort_test, ListTypes );

GTEST_API_ int main( int argc, char **argv ) {
    printf("Running main() from datastructures/sorts/unittests/main.cpp\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

