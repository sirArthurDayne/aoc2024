#include "utils.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace Utils {
    FileData ReadFromFile(const std::string& filename) {
        FileData fileData;
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("[ERROR] readfromsamplefile - cannot open filename " + filename);
        }
        std::string line;
        while (std::getline(file, line)) {
            fileData.lines.push_back(line);
             // Dividir la línea en palabras
            std::istringstream iss(line);
            std::vector<std::string> lineWords;
            std::string word;
            while (iss >> word) {
                lineWords.push_back(word);
            }
            fileData.words.push_back(lineWords);
        }
        file.close();
        return fileData;
    }
}
