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
            FileData data = ReadFromFile("samples/three.txt");
            if (!data.lines.empty()) {
                fmt::print("lineas encontradas: {}\n",data.lines.size());
                int total = 0;
                for (int i = 0; i < data.lines.size(); ++i) {
                    total += SumValidPatterns(data.lines[i]);
                }
            fmt::print("TOTAL = {}\n", total);
            }
        }

    static bool canMult = true;//keep tracking instruction for every line
    
    int SumValidPatterns2(std::string& instruction) {
        int counter = 0;

        const std::regex mult_pattern(R"(mul\(\s*(\d{1,3})\s*,\s*(\d{1,3})\s*\))");
        const std::regex doPattern(R"(do\(\))");
        const std::regex dontPattern(R"(don't\(\))");
        const std::regex allpattern(R"(mul\(\s*(\d{1,3})\s*,\s*(\d{1,3})\s*\)|do\(\)|don't\(\))");

        auto matches_begin = std::sregex_iterator(instruction.begin(), instruction.end(), allpattern);
        auto matches_end = std::sregex_iterator();

        for (auto it = matches_begin; it != matches_end; ++it) {
            const std::smatch& match = *it;
            //do() operator found
            if (std::regex_match(match.str(), doPattern)) {
                //fmt::print("do() found, enabling Mult! {}\n", match.str());
                canMult = true;
            }
            //don't() operator found
            else if(std::regex_match(match.str(), dontPattern)) {
                //fmt::print("don't() found, disabling Mult! {}\n", match.str());
                canMult = false;
            }
            //mul(X,Y) operator found
            else if(std::regex_match(match.str(), mult_pattern) && canMult) {
               // fmt::print("mult(X,Y) found,  {}!\n", match.str());
                int x = std::stoi(match[1].str());
                int y = std::stoi(match[2].str());
                counter += x * y;
            }
        }

        return counter;
    }

    void SolvePart2() {
            FileData data = ReadFromFile("samples/three.txt");
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
