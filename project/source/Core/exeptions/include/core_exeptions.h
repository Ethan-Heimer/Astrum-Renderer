#pragma once

#include <stdexcept>
using namespace std;

namespace Core{
    namespace Exeptions{
        class ResourceNotFound : public runtime_error{
            public:
                ResourceNotFound(const string& typeName);
        };
    }
}
