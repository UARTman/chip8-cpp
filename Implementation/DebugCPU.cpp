//
// Created by uartman on 12.07.2021.
//

#include <iostream>
#include "DebugCPU.h"
#include "imgui/imgui.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"

SFMLImpl::DebugCPU::DebugCPU(SFMLImpl::SFMLScreen &mSFMLScreen) : CPU(mSFMLScreen) {

}

void SFMLImpl::DebugCPU::Debug() {
    ImGui::Begin("Emulator debug window");
    PauseResumeButton();

    if (ImGui::Button("Load ROM file"))
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose ROM File", ".ch8,.bin", ".");

    // display
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
    {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

            std::ifstream ifs(filePathName, std::ios::binary|std::ios::ate);
            std::ifstream::pos_type pos = ifs.tellg();

            std::vector<char>  result(pos);
            ifs.seekg(0, std::ios::beg);
            ifs.read(&result[0], pos);
            LoadRom(result);
            // action
        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }

    ImGui::Text("Keyboard");

    KeyboardButton(1);
    ImGui::SameLine();
    KeyboardButton(2);
    ImGui::SameLine();
    KeyboardButton(3);
    ImGui::SameLine();
    KeyboardButton(0xC);

    KeyboardButton(4);
    ImGui::SameLine();
    KeyboardButton(5);
    ImGui::SameLine();
    KeyboardButton(6);
    ImGui::SameLine();
    KeyboardButton(0xD);

    KeyboardButton(7);
    ImGui::SameLine();
    KeyboardButton(8);
    ImGui::SameLine();
    KeyboardButton(9);
    ImGui::SameLine();
    KeyboardButton(0xE);

    KeyboardButton(0xA);
    ImGui::SameLine();
    KeyboardButton(0);
    ImGui::SameLine();
    KeyboardButton(0xB);
    ImGui::SameLine();
    KeyboardButton(0xF);

    ImGui::Text("ST: %d", m_soundTimer);

    ImGui::End();
}

void SFMLImpl::DebugCPU::PauseResumeButton() {
    if (m_executionState == CPUExecutionState::PAUSED) {
        ImGui::Text("Emulator paused");
        if (ImGui::Button("Resume")) {
            m_executionState = CPUExecutionState::RUNNING;
        }
    } else if (m_executionState == CPUExecutionState::RUNNING) {
        ImGui::Text("Emulator running");
        if (ImGui::Button("Pause")) {
            m_executionState = CPUExecutionState::PAUSED;
        }
    } else {
        ImGui::Text("Waiting for key press");
    }
}

void SFMLImpl::DebugCPU::HandleEvent(sf::Event &event) {
    if (m_executionState != CPUExecutionState::PAUSED) {
        if (event.type == sf::Event::KeyPressed) {
            if (m_keymap.find(event.key.code) != m_keymap.end()) {
                uint8_t code = m_keymap[event.key.code];
                OnKeyPressed(code);
                m_keyboard[code] = true;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (m_keymap.find(event.key.code) != m_keymap.end()) {
                uint8_t code = m_keymap[event.key.code];
                m_keyboard[code] = false;
            }
        }
    }
}

void SFMLImpl::DebugCPU::KeyboardButton(uint8_t key) {
    const char* labels[] =  {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    bool key_pressed = m_keyboard[key];
    if (key_pressed) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 0, 0, 255));
    }
    ImGui::Text("%s", labels[key]);
    if (key_pressed) {
        ImGui::PopStyleColor();
    }
}
