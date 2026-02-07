#include "core_exeptions.h"
#include <stdexcept>
#include <string>

using namespace Core;
using namespace Exeptions;
using namespace std;

ResourceNotFound::ResourceNotFound(const string& typeName) 
    : runtime_error("Resource " + typeName + " Is Not Regestered To The Application."){}


LuaPointerArgNotProvided::LuaPointerArgNotProvided(const string& functionName, const string& referenceTypeName)
    : runtime_error("Lua Function Named \"" 
    + functionName + "\"Expects a reference argument of type" +
    referenceTypeName + "."){}
