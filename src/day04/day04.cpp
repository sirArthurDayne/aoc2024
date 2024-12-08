#include "day04.h"
#include "utils.h"

#include <fmt/core.h>

using namespace Utils;

namespace Day04 {
    void SolvePart1() {
        FileData data = ReadFromFile("samples/four.txt");
        if (!data.lines.empty()) {
            const int W = data.lines[0].size();
            const int C = data.lines.size();
            int countXMAS = 0;
            //fmt::print("board-dimensions: W:{} C:{}\n", W,C);
            for (int w = 0; w < W; w++) {
                for (int c = 0; c < C; c++) {
                    if (data.lines[w][c] == 'X') {
                        //check left-to-right
                        if (c < C  - 3) { 
                            if (data.lines[w][c+1] == 'M' && data.lines[w][c+2] == 'A' && data.lines[w][c+3] == 'S') {
                                fmt::print("found left-to-right XMAS\n"); countXMAS++;
                            }
                        }
                        //check right-to-left
                        if (c > 2) {
                            if (data.lines[w][c-1] == 'M' && data.lines[w][c-2] == 'A' && data.lines[w][c-3] == 'S') {
                                fmt::print("found right-to-left XMAS\n"); countXMAS++;
                            }
                        }
                        //check top-to-bottom
                        if (w < W - 3) {
                            if (data.lines[w+1][c] == 'M' && data.lines[w+2][c] == 'A' && data.lines[w+3][c] == 'S') {
                                fmt::print("found top-to-bottom XMAS\n"); countXMAS++;
                            }
                        }
                        //check bottom-to-top
                        if (w > 2) {
                            if (data.lines[w-1][c] == 'M' && data.lines[w-2][c] == 'A' && data.lines[w-3][c] == 'S') {
                                fmt::print("found bottom-to-top XMAS\n"); countXMAS++;
                            }
                        }
                        //check north to east 
                        if (w > 2 && c < C - 3) {
                            if (data.lines[w-1][c+1] == 'M' && data.lines[w-2][c+2] == 'A' && data.lines[w-3][c+3] == 'S') {
                                fmt::print("found north-to-east XMAS\n"); countXMAS++;
                            }
                        }
                        //check north to west
                        if (w > 2 && c > 2) {
                            if (data.lines[w-1][c-1] == 'M' && data.lines[w-2][c-2] == 'A' && data.lines[w-3][c-3] == 'S') {
                                fmt::print("found north-to-west XMAS\n"); countXMAS++;
                            }
                        }
                        //check south to east
                        if (w < W -3 && c < C -3) {
                            if (data.lines[w+1][c+1] == 'M' && data.lines[w+2][c+2] == 'A' && data.lines[w+3][c+3] == 'S') {
                                fmt::print("found south-to-east XMAS\n"); countXMAS++;
                            }
                        }
                        //check south to west
                        if (w < W -3 && c > 2) {
                            if (data.lines[w+1][c-1] == 'M' && data.lines[w+2][c-2] == 'A' && data.lines[w+3][c-3] == 'S') {
                                fmt::print("found south-to-west XMAS\n"); countXMAS++;
                            }
                        }
                    }
                }
            }
            fmt::print("XMAS:{}", countXMAS);
        }
    }
    void SolvePart2() {
        FileData data = ReadFromFile("samples/four.txt");
        if (!data.lines.empty()) {
            const int W = data.lines[0].size();
            const int C = data.lines.size();
            int countXMAS = 0;
            fmt::print("board-dimensions: W:{} C:{}\n", W,C);
            for (int w = 0; w < W; w++) {
                for (int c = 0; c < C; c++) {
                    if (data.lines[w][c] == 'A') {
                        if (w > 0 && c > 0 && w < W-1  && c < C-1){//check boundaries

                            //check both forwards
                            if (data.lines[w-1][c-1] == 'M' && data.lines[w+1][c+1] == 'S' && data.lines[w+1][c-1] == 'M' && data.lines[w-1][c+1] == 'S') {
                                fmt::print("found both forwads\n");
                                countXMAS++;
                            }
                            //check both backwards
                            if (data.lines[w-1][c-1] == 'S' && data.lines[w+1][c+1] == 'M' && data.lines[w+1][c-1] == 'S' && data.lines[w-1][c+1] == 'M') {
                                fmt::print("found both backwards\n");
                                countXMAS++;
                            }
                            //check first forwad second backwards
                            if (data.lines[w-1][c-1] == 'M' && data.lines[w+1][c+1] == 'S' && data.lines[w+1][c-1] == 'S' && data.lines[w-1][c+1] == 'M') {
                                fmt::print("found first forwad second backwards\n");
                                countXMAS++;
                            }
                            //check first backwards second forward
                            if (data.lines[w-1][c-1] == 'S' && data.lines[w+1][c+1] == 'M' && data.lines[w+1][c-1] == 'M' && data.lines[w-1][c+1] == 'S') {
                                fmt::print("found first backwards second backwards\n");
                                countXMAS++;
                            }
                        }
                    }
                }
            }
            fmt::print("MAS:{}", countXMAS);
        }
    }
}
