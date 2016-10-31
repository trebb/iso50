/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(void);
static void init_rows(void);
static void unselect_cols(void);
static void select_col(uint8_t row);


inline uint8_t
matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline uint8_t
matrix_cols(void)
{
    return MATRIX_COLS;
}

void
matrix_init(void)
{
    // initialize row and col
    unselect_cols();
    init_rows();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t
matrix_scan(void)
{
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_col(col);
        _delay_us(30);  // without this wait read unstable value.
        uint8_t rows = read_rows();
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
            bool curr_bit = rows & (1<<row);
            if (prev_bit != curr_bit) {
                matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
                if (debouncing) {
                    debug("bounce!: "); debug_hex(debouncing); debug("\n");
                }
                debouncing = DEBOUNCE;
            }
            unselect_cols();
        }
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

bool
matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline bool
matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline matrix_row_t
matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void
matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t
matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

/* Row pin configuration
 * row: 0  1  2  3
 * pin: C6 C7 F0 B5
 */
static void
init_rows(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRB  &= ~0b00100000;
    PORTB |=  0b00100000;
    DDRC  &= ~0b11000000;
    PORTC |=  0b11000000;
    DDRF  &= ~0b00000001;
    PORTF |=  0b00000001;
}

static uint8_t
read_rows(void)
{
    return
        (PINC&(1<<6) ? 0 : (1<<0)) |
        (PINC&(1<<7) ? 0 : (1<<1)) |
        (PINF&(1<<0) ? 0 : (1<<2)) |
        (PINB&(1<<5) ? 0 : (1<<3));
}


/* Column pin configuration
 * col: 0  1  2  3  4  5  6  7  8  9  A  B  C  D
 * pin: B4 D7 D6 B7 D0 B0 B1 B2 F1 F4 F5 F6 F7 B6
 */
static void
unselect_cols(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRB  |= 0b11010111;
    PORTB |= 0b11010111;
    DDRD  |= 0b11000001;
    PORTD |= 0b11000001;
    DDRF  |= 0b11110010;
    PORTF |= 0b11110010;
}

static void
select_col(uint8_t col)
{
    // Output low(DDR:1, PORT:0) to select
    switch (col) {
        case 0x0:
            DDRB  |= (1<<4);
            PORTB &= ~(1<<4);
            break;
        case 0x1:
            DDRD  |= (1<<7);
            PORTD &= ~(1<<7);
            break;
        case 0x2:
            DDRD  |= (1<<6);
            PORTD &= ~(1<<6);
            break;
        case 0x3:
            DDRB  |= (1<<7);
            PORTB &= ~(1<<7);
            break;
        case 0x4:
            DDRD  |= (1<<0);
            PORTD &= ~(1<<0);
            break;
        case 0x5:
            DDRB  |= (1<<0);
            PORTB &= ~(1<<0);
            break;
        case 0x6:
            DDRB  |= (1<<1);
            PORTB &= ~(1<<1);
            break;
        case 0x7:
            DDRB  |= (1<<2);
            PORTB &= ~(1<<2);
            break;
        case 0x8:
            DDRF  |= (1<<1);
            PORTF &= ~(1<<1);
            break;
        case 0x9:
            DDRF  |= (1<<4);
            PORTF &= ~(1<<4);
            break;
        case 0xa:
            DDRF  |= (1<<5);
            PORTF &= ~(1<<5);
            break;
        case 0xb:
            DDRF  |= (1<<6);
            PORTF &= ~(1<<6);
            break;
        case 0xc:
            DDRF  |= (1<<7);
            PORTF &= ~(1<<7);
            break;
        case 0xd:
            DDRB  |= (1<<6);
            PORTB &= ~(1<<6);
            break;
    }
}
