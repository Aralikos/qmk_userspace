#pragma once

// The colour the keyboard had under the stock VIA firmware, read back over VIA
// on 2026-09-23: solid colour, hue 208, sat 188 (#eb43ff), brightness 208.
// VIA reports brightness scaled to the maximum, and 208 is only reachable with
// no cap (255). The current BKB tree caps at 50, which flashed about 4x dimmer
// than the old firmware, so the cap goes back to QMK's default.
#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#undef RGB_MATRIX_DEFAULT_MODE
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#undef RGB_MATRIX_DEFAULT_HUE
#define RGB_MATRIX_DEFAULT_HUE 208
#undef RGB_MATRIX_DEFAULT_SAT
#define RGB_MATRIX_DEFAULT_SAT 188
#undef RGB_MATRIX_DEFAULT_VAL
#define RGB_MATRIX_DEFAULT_VAL 208
#undef RGB_MATRIX_DEFAULT_SPD
#define RGB_MATRIX_DEFAULT_SPD 255
