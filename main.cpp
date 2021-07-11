#include <iostream>
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include <imgui-SFML.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "CHIP8 Emulator");
    ImGui::SFML::Init(window);

    window.resetGLStates();
    sf::Clock delta_clock;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            // Event handling here

            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, delta_clock.restart());
        // ImGui stuff here

        ImGui::Begin("Window");


        ImGui::End();
        window.clear();
        // Custom draw here

        ImGui::SFML::Render(window);
        window.display();

    }


    return 0;
}
