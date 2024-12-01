#include <fmt/core.h>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <list>
#include <cmath>

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



int main() {
    fmt::print("AOC2024 - Problema 1 part 1\n");
    FileData data = ReadFromFile("samples/one_sample.txt");

    fmt::print("load right and left list\n");
    std::list<int> right;
    std::list<int> left;

    if (!data.words.empty()) {
        for (int i = 0; i < data.words.size(); i++) {
            /*fmt::print("palabras en linea {}\n", i);*/
            bool load_left = true;
            for (const auto& word : data.words[i]) {
                //load right and left list
                if (load_left) {
                    /*fmt::print("line {} - inserting in left list: {}\n",i, word);*/
                    left.push_back(std::stoi(word));
                } else {
                    /*fmt::print("line {} - inserting in right list: {}\n",i, word);*/
                    right.push_back(std::stoi(word));
                }
                load_left = !load_left;
            }
        }
    }

    //sort before calculating the distances
    left.sort();
    right.sort();
    //calculate distances
    int total = 0;
    auto leftIT = left.begin();
    auto rightIT = right.begin();
    while (leftIT != left.end() && rightIT != right.end()) {
        int distance = *leftIT - *rightIT;
        total += std::abs(distance);
        ++leftIT;
        ++rightIT;
    }
    fmt::print("\t total distance = {}\n", total);

    return 0;
}
