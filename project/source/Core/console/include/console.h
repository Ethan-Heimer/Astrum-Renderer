#ifndef ERRORS_H
#define ERRORS_H

#include <string>
namespace Core{
    enum Colors{
        Black = 0,
        Red = 1,
        Green = 2,
        Yellow = 3,
        Blue = 4, 
        Purple = 5, 
        Cyan = 6,
        White = 7
    };

    enum MessageType{
        Message,
        Warning,
        Error
    };

    class Console{
        public:
            static void Log(MessageType messageType, const std::string& message);

            static void Log(MessageType messageType, const std::string& header, 
                    const std::string& message);

            static void Log(MessageType messageType, const std::string& header, 
                    Colors headerColor, const std::string& message);

            static void Log(MessageType messageType, const std::string& header, 
                    Colors headerColor, const std::string& message, Colors messageColor);

            static void ShowWarnings(bool show);

        private:
            static bool showWarnings;
    };
}

#endif
