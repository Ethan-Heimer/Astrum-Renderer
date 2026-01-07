#include "file_watcher.h"
#include <filesystem>

#include <iostream>

using namespace std;

void Utils::FileWatcher::WatchFile(const string& filePath, function<void()> onFileTouched){

    //get current time stamp
    string fullFileName = std::filesystem::current_path()/filePath;
    filesystem::file_time_type timestamp = filesystem::last_write_time(fullFileName);

    timeStamps[fullFileName] = timestamp;
    callbacks[fullFileName] = onFileTouched;
}

void Utils::FileWatcher::CheckFiles(){
    for(auto& pair : timeStamps){
        string fileName = pair.first; 
        filesystem::file_time_type oldTimestamp = pair.second;
        filesystem::file_time_type timestamp = oldTimestamp;

        if(filesystem::exists(fileName))
            timestamp = filesystem::last_write_time(fileName);

        if(oldTimestamp != timestamp){
            timeStamps[fileName] = timestamp;
            callbacks[fileName]();
        }
        
    }
}

