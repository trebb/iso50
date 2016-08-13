#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = KEYMAP(               /* qwerty */
        ESC ,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,LBRC,RBRC,
        TAB ,   A,   S,   D,   F,   G,   H,   J,   K,   L,SCLN,QUOT,NUHS, ENT,
        LSFT,NUBS,   Z,   X,   C,   V,   B,   N,   M,COMM, DOT,SLSH,RSFT,BSPC,
        LCTL,LGUI,LALT, FN0, FN1,                FN2, SPC, FN3,RGUI, APP,RCTL),
    [1] = KEYMAP(               /* Num */
        1   ,   2,   3,   4,   5,   6,   7,   8,   9,   0,MINS, EQL,PPLS,
        F1  ,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12, GRV,PENT,
        TRNS,  P1,  P2,  P3,  P4,  P5,  P6,  P7,  P8,  P9,  P0,PMNS,TRNS,PDOT,
        TRNS,TRNS,TRNS,TRNS,  NO,                 NO,NLCK,  NO,TRNS,TRNS,TRNS),
    [2] = KEYMAP(               /* Nav */
        TRNS,  NO,  UP,  NO,  NO,  NO,  NO,PGUP,  UP,PGDN,PSCR,SLCK,PAUS,
        TRNS,LEFT,DOWN,RGHT,  NO,  NO,HOME,LEFT,DOWN,RGHT, INS, DEL,  NO,TRNS,
        TRNS,MUTE,VOLD,EJCT,VOLU,  NO,  NO, END,  NO,  NO,  NO,  NO,TRNS, DEL,
        TRNS,TRNS,TRNS,  NO,TRNS,                 NO,CAPS,  NO,TRNS,TRNS,TRNS),
    [3] = KEYMAP(               /* Rat */
        TRNS,  NO,  NO,  NO,  NO,  NO,WH_L,WH_U,MS_U,WH_D,WH_R,  NO,  NO,
        TRNS,  NO,  NO,  NO,  NO,  NO,BTN2,MS_L,MS_D,MS_R,BTN1,  NO,  NO,TRNS,
        TRNS,  NO,  NO,  NO,  NO,  NO,BTN3,BTN2,BTN1,BTN4,BTN5,  NO,TRNS,  NO,
        TRNS,TRNS,TRNS,  NO,  NO,               TRNS,BTN1,TRNS,TRNS,TRNS,TRNS),
    [4] = KEYMAP(               /* Alt Gr */
        TRNS,TRNS,TRNS,TRNS,TRNS,   6,   7,   8,   9,   0,MINS, EQL,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,  NO,  NO,                 NO,TRNS,TRNS,TRNS,TRNS,TRNS),
};

enum function_id {
    ALTGR,
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1), /* Num */
    [1] = ACTION_LAYER_MOMENTARY(2), /* Nav */
    [2] = ACTION_LAYER_MOMENTARY(3), /* Rat */
    [3] = ACTION_FUNCTION(ALTGR),    /* Alt Gr */
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
    case ALTGR:
        if (record->event.pressed) {
            add_mods(MOD_BIT(KC_RALT));
            layer_on(4);
        } else {
            del_mods(MOD_BIT(KC_RALT));
            layer_off(4);
        }
        break;
    }
}
