#include "CPU.h"

void Core::CPU::ExecuteInstruction(uint16_t t_instruction) {
    uint16_t opcode = t_instruction >> 12;
    uint16_t addr = t_instruction & 0x0FFF;
    uint8_t byte = t_instruction & 0x00FF;
    uint8_t x = (t_instruction & 0x0F00) >> 8;
    uint8_t y = (t_instruction & 0x00F0) >> 4;
    uint8_t n = (t_instruction & 0x000F);


    // CLS
    if (t_instruction == 0x00E0) {
        m_screen.ClearScreen();
    }
        // RET
    else if (t_instruction == 0x00EE) {
        m_programCounter = StackPop();
    }

    // JP addr
    if (opcode == 1) {
        m_programCounter = addr;
    }
    // CALL addr
    if (opcode == 2) {
        StackPush(m_programCounter);
        m_programCounter = addr;
    }
    // SE Vx, byte
    if (opcode == 3) {
        if (m_registers[x] == byte) {
            m_programCounter += 2;
        }
    }
    // SNE Vx, byte
    if (opcode == 4) {
        if (m_registers[x] != byte) {
            m_programCounter += 2;
        }
    }
    // SE Vx, Vy
    if (opcode == 5) {
        if (m_registers[x] == m_registers[y]) {
            m_programCounter += 2;
        }
    }
    // LD Vx, byte
    if (opcode == 6) {
        m_registers[x] = byte;
    }
    // ADD Vx, byte
    if (opcode == 7) {
        m_registers[x] += byte;
    }
    if (opcode == 8) {
        // LD Vx, Vy
        if (n == 0) {
            m_registers[x] = m_registers[y];
        }
        // OR Vx, Vy
        if (n == 1) {
            m_registers[x] = m_registers[x] | m_registers[y];
        }
        // AND Vx, Vy
        if (n == 2) {
            m_registers[x] = m_registers[x] & m_registers[y];
        }
        // XOR Vx, Vy
        if (n == 3) {
            m_registers[x] = m_registers[x] ^ m_registers[y];
        }
        // ADD Vx, Vy
        if (n == 4) {
            uint16_t result = m_registers[x] + m_registers[y];
            m_registers[15] = (uint8_t)(result > 255);
            m_registers[x] = (uint8_t)result;
        }
        // SUB Vx, Vy
        if (n == 5) {
            m_registers[15] = (uint8_t)(m_registers[x] > m_registers[y]);
            m_registers[x] = m_registers[x] - m_registers[y];
        }
        // SHR Vx
        if (n == 6) {
            m_registers[15] = m_registers[x] & 1;
            m_registers[x] = m_registers[x] >> 1;
        }
        //SUBN Vx, Vy
        if (n == 7) {
            m_registers[15] = (uint8_t)(m_registers[y] > m_registers[x]);
            m_registers[x] = m_registers[y] - m_registers[x];
        }
        // SHL Vx
        if (n == 0xE) {
            m_registers[15] = (m_registers[x] & 0b10000000) >> 7;
            m_registers[x] = m_registers[x] << 1;
        }
    }
    // SNE Vx, Vy
    if (opcode == 9) {
        if (m_registers[x] != m_registers[y]) {
            m_programCounter += 2;
        }
    }
    // LD I, addr
    if (opcode == 0xA) {
        m_registerI = addr;
    }
    // JP V0, addr
    if (opcode == 0xB) {
        m_programCounter = addr + m_registers[0];
    }
    // RND Vx, byte
    if (opcode == 0xC) {
        uint8_t rb = static_cast<char>(m_dist(m_rd));
        m_registers[x] = rb & byte;
    }
    // DRW Vx, Vy, nibble
    if (opcode == 0xD) {
        m_registers[15] = (uint8_t) m_screen.DrawSprite(m_registers[x], m_registers[y], &m_memory[m_registerI], n);
    }

    if (opcode == 0xE) {
        // SKP Vx
        if (byte == 0x9E) {
            // TODO: Keyboard
        }
        if (byte == 0xA1) {
            // TODO: Keyboard
        }
    }

    if (opcode == 0xF) {
        // LD Vx, DT
        if (byte == 0x07) {
            m_registers[x] = m_delayTimer;
        }
        // LD Vx, K
        if (byte == 0x0A) {
            // TODO: Keyboard
        }
        // LD DT, Vx
        if (byte == 0x15) {
            m_delayTimer = m_registers[x];
        }
        // LD ST, Vx
        if (byte == 0x18) {
            m_soundTimer = m_registers[x];
        }
        // ADD I, Vx
        if (byte == 0x1E) {
            m_registerI += m_registers[x];
        }
        // LD F, Vx
        if (byte == 0x29) {
            m_registerI = m_registers[x] * 5;
        }
        // LD B, Vx
        if (byte == 0x33) {
            uint8_t val = m_registers[x];
            m_memory[m_registerI] = val / 100;
            m_memory[m_registerI + 1] = (val / 10) % 10;
            m_memory[m_registerI + 2] = val % 10;
        }
        // LD [I], Vx
        if (byte == 0x55) {
            // TODO: Memory check
            for (int i = 0; i <= x; ++i) {
                m_memory[m_registerI + i] = m_registers[i];
            }
        }
        // LD Vx, [I]
        if (byte == 0x65) {
            // TODO: Memory check
            for (int i = 0; i <= x; ++i) {
                m_registers[i] = m_memory[m_registerI + i];
            }
        }
    }
}
