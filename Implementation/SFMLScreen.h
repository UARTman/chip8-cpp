#pragma once

#include "Core/Screen.h"
#include <SFML/Graphics.hpp>
#include "common.h"

namespace SFMLImpl {
    class SHARED_EXPORT SFMLScreen : public Core::Screen {
    public:
        sf::Texture m_texture;
        std::array<uint8_t, 4 * 64 * 32> m_framebuffer = {};

        SFMLScreen();
        void ClearScreen() override;
        void UpdateScreen() override;
        bool GetPixel(uint8_t x, uint8_t y) override;
        void SetPixel(uint8_t x, uint8_t y, bool pixel) override;
    };
}




