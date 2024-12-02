#include "day02.h"
#include "utils.h"

#include <fmt/core.h>

using namespace Utils;
namespace Day02 {
    bool isMonotonic(std::vector<std::string>& reports) {
            bool isIncreasing = true;
            bool isDecreasing = true;
            for (int i = 1; i < reports.size(); ++i) {
                int a = std::stoi(reports[i]);
                int b = std::stoi(reports[i-1]);
                if (a > b) { //increasing
                    isDecreasing = false;
                } else if (a < b) {//decreasing
                    isIncreasing = false;
                } else {
                    return false; //diff 0, is not monotonic
                }
            }
           if (!(isIncreasing || isDecreasing))
            return false;

        return true;
    }

    bool isDiffInRange(std::vector<std::string>& report) {
            for (int i = 0; i < report.size() -1; i++) {
                int a = std::stoi(report[i]);
                int b = std::stoi(report[i+1]);
                int difference = std::abs(b - a);
                fmt::print("a:{}, b:{}, diff:{}\n",a,b, difference);
                if ( difference < 1 || difference > 3) {
                    //fmt::print("UNSAFE\n");
                    return false;
                } 
            }
        return true;
    }

    void SolvePart1() {
        
        FileData data = ReadFromFile("samples/two.txt");
        if (!data.words.empty()) {
            fmt::print("total reports: {}\n",data.words.size());
            int safe_count = 0;
            for (int n = 0; n < data.words.size(); n++) {
                //checking monotonic and monotonic
                if (isMonotonic(data.words[n]) && isDiffInRange(data.words[n]) ) {
                    //fmt::print("report {} is Monotonic and diff is range\n", n);
                    safe_count++;
                }
            }
            fmt::print("\n\t total SAFE reports:{} \n", safe_count);
        }
    }

    void SolvePart2() {
        //fmt::print("problema 2 parte 2\n");
        //FileData data = ReadFromFile("samples/two_sample.txt");
    }

}
