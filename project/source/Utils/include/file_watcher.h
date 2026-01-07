#ifndef FILE_WATCHER_H
#define FILE_WATCHER_H

#include <functional>
#include <map>
#include <string>
#include <filesystem>

namespace Utils{
    class FileWatcher{
        public:
            void WatchFile(const std::string& filePath, std::function<void()> onFileTouched);

            void CheckFiles();


        private:
            std::map<std::string, std::filesystem::file_time_type> timeStamps;
            std::map<std::string, std::function<void()>> callbacks;
    };
}

#endif
