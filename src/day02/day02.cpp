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
                //fmt::print("a:{}, b:{}, diff:{}\n",a,b, difference);
                if ( difference < 1 || difference > 3) {
                    //fmt::print("UNSAFE\n");
                    return false;
                } 
            }
        return true;
    }

    bool isSafe(std::vector<std::string> report) {
        if (isMonotonic(report) && isDiffInRange(report) ) return true;
        return false;
    }

    bool isSafeWithDampener(std::vector<std::string>& report) {
            for (int i = 0; i < report.size(); i++) {
                std::vector<std::string> modreport = report;
                 modreport.erase(modreport.begin() + i);
                if(isSafe(modreport)) {
                    return true;
                }
            }   
        return false;
    }

    void SolvePart1() {
        
        FileData data = ReadFromFile("samples/two_sample.txt");
        if (!data.words.empty()) {
            /*fmt::print("total reports: {}\n",data.words.size());*/
            int safe_count = 0;
            for (int n = 0; n < data.words.size(); n++) {
                //checking monotonic and diff is range
                if (isSafe(data.words[n])) {
                    //fmt::print("report {} is Monotonic and diff is range\n", n);
                    safe_count++;
                }
            }
            fmt::print("\t P1-total SAFE reports:{} \n", safe_count);
        }
    }

    void SolvePart2() {
        FileData data = ReadFromFile("samples/two_sample.txt");
        if (!data.words.empty()) {
            /*fmt::print("total reports: {}\n",data.words.size());*/
            int safe_count = 0;
            for (int n = 0; n < data.words.size(); n++) {
                if (isSafe(data.words[n])) {
                    safe_count++;
                    continue;
                }
                //check removing level for safe
                if (isSafeWithDampener(data.words[n])) {
                    //fmt::print("report {} is safe with damper\n", n);
                    safe_count++;
                }
            }
            fmt::print("\t P2-total SAFE reports:{} \n", safe_count);
        }
    }

}
