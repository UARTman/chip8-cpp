#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include "Implementation/DebugCPU.h"
#include "Implementation/SFMLScreen.h"


#include <vector>
#include <fstream>
#include <chrono>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "CHIP8 Emulator");
    ImGui::SFML::Init(window);

//    std::ifstream ifs("pong.ch8", std::ios::binary|std::ios::ate);
//    std::ifstream::pos_type pos = ifs.tellg();
//
//    std::vector<char>  result(pos);
//    ifs.seekg(0, std::ios::beg);
//    ifs.read(&result[0], pos);
//    std::cout << result.size() << "\n";

    std::vector<uint8_t> result = {
            0x60, 0x00, 0x61, 0x00, 0xA2, 0x22, 0xC2, 0x01, 0x32, 0x01, 0xA2, 0x1E, 0xD0, 0x14, 0x70, 0x04, 0x30,
            0x40, 0x12, 0x04, 0x60, 0x00, 0x71, 0x04, 0x31, 0x20, 0x12, 0x04, 0x12, 0x1C, 0x80, 0x40, 0x20, 0x10,
            0x20, 0x40, 0x80, 0x10};

    SFMLImpl::SFMLScreen screen;
    SFMLImpl::DebugCPU CPU(screen);
    CPU.LoadRom(result);

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
    }


    return 0;
}
