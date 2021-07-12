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

    ImGui::End();
}

void SFMLImpl::DebugCPU::PauseResumeButton() {
    if (m_executionState == CPUExecutionState::PAUSED) {
        ImGui::Text("Emulator paused");
        if (ImGui::Button("Resume")) {
            m_executionState = CPUExecutionState::RUNNING;
        }
    } else {
        ImGui::Text("Emulator running");
        if (ImGui::Button("Pause")) {
            m_executionState = CPUExecutionState::PAUSED;
        }
    }
}
