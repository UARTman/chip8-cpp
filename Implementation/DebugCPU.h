#pragma once
#include "Core/CPU.h"
#include "SFMLScreen.h"
namespace SFMLImpl {
    class DebugCPU: public Core::CPU {
    public:
        explicit DebugCPU( SFMLImpl::SFMLScreen &mSFMLScreen);
        void Debug();

    private:
        void PauseResumeButton();
    };
}


