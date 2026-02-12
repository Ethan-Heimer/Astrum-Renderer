#pragma once

namespace Renderer{
    class Screen{
        public:  
            Screen();
            ~Screen();

            void Delete();
            void Use();
            void Disable();

        private:
            unsigned int vao = 0;
            unsigned int vbo = 0;
    };
}
