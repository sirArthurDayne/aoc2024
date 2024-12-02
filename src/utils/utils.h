#pragma once

#include <string>
#include <vector>

namespace Utils {
        struct FileData {
            std::vector<std::string> lines;
            std::vector<std::vector<std::string>> words;
        };

    FileData ReadFromFile(const std::string& filename);
}
