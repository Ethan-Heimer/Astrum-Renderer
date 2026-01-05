#ifndef UTILS_APP_LAYER_H
#define UTILS_APP_LAYER_H

#include "application.h"
#include "application_layer.h"
#include "input.h"

namespace Core{
    class UtilsApplicationLayer : ApplicationLayer{
        public:
            UtilsApplicationLayer(Application* application);
        private:
            Utils::Input inputManager;
    };
}

#endif
