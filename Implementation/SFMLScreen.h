#pragma once

#include "Core/Screen.h"
#include <SFML/Graphics.hpp>

namespace SFMLImpl {
    class SFMLScreen : public Core::Screen {
    public:
        sf::Texture m_texture;
        std::array<uint8_t, 4 * 64 * 32> m_framebuffer = {};

        SFMLScreen();
        bool DrawPixelUnchecked(uint8_t x, uint8_t y, bool nibble) override;
        void ClearScreen() override;
        bool DrawSprite(uint8_t x, uint8_t y, uint8_t *sprite, uint8_t size) override;
    private:
        void UpdateTexture();
        bool GetPixel(uint8_t x, uint8_t y);
        void SetPixel(uint8_t x, uint8_t y, bool pixel);

    };
}




