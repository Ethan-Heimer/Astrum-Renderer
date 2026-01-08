#include "console/console.h"

#include <ctime>
#include <iostream>
#include <sstream>

bool Core::Console::showWarnings = true;

void Core::Console::ShowWarnings(bool show){
    showWarnings = show;
}

void Core::Console::Log(Core::MessageType messageType, const std::string& message){
    std::stringstream headerStream;

    std::time_t currentTime = std::time(nullptr);
    auto localTime = localtime(&currentTime);

    int hours = localTime->tm_hour;
    int min = localTime->tm_min;
    int sec = localTime->tm_sec;

    switch(messageType){
        case MessageType::Message:
            headerStream << hours << ":" << min << ":" << sec;
        break;
        
        case MessageType::Warning:
            headerStream << "Warning @ ";
            headerStream << hours << ":" << min << ":" << sec;
        break;

        case MessageType::Error:
            headerStream << "Error @ ";
            headerStream << hours << ":" << min << ":" << sec;
        break;
    }
    
    Log(messageType, headerStream.str(), message);
}

void Core::Console::Log(Core::MessageType messageType, const std::string& header, 
    const std::string& message){

    Colors headerColor = Colors::White;
    if(messageType == Warning)
        headerColor = Colors::Yellow;
    else if(messageType == Error)
        headerColor = Colors::Red;

    Log(messageType, header, headerColor, message);
}

void Core::Console::Log(Core::MessageType messageType, const std::string& header, 
        Colors headerColor, const std::string& message){

    Log(messageType, header, headerColor, message, Colors::White);
}

void Core::Console::Log(Core::MessageType messageType, const std::string& header, 
        Colors headerColor, const std::string& message, Colors messageColor){

        if(!showWarnings && messageType == MessageType::Warning)
            return;
        
        std::stringstream headerStream;
        headerStream << "\e[1;3" << (int)headerColor << "m";
        headerStream << "[" << header << "] " << "\e[0m";

        std::stringstream messageStream;
        messageStream << "\e[3" << (int)messageColor << "m";
        messageStream << message << "\e[0m";
    
        if(messageType == MessageType::Error)
            std::cerr << headerStream.str().c_str() << messageStream.str().c_str() << std::endl;
        else
            std::cout << headerStream.str().c_str() << messageStream.str().c_str() << std::endl;
}
