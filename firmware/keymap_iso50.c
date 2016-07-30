#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* qwerty */
    [0] = KEYMAP(
        ESC ,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,LBRC,RBRC,
        TAB ,   A,   S,   D,   F,   G,   H,   J,   K,   L,SCLN,QUOT,NUHS, ENT,
        LSFT,NUBS,   Z,   X,   C,   V,   B,   N,   M,COMM, DOT,SLSH,RSFT,BSPC,
        LCTL,LGUI,LALT, FN0,                FN1, FN2, SPC, FN4,RGUI, APP,RCTL),
    /* Num */
    [1] = KEYMAP(
        1   ,   2,   3,   4,   5,   6,   7,   8,   9,   0,MINS, EQL,PPLS,
        F1  ,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12, GRV,PENT,
        TRNS,  P1,  P2,  P3,  P4,  P5,  P6,  P7,  P8,  P9,  P0,PMNS,TRNS,PDOT,
        TRNS,TRNS,TRNS,TRNS,                FN3,TRNS,PDOT,TRNS,TRNS,TRNS,TRNS),
    /* Nav */
    [2] = KEYMAP(
        TRNS,  NO,  UP,  NO,  NO,  NO,  NO,PGUP,  UP,PGDN,PSCR,SLCK,PAUS,
        NO  ,LEFT,DOWN,RGHT,  NO,  NO,HOME,LEFT,DOWN,RGHT, INS, DEL,  NO,  NO,
        TRNS,MUTE,VOLD,EJCT,VOLU,  NO,  NO, END,  NO,  NO,  NO,  NO,TRNS, DEL,
        TRNS,TRNS,TRNS, FN3,               TRNS,TRNS,CAPS,TRNS,TRNS,TRNS,TRNS),
    /* Num + Nav */
    [3] = KEYMAP(
        TRNS,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,
        NO  ,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,TRNS, DEL,
        TRNS,TRNS,TRNS,TRNS,               TRNS,TRNS,NLCK,TRNS,TRNS,TRNS,TRNS),
    /* Rat */
    [4] = KEYMAP(
        TRNS,  NO,  NO,  NO,  NO,  NO,WH_L,WH_U,MS_U,WH_D,WH_R,  NO,  NO,
        NO  ,  NO,  NO,  NO,  NO,  NO,BTN2,MS_L,MS_D,MS_R,BTN1,  NO,  NO,  NO,
        TRNS,  NO,  NO,  NO,  NO,  NO,BTN3,BTN2,BTN1,BTN4,BTN5,  NO,TRNS,  NO,
        TRNS,TRNS,TRNS,  NO,                 NO,TRNS,BTN1,TRNS,TRNS,TRNS,TRNS),
    /* Alt Gr */
    [5] = KEYMAP(
        ESC ,   Q,   W,   E,   R,   6,   7,   8,   9,   0,MINS,LBRC,RBRC,
        TAB ,   A,   S,   D,   F,   G,   H,   J,   K,   L,SCLN,QUOT,NUHS, ENT,
        LSFT,NUBS,   Z,   X,   C,   V,   B,   N,   M,COMM, DOT,SLSH,RSFT,BSPC,
        LCTL,LGUI,LALT, FN0,                FN1, FN2, SPC,RALT,RGUI, APP,RCTL),
};

enum macro_id {
    ALTGR,
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1), /* Num */
    [1] = ACTION_LAYER_MOMENTARY(2), /* Nav */
    [2] = ACTION_LAYER_MOMENTARY(4), /* Rat */
    [3] = ACTION_LAYER_MOMENTARY(3), /* Num + Nav */
    [4] = ACTION_MACRO(ALTGR),       /* Alt Gr; invoking macro */
    [5] = ACTION_LAYER_MOMENTARY(5), /* Alt Gr; used in macro */
};

/*
 * Macro definition
 */
const macro_t *
action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
    case ALTGR:
        return (record->event.pressed ?
                MACRO(D(RALT), D(FN5), END) :
                MACRO(U(RALT), U(FN5), END));
        break;
    }
    return MACRO_NONE;
}
