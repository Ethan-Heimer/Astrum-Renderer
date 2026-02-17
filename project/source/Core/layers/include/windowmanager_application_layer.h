#pragma once

#include "application_layer.h"
#include "window_manager.h"

namespace Core{
    class WindowManagerApplicationLayer : public ApplicationLayer{
        public:
            WindowManagerApplicationLayer(Application* application);

        private:
            WindowManager windowManager;
    };
}
