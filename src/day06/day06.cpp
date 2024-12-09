#include "day06.h"
#include "utils.h"

#include <fmt/core.h>
#include <thread> // For sleep_for
#include <chrono> // For duration
#include <utility>
#include <unordered_set>


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
        Dir direction = TOP;
        int numSteps = 0;
        Dir Rotate90Degress(Dir dir) {
            //rotate 90 degres to the right (CW order)
            return static_cast<Dir>( (dir+1)%4);
        }
    };

    bool isOutOfBounds(int newX, int newY, int limitW, int limitC) {
        return newX < 0 || newY < 0 || newX >= limitW || newY >= limitC;
        //fmt::print("[OUT OF BOUNDS]  lastX:{}, lastY:{}\n", x, y);
    }
    void UpdatePosition(int& newX, int& newY, int x, int y, Dir direction) {
                if (direction == TOP) {
                    newX = x - 1;
                    newY = y;
                }
                else if (direction == RIGHT) {
                    newX = x;
                    newY = y + 1;
                }
                else if (direction == BOTTOM) {
                    newX = x + 1;
                    newY = y;
                }
                else if (direction == LEFT) {
                    newX = x;
                    newY = y - 1;
                }
    }

    Soldier FindSoldierOnMap(std::vector<std::string>& map, char target) {
        for (int w = 0; w < map[0].size(); ++w) {
            for (int c = 0; c < map.size(); ++c) {
                if (map[w][c] == target) {
                    fmt::print("soldier found! w:{},c:{}\n", w,c);
                    /*map[w][c] = 'X';*/
                    return {w,c};
                }
            }
        }
        fmt::print("[ERROR] - soldier not found on map\n");
        return {-1,-1};
    }

    void PrintMap(const std::vector<std::string>& map) {
        int limitW = static_cast<int>(map[0].size());
        int limitC = static_cast<int>(map.size());
        for (int w = 0; w < limitW; ++w) {
            for (int c = 0; c < limitC; ++c) {
                fmt::print("{}", map[w][c]);
            }
            fmt::print("\n");
        }
    }
    std::vector<std::pair<int,int>> soldierVisitedPositions;
    void SolvePart1() {
        fmt::print("part1\n");
        FileData data = ReadFromFile("samples/six.txt");
        if (!data.lines.empty()) {
            fmt::print("w:{},c:{}\n", data.lines.size(), data.lines[0].size());
            Soldier soldier = FindSoldierOnMap(data.lines, '^');
            data.lines[soldier.x][soldier.y] = 'X';
            soldierVisitedPositions.push_back(std::make_pair(soldier.x, soldier.y));
            int totalX = 1;//soldier found
            int limitW = static_cast<int>(data.lines[0].size());
            int limitC = static_cast<int>(data.lines.size());
            Dir dir = TOP;
            //keep moving until your scape the map, rotate when obstacle its found
            while (true) {
                //update position
                int soldierNewX, soldierNewY;
                UpdatePosition(soldierNewX, soldierNewY, soldier.x, soldier.y, dir);
            
                //check for boundaries
                if (isOutOfBounds(soldierNewX, soldierNewY, limitW, limitC)) {
                    break;
                }

                //if '.' found update map and add counter
                if (data.lines[soldierNewX][soldierNewY] == '.') {
                    data.lines[soldierNewX][soldierNewY] = 'X';
                    soldier.x = soldierNewX;
                    soldier.y = soldierNewY;
                    totalX++;
                    soldierVisitedPositions.push_back(std::make_pair(soldier.x, soldier.y));
                }
                //if '#' found change direction
                else if (data.lines[soldierNewX][soldierNewY] == '#') {
                    dir = soldier.Rotate90Degress(dir);
                }
                //move to allready visited cell
                else if (data.lines[soldierNewX][soldierNewY] == 'X') {
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


    bool isLoops(std::vector<std::string>& map, int startX, int startY, Dir startDir) {
            std::unordered_set<std::string> visited;
            int x = startX;
            int y = startY;
            Dir dir = startDir;
            Soldier soldier;
        
            while (true) {
                std::string pos = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(dir);
                //fmt::print("{}\n",pos);
                 if (visited.find(pos) != visited.end()) {
                    return true; // Guard is in a loop
                }
                visited.insert(pos);
                //update position
                int newX, newY;
                UpdatePosition(newX, newY, x, y, dir);
                //check for boundaries
                if (isOutOfBounds(newX, newY, (int)map[0].size(), (int)map.size())) {
                    return false;
                }
                //if '#' found change direction
                if (map[newX][newY] == '#') {
                    dir = soldier.Rotate90Degress(dir);
                }   
                else {
                    x = newX;
                    y = newY;
                }
            
                //show map for debugging
                //PrintMap(data.lines);
                //printf("\r");
                //std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        
        return false;
    }

    void SolvePart2() {
        FileData data = ReadFromFile("samples/six.txt");
        if (!data.lines.empty()) {
            fmt::print("w:{},c:{}\n", data.lines.size(), data.lines[0].size());
            int validPos = 0;
            Soldier soldier = FindSoldierOnMap(data.lines, '^');
            int limitW = static_cast<int>(data.lines[0].size());
            int limitC = static_cast<int>(data.lines.size());
            for (int w = 0; w < limitW; ++w) {
                for(int c = 0; c < limitC; ++c) {
                    if (data.lines[w][c] != '.') continue;
                    char temp = data.lines[w][c];
                    data.lines[w][c] = '#';

                    if (isLoops(data.lines, soldier.x,soldier.y, TOP)) {
                        validPos++;
                    }
                    data.lines[w][c] = temp;

                }
            }
            //improvements version
            /*for (auto pos : soldierVisitedPositions) {*/
            /*    if (data.lines[pos.first][pos.second] != '.') continue;*/
            /*    char temp = data.lines[pos.first][pos.second];*/
            /*    data.lines[pos.first][pos.second] = '#';*/
            /*    if (isLoops(data.lines, pos.first,pos.second, TOP)) {*/
            /*        validPos++;*/
            /*    }*/
            /*    data.lines[pos.first][pos.second] = temp;*/
            /*}*/
            fmt::print("LOOP:{}\n", validPos);
        }
    }
}
