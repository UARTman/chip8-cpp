//
// Created by uartman on 12.07.2021.
//

#include "Screen.h"

bool Core::Screen::DrawSprite(uint8_t x, uint8_t y, uint8_t *sprite, uint8_t size) {
    bool acc = false;
    for (int i = 0; i < size; ++i) {
        acc = acc | DrawLine(x, y + i, sprite[i]);
    }
    return acc;
}

bool Core::Screen::DrawLine(uint8_t x, uint8_t y, uint8_t line) {
    y = y % 32;
    bool acc = false;
    for (int i = 0; i < 8; ++i) {
        bool n = (bool)((line >> (7 - i)) & 1);
        acc = acc | DrawPixel(x + i, y, n);
    }
    return acc;
}

bool Core::Screen::DrawPixel(uint8_t x, uint8_t y, bool nibble) {
    x = x % 64;
    return DrawPixelUnchecked(x, y, nibble);
}


