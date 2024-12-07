#include "day03.h"
#include "utils.h"

#include <fmt/core.h>
#include <regex>

using namespace Utils;

namespace Day03 {

    int SumValidPatterns(std::string& instruction) {
        int counter =0;
        const std::regex mult_pattern(R"(mul\(\s*(\d{1,3})\s*,\s*(\d{1,3})\s*\))");
        auto matches_begin = std::sregex_iterator(instruction.begin(), instruction.end(), mult_pattern);
        auto matches_end = std::sregex_iterator();

        for (auto it = matches_begin; it != matches_end; ++it) {
            const std::smatch& match = *it;
            //fmt::print("[PATTERNFOUND] - match0:{}, match1:{}, match2:{}\n", match[0].str(), match[1].str(), match[2].str());
            int x = std::stoi(match[1].str());
            int y = std::stoi(match[2].str());
            counter += x * y;
        }
        return counter;
    }
    
    void SolvePart1() {
            FileData data = ReadFromFile("samples/three_sample.txt");
            if (!data.lines.empty()) {
                fmt::print("lineas encontradas: {}\n",data.lines.size());
                int total = 0;
                for (int i = 0; i < data.lines.size(); ++i) {
                    total += SumValidPatterns(data.lines[i]);
                }
            fmt::print("TOTAL = {}\n", total);
            }
        }
    
    int SumValidPatterns2(std::string& instruction) {
        return 0;
    }

    void SolvePart2() {
            FileData data = ReadFromFile("samples/three_sample2.txt");
            if (!data.lines.empty()) {
                fmt::print("lineas encontradas: {}\n",data.lines.size());
                int total = 0;
                for (int i = 0; i < data.lines.size(); ++i) {
                    total += SumValidPatterns2(data.lines[i]);
                }
            fmt::print("TOTAL = {}\n", total);
            }
    }
}
