#include "core_exeptions.h"
#include <stdexcept>
#include <string>

using namespace Core;
using namespace Exeptions;
using namespace std;

ResourceNotFound::ResourceNotFound(const string& typeName) 
    : runtime_error("Resource " + typeName + " Is Not Regestered To The Application."){}
