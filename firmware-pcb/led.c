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

#include <avr/io.h>
#include "stdint.h"
#include "led.h"

/*
 * LED pin configuration
 * LED: NumLock  CapsLock  ScrollLock
 * pin: D3, D5   D1, D2    B3, E6
 */

void
led_set(uint8_t usb_led)
{
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        DDRD |= (1<<3);
        PORTD |= (1<<3);
        DDRD |= (1<<5);
        PORTD |= (1<<5);
    } else {
        DDRD |= (1<<3);
        PORTD &= ~(1<<3);
        DDRD |= (1<<5);
        PORTD &= ~(1<<5);
    }
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        DDRD |= (1<<1);
        PORTD |= (1<<1);
        DDRD |= (1<<2);
        PORTD |= (1<<2);
    } else {
        DDRD |= (1<<1);
        PORTD &= ~(1<<1);
        DDRD |= (1<<2);
        PORTD &= ~(1<<2);
    }
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        DDRB |= (1<<3);
        PORTB |= (1<<3);
        DDRE |= (1<<6);
        PORTE |= (1<<6);
    } else {
        DDRB |= (1<<3);
        PORTB &= ~(1<<3);
        DDRE |= (1<<6);
        PORTE &= ~(1<<6);
    }
}
