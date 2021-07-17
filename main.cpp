#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <imgui-SFML.h>
#include "Implementation/DebugCPU.h"
#include "Implementation/SFMLScreen.h"


#include <vector>
#include <fstream>
#include <chrono>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "CHIP8 Emulator");
    ImGui::SFML::Init(window);

    sf::Sound beep;
    sf::SoundBuffer beepBuffer;

    std::vector<float> samples = {};
    for (int i = 0; i < 44100 * 0.4; ++i) {
        double x = std::sin(3.14 * 2 / 100);
        samples.push_back((float) x);
    }
    beepBuffer.loadFromSamples( (sf::Int16 *) (&samples[0]), samples.size(), 1, 44100);
    beep.setBuffer(beepBuffer);

    std::vector<uint8_t> rom  = {
            0x60, 0x00, 0x61, 0x00, 0xA2, 0x22, 0xC2, 0x01, 0x32, 0x01, 0xA2, 0x1E, 0xD0, 0x14, 0x70, 0x04, 0x30,
            0x40, 0x12, 0x04, 0x60, 0x00, 0x71, 0x04, 0x31, 0x20, 0x12, 0x04, 0x12, 0x1C, 0x80, 0x40, 0x20, 0x10,
            0x20, 0x40, 0x80, 0x10};

    SFMLImpl::SFMLScreen screen;
    SFMLImpl::DebugCPU CPU(screen);
    CPU.LoadRom(rom);

    sf::Sprite sprite(screen.m_texture);

    float ScaleX = (float) window.getSize().x / 64.0f;
    float ScaleY = (float) window.getSize().y / 32.0f;

    sprite.setScale(ScaleX, ScaleY);


    window.resetGLStates();
    sf::Clock delta_clock;


    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            // Event handling here
            CPU.HandleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, delta_clock.restart());
        // ImGui stuff here
        CPU.Debug();

        window.clear();
        window.draw(sprite);
        // Custom draw here

        ImGui::SFML::Render(window);
        window.display();
        CPU.Tick();
        if (CPU.m_soundTimer > 0 && beep.getStatus() != sf::SoundSource::Playing) {
            beep.play();
        }
    }

    return 0;
}
