#include "CPU.h"

void Core::CPU::Reset() {
    m_registers.fill(0);
    m_memory.fill(0);
    m_stack.fill(0);
    SetupSprites();
    //TODO: Initialize alphabet
    m_programCounter = 0x200;
    m_stackPointer = 0;
    m_registerI = 0;
    m_soundTimer = 0;
    m_delayTimer = 0;
    m_executionState = CPUExecutionState::PAUSED;

    m_screen.ClearScreen();
}

void Core::CPU::LoadRom(std::vector<char> &t_rom) {
    Reset();
    for (int i = 0; i < t_rom.size(); ++i) {
        m_memory[0x200 + i] = t_rom[i];
    }
}


void Core::CPU::StackPush(uint16_t t_val) {
    if (m_stackPointer == 16) {
        throw CPUException();
    }
    m_stack[m_stackPointer] = t_val;
    m_stackPointer += 1;
}

uint16_t Core::CPU::StackPop() {
    if (m_stackPointer == 0) {
        throw CPUException();
    }
    m_stackPointer -= 1;
    return m_stack[m_stackPointer];
}

uint16_t Core::CPU::FetchNextInstruction() {
    if (m_programCounter > 4094) {
        throw CPUException();
    }
    uint16_t ret = (m_memory[m_programCounter] << 8) | m_memory[m_programCounter + 1];
    m_programCounter += 2;
    return ret;
}


void Core::CPU::SingleStep() {
    UpdateTimers();
    uint16_t instruction = FetchNextInstruction();
    ExecuteInstruction(instruction);
}

void Core::CPU::UpdateTimers() {
    if (m_soundTimer > 0) {
        m_soundTimer -= 1;
    }
    if (m_delayTimer > 0) {
        m_delayTimer -= 1;
    }
}

void Core::CPU::Tick() {
    if (m_executionState != CPUExecutionState::RUNNING) {
        return;
    }
    m_cycle_end = std::chrono::steady_clock::now();
    long x = std::chrono::duration_cast<std::chrono::microseconds>(m_cycle_end - m_cycle_begin).count();
    if (x > 1000) {
        SingleStep();
        m_cycle_begin = std::chrono::steady_clock::now();
    }
}

void Core::CPU::OnKeyPressed(uint8_t key) {
    if (m_executionState == CPUExecutionState::WAITING_FOR_KEYPRESS) {
        m_executionState = CPUExecutionState::RUNNING;
        m_registers[m_keyPressTargetRegister] = key;
    }
}

void Core::CPU::LoadRom(std::vector<uint8_t> &t_rom) {
    Reset();
    for (int i = 0; i < t_rom.size(); ++i) {
        m_memory[0x200 + i] = t_rom[i];
    }
}
