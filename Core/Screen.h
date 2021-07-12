#pragma once

#include "common.h"

namespace Core {
    class Screen {
    public:
        virtual bool DrawPixelUnchecked(uint8_t x, uint8_t y, bool nibble) = 0;
        virtual void ClearScreen() = 0;
        bool DrawPixel(uint8_t x, uint8_t y, bool nibble);
        bool DrawLine(uint8_t x, uint8_t y, uint8_t line);
        virtual bool DrawSprite(uint8_t x, uint8_t y, uint8_t *sprite, uint8_t size);
    };
}



