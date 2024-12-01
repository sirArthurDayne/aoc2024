#include <fmt/core.h>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <list>
#include <cmath>
#include <map>

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
    FileData data = ReadFromFile("samples/one.txt");

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

    //PART 1
    /*
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
    */


    //PART 2
    int total = 0;
    std::map<int,int> resultsMap;//key:left list element,value: key * n times on right list

    auto leftIT = left.begin();

    while (leftIT != left.end()) {
        int left_value = *leftIT;
        int amount_times = 0;
        //checks if key exists on map
        if (!resultsMap.contains(left_value)) {
            // if not, calculate amount from rightList and add to resultmap
            auto rightIT = right.begin();
            while (rightIT != right.end()) {
                int right_value = *rightIT;
                if (right_value == left_value) {
                    amount_times++;
                }
                ++rightIT;
            }
            int c = left_value * amount_times;
            resultsMap[left_value] = c; //add to map
            total += c;
        } else {
            // if does, return total from map and iterate
            total += resultsMap[left_value];
        }
        ++leftIT;
    }

    fmt::print("\n\t total {}\n", total);
    return 0;
}
