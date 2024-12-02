#include "day02.h"
#include "utils.h"

#include <fmt/core.h>

using namespace Utils;
namespace Day02 {

    void SolvePart1() {
        
        FileData data = ReadFromFile("samples/two_sample.txt");
        if (!data.words.empty()) {
            fmt::print("not empty word list");
        }
    }

    void SolvePart2() {
        //fmt::print("problema 2 parte 2\n");
        //FileData data = ReadFromFile("samples/two_sample.txt");
    }

}
