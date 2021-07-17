#pragma once

#include <random>
#include "common.h"
#include "Screen.h"
#include "chrono"
enum class CPUExecutionState {
    PAUSED,
    RUNNING
};
namespace Core {
    class CPU {
    public:
        std::array<uint8_t, 16> m_registers{};
        std::array<uint8_t, 4096> m_memory{};
        uint16_t m_programCounter = 0;
        uint16_t m_registerI = 0;
        Screen &m_screen;
        uint8_t m_delayTimer = 0;
        uint8_t m_soundTimer = 0;

        std::chrono::steady_clock::time_point m_cycle_begin = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point m_cycle_end = std::chrono::steady_clock::now();

        CPUExecutionState m_executionState = CPUExecutionState::PAUSED;

        void Reset();
        void LoadRom(std::vector<char> &t_rom);
        void LoadRom(std::vector<uint8_t> &t_rom);
        void SingleStep();
        void Tick();

        explicit CPU(Screen &mScreen) : m_screen(mScreen) {
            Reset();
        }
    protected:
        std::random_device m_rd;
        std::uniform_int_distribution<int> m_dist = std::uniform_int_distribution<int>(0,255);
        std::array<uint16_t, 16> m_stack{};
        uint16_t m_stackPointer = 0;

        void StackPush(uint16_t t_val);
        uint16_t StackPop();
        uint16_t FetchNextInstruction();
        void ExecuteInstruction(uint16_t t_instruction);
        void UpdateTimers();
        void SetupSprites();

    };

    class CPUException : public std::exception {

    };
}
