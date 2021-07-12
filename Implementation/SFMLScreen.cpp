#include "SFMLScreen.h"

SFMLImpl::SFMLScreen::SFMLScreen() {
    m_texture.create(64, 32);
    m_framebuffer.fill(0);
    UpdateTexture();
}

bool SFMLImpl::SFMLScreen::DrawPixelUnchecked(uint8_t x, uint8_t y, bool nibble) {
    bool pixel = GetPixel(x, y);
    bool newPix = pixel ^ nibble;
    bool ret = pixel & nibble;
    SetPixel(x, y, newPix);

    return ret;
}

void SFMLImpl::SFMLScreen::UpdateTexture() {
    m_texture.update(m_framebuffer.data());
}

void SFMLImpl::SFMLScreen::ClearScreen() {
    m_framebuffer.fill(0);
    UpdateTexture();
}

bool SFMLImpl::SFMLScreen::GetPixel(uint8_t x, uint8_t y) {
    return m_framebuffer[y * 64 * 4 + x * 4];
}

void SFMLImpl::SFMLScreen::SetPixel(uint8_t x, uint8_t y, bool pixel) {
    uint8_t color = 0;
    if (pixel) {
        color = 255;
    }
    m_framebuffer[y * 64 * 4 + x * 4] = color;
    m_framebuffer[y * 64 * 4 + x * 4 + 1] = color;
    m_framebuffer[y * 64 * 4 + x * 4 + 2] = color;
    m_framebuffer[y * 64 * 4 + x * 4 + 3] = color;
}

bool SFMLImpl::SFMLScreen::DrawSprite(uint8_t x, uint8_t y, uint8_t *sprite, uint8_t size) {
    bool ret = Screen::DrawSprite(x, y, sprite, size);
    UpdateTexture();
    return ret;
}
