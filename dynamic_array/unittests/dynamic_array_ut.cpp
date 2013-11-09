/*
 * =====================================================================================
 *
 *       Filename:  dynamic_array_ut.cpp
 *
 *    Description:  unit tests for the dynamic array class
 *
 *        Version:  1.0
 *        Created:  11/08/2013 09:47:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "../dynamic_array.hh"
#include "../../unittests/test_data.h"
#include "gtest/gtest.h"


template <typename T>
class dynamic_array_test : public testing::Test {
public:
    dynamic_array_test() { }

    void SetUp() { }

    void TearDown() { }

    ~dynamic_array_test() { }

    Dynamic_array<T> dyn_array;
};

TYPED_TEST_CASE_P( dynamic_array_test );

TYPED_TEST_P( dynamic_array_test, add ) {
    TypeParam *asc_data;
    test_data::get_ascending_data( &asc_data );
    
    int num = 10;
    for( int i = 0; i < num; ++i ) {
        this->dyn_array.add( asc_data[i] );
    }
    int i;
    for( i = 0; i < num; ++i ) {
        TypeParam* results = this->dyn_array.get(i);
        if( results != NULL ) {
            EXPECT_EQ( asc_data[i], *results );
        } else {   
            EXPECT_TRUE( results != NULL );
        }
    }
    EXPECT_EQ( NULL, this->dyn_array.get(i) );
}

TYPED_TEST_P( dynamic_array_test, add_array ) {
    TypeParam *asc_data;
    test_data::get_ascending_data( &asc_data );
    
    int num = 10;
    this->dyn_array.add( asc_data, num );

    int i;
    for( i = 0; i < num; ++i ) {
        TypeParam* results = this->dyn_array.get(i);
        if( results != NULL ) {
            EXPECT_EQ( asc_data[i], *results );
        } else {
            EXPECT_TRUE( results != NULL );
        }
    }
    EXPECT_EQ( NULL, this->dyn_array.get(i) );
}

TYPED_TEST_P( dynamic_array_test, add_dynamic_array ) {
    TypeParam *asc_data;
    test_data::get_ascending_data( &asc_data );
    Dynamic_array<TypeParam> dyn_array2;
    
    int num = 10;
    this->dyn_array.add( asc_data, num/2 );

    dyn_array2.add( asc_data+num/2, (num+1)/2 );

    this->dyn_array.add( &dyn_array2 );

    int i;
    for( i = 0; i < num; ++i ) {
        TypeParam* results = this->dyn_array.get(i);
        if( results != NULL ) {
            EXPECT_EQ( asc_data[i], *results );
        } else {
            EXPECT_TRUE( results != NULL );
        }
    }
    EXPECT_EQ( NULL, this->dyn_array.get(i) );
}

REGISTER_TYPED_TEST_CASE_P( dynamic_array_test, add, add_array, add_dynamic_array );

typedef ::testing::Types<int, unsigned int> ListTypes;
INSTANTIATE_TYPED_TEST_CASE_P( My, dynamic_array_test, ListTypes );

GTEST_API_ int main( int argc, char **argv ) {
    printf("Running main() from datastructures/dynamic_array/unittests/main.cpp\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

