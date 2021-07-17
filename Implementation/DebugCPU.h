#pragma once
#include "Core/CPU.h"
#include "SFMLScreen.h"
#include "common.h"

namespace SFMLImpl {
    class SHARED_EXPORT DebugCPU: public Core::CPU {
    public:
        explicit DebugCPU( SFMLImpl::SFMLScreen &mSFMLScreen);
        void Debug();

    private:
        void PauseResumeButton();
    };
}


