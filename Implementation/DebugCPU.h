#pragma once
#include "Core/CPU.h"
#include "SFMLScreen.h"
#include "common.h"
#include <unordered_map>

namespace SFMLImpl {
    class SHARED_EXPORT DebugCPU: public Core::CPU {
    public:
        explicit DebugCPU( SFMLImpl::SFMLScreen &mSFMLScreen);
        void HandleEvent(sf::Event &event);
        void Debug();
        /* CHIP8:      PC:
          * 1 2 3 C     1 2 3 4
          * 4 5 6 D     Q W E R
          * 7 8 9 E     A S D F
          * A 0 B F     Z X C V
          */
        std::unordered_map<sf::Keyboard::Key, uint8_t> m_keymap = {
                {sf::Keyboard::Num1, 1}, {sf::Keyboard::Num2, 2},
                {sf::Keyboard::Num3, 3}, {sf::Keyboard::Num4, 0xC},
                {sf::Keyboard::Q, 4},    {sf::Keyboard::W, 5},
                {sf::Keyboard::E, 6},    {sf::Keyboard::R, 0xD},
                {sf::Keyboard::A, 7},    {sf::Keyboard::S, 8},
                {sf::Keyboard::D, 9},    {sf::Keyboard::F, 0xE},
                {sf::Keyboard::Z, 0xA},  {sf::Keyboard::X, 0},
                {sf::Keyboard::C, 0xB},  {sf::Keyboard::V, 0xF},
        };

    private:
        void PauseResumeButton();
        void KeyboardButton(uint8_t key);
    };
}


