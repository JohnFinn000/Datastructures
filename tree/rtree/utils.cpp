/*
 * =====================================================================================
 *
 *       Filename:  utils.cpp
 *
 *    Description:  various utilities
 *
 *        Version:  1.0
 *        Created:  04/16/2013 07:49:02 PM
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
#include <inttypes.h>
#include "hilbert_tables.h"

void generate_hilbert_to_point_table(); 
void generate_point_to_hilbert_table();
void point_to_hilbert_base( uint64_t x, uint64_t y, uint64_t &hilbert );
void hilbert_to_point_base( uint64_t hilbert, uint64_t &x, uint64_t &y );

const int maximum_order = 7;

char *int_to_binary( uint64_t num, int precision ) {
    
    char *arr = (char*) malloc( sizeof(char) * (precision + 1) );
    arr[precision] = '\0';

    for( uint64_t i = precision; i > 0; --i ) {
        arr[precision-i] = (num & (1 << (i-1))) ? '1' : '0';
    }
    
    return arr;

}
// uses more extended tables to decode hilbert values more quickly
void hilbert_to_point( uint64_t hilbert, uint64_t &x, uint64_t &y ) {
/*
		      old_state
             /               partial hilbert value
        ____/                /
        |   |_______________/
	    |   |               |
code    |0 0|0 0 0 0 0 0 0 0|
        |___|_______________|

*/
	uint64_t code = 0;
    x = 0;
    y = 0;

    int step = (maximum_order * 2) - 8;

	for( ; step >= 0; step -= 8 ) {

		code  &= 0X300;
        code |= (( hilbert >> step ) & 0xFF );

		code = xy_table_256[code];

		x <<= 4;
		x |= (( code >> 4 ) & 0XF );

		y <<= 4;
		y |= ( code & 0XF );
        
	}
/*
    uint64_t num = 0;
    uint64_t state = 0;
	for( ; step >= 0; step -= 8 ) {

        code = (( hilbert >> step ) & 0xFF );

		num = xy_table_256[code] ^ state;
        
        // 0 0X00       
        // 1 0X0F       
        // 2 0XF0       
        // 3 0XFF       
		

		x <<= 4;
		x |= (( code >> 4 ) & 0XF );

		y <<= 4;
		y |= ( code & 0XF );
        
	}
*/
}

void point_to_hilbert_base( uint64_t x, uint64_t y, uint64_t &hilbert ) {
	/*
		   current_state
		   /  x coord
		  /   / y coord
		 /\  / /
code	0 0 0 0
	*/
	uint64_t code;
	uint64_t hilbert_value = 0;
	uint64_t curve_length  = 0;
	uint64_t current_state = 0;

	for( int step = maximum_order; step >= 0; --step ) {

		code  = current_state << 2;
		code |= ( x & ( 1 << step ) ) ? 2 : 0;
		code |= ( y & ( 1 << step ) ) ? 1 : 0;

		curve_length  = hilbert_table[code];
        current_state = hilbert_state_table[code];

		hilbert_value <<= 2;
		hilbert_value |= curve_length;
	}
	hilbert = hilbert_value;
}

// this will only decode hilbert values using the smallest hilbert table
void hilbert_to_point_base( uint64_t hilbert, uint64_t &x, uint64_t &y ) {
	/*
		   old_state
		   /  new_state
		  /   / 
		 /\  /\
code	0 0 0 0
	*/
	uint8_t code = 0;
	uint8_t old_state = 0;
	uint8_t new_state = 0;
	uint8_t num = 0;
    x = 0;
    y = 0;

	for( int step = maximum_order; step >= 0; --step ) {

		code = ( old_state << 2 );
		code |= ( hilbert & ( 2 << (step * 2) ) ) ? 2 : 0;
		code |= ( hilbert & ( 1 << (step * 2) ) ) ? 1 : 0;

		num = xy_table_4[code];
        new_state = xy_state_table_4[code];

		x <<= 1;
		x |= (num & 2) ? 1 : 0;

		y <<= 1;
		y |= (num & 1) ? 1 : 0;

		old_state = new_state;

	}
}

int msb( uint64_t num ) {
    if( num == 0 ) {
        return 0;
    }
    int n = 64;
    (num & 0xFFFFFFFF00000000) == 0 ? (n -= 32, num = num << 32) : 0;
    (num & 0xFFFF000000000000) == 0 ? (n -= 16, num = num << 16) : 0;
    (num & 0xFF00000000000000) == 0 ? (n -= 8,  num = num << 8 ) : 0;
    (num & 0xF000000000000000) == 0 ? (n -= 4,  num = num << 4 ) : 0;
    (num & 0xC000000000000000) == 0 ? (n -= 2,  num = num << 2 ) : 0;
    (num & 0x8000000000000000) == 0 ? (n -= 1,  num = num << 1 ) : 0;
    return n;

}

void generate_hilbert_to_point_table( ) {

    uint64_t x = 0;
    uint64_t y = 0;
	uint64_t code = 0;
	uint64_t old_state = 0;
	uint64_t new_state = 0;
	uint64_t num = 0;

    //uint64_t iterations = 1;

    for( uint64_t start_state = 0; start_state < 4; ++start_state ) {
        for( uint64_t new_hil = 0; new_hil < 65536; ++new_hil ) {
            old_state = start_state;
            x = 0;
            y = 0;
            for( int step = 4; step >= 0; --step ) {

                code = ( old_state << 2 );
                code |= ( new_hil & ( 2 << (step * 2) ) ) ? 2 : 0;
                code |= ( new_hil & ( 1 << (step * 2) ) ) ? 1 : 0;

                num = xy_table_4[code];
                new_state = xy_state_table_4[code];

                x <<= 1;
                x |= (num & 2) ? 1 : 0;

                y <<= 1;
                y |= (num & 1) ? 1 : 0;

                old_state = new_state;

            }
            uint64_t new_num;
            new_num = x;
            if( (new_hil % 32) == 0 ) {
                printf("\n");
            }
            printf("%#.*lX,", new_num ? 2 : 4, new_num );
        }
        printf("\n\n");
        
    }

}

void generate_point_to_hilbert_table( ) {

    uint64_t x = 0;
    uint64_t y = 0;
	uint64_t code = 0;

	uint64_t hilbert_value = 0;
	uint64_t curve_length  = 0;
	uint64_t current_state = 0;


    for( uint64_t start_state = 0; start_state < 4; ++start_state ) {
        for( uint64_t new_hil = 0; new_hil < 256; ++new_hil ) {
            current_state = start_state;
            x = 0;
            y = 0;
            for( int step = 3; step >= 0; --step ) {

                code  = current_state << 2;
                code |= ( x & ( 1 << step ) ) ? 2 : 0;
                code |= ( y & ( 1 << step ) ) ? 1 : 0;

                curve_length  = hilbert_table[code];
                current_state = hilbert_state_table[code];

                hilbert_value <<= 2;
                hilbert_value |= curve_length;

            }
            uint64_t new_num;
            new_num = current_state << 8;
            new_num |= curve_length;
            if( (new_hil % 16) == 0 ) {
                printf("\n");
            }
            printf("%#.*lX,", new_num ? 3 : 5, new_num );
        }
        printf("\n\n");
        
    }

}

