#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
//#include <list>
//#include <cmath>
//#include <map>

struct FileData {
    std::vector<std::string> lines;
    std::vector<std::vector<std::string>> words;
};

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
