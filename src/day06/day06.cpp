#include "day06.h"
#include "utils.h"

#include <fmt/core.h>
#include <thread> // For sleep_for
#include <chrono> // For duration
#include <stdio.h>


using namespace Utils;
namespace Day06 {

    enum Dir {
        TOP,//0
        RIGHT,//1
        BOTTOM,//2
        LEFT//3
    };
    struct Soldier {
        int x;
        int y;
        Dir Rotate90Degress(Dir dir) {
            //rotate 90 degres to the right (CW order)
            if (dir == TOP)  return RIGHT;
            else if (dir == RIGHT) return BOTTOM;
            else if (dir == BOTTOM) return LEFT;
            else if (dir == LEFT) return TOP;
        }
        bool isOutOfBounds(int newX, int newY, int limitW, int limitC) {
            if (newX < 0 || newY < 0 || newX >= limitW || newY >= limitC) {
                fmt::print("[OUT OF BOUNDS]  lastX:{}, lastY:{}\n", x, y);
                return true;
            }
            return false;
        }
    };

    Soldier FindSoldierOnMap(std::vector<std::string>& map, char target) {
        for (int w = 0; w < map[0].size(); ++w) {
            for (int c = 0; c < map.size(); ++c) {
                if (map[w][c] == target) {
                    fmt::print("soldier found! w:{},c:{}\n", w,c);
                    map[w][c] = 'X';
                    return {w,c};
                }
            }
        }
        fmt::print("[ERROR] - soldier not found on map\n");
        return {-1,-1};
    }

    void PrintMap(const std::vector<std::string>& map) {
        int limitW = map[0].size();
        int limitC = map.size();
        for (int w = 0; w < limitW; ++w) {
            for (int c = 0; c < limitC; ++c) {
                fmt::print("{}", map[w][c]);
            }
            fmt::print("\n");
        }
    }
    void SolvePart1() {
        fmt::print("part1\n");
        FileData data = ReadFromFile("samples/six.txt");
        if (!data.lines.empty()) {
            
            fmt::print("w:{},c:{}\n", data.lines.size(), data.lines[0].size());
            Soldier soldier = FindSoldierOnMap(data.lines, '^');
            int totalX = 1;//soldier found
            int limitW = data.lines[0].size();
            int limitC = data.lines.size();
            Dir dir = TOP;
            bool keep_moving = true;
            //keep moving until your scape the map, rotate when obstacle its found
            while (keep_moving) {
                //clear screen on old frame
                int soldierNewX, soldierNewY;
                
                //check for obstacle
                if (dir == TOP) {
                    soldierNewX = soldier.x - 1;
                    soldierNewY = soldier.y;
                }
                else if (dir == RIGHT) {
                    soldierNewX = soldier.x;
                    soldierNewY = soldier.y + 1;
                }
                else if (dir == BOTTOM) {
                    soldierNewX = soldier.x + 1;
                    soldierNewY = soldier.y;
                }
                else if (dir == LEFT) {
                    soldierNewX = soldier.x;
                    soldierNewY = soldier.y - 1;
                }
                if (soldier.isOutOfBounds(soldierNewX, soldierNewY, limitW, limitC)) {
                    keep_moving = false;
                    break;
                }
                //if '.' found update map and add counter
                if (data.lines[soldierNewX][soldierNewY] == '.') {
                    data.lines[soldierNewX][soldierNewY] = 'X';
                    soldier.x = soldierNewX;
                    soldier.y = soldierNewY;
                    totalX++;
                }
                //if '#' found change direction
                else if (data.lines[soldierNewX][soldierNewY] == '#') {
                    dir = soldier.Rotate90Degress(dir);
                }
                else if (data.lines[soldierNewX][soldierNewY] == 'X') {
                    //update position
                    soldier.x = soldierNewX;
                    soldier.y = soldierNewY;
                }
                //show map for debugging
                //PrintMap(data.lines);
                //printf("\r");
                //std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            fmt::print("\n\tTOTALX:{}\n",totalX);
        }
    }
    void SolvePart2() {
        /*fmt::print("part2\n");*/
    }
}
