#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include "application.h"
namespace Core{
    class ApplicationLayer{
        public:
            ApplicationLayer(Application* application) : application(application){}
        protected:
            Application* application;
    };
}

#endif
