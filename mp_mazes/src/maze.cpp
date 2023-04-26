/* Your code here! */
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <queue>
#include "./cs225/PNG.h"
#include "dsets.h"
#include "maze.h"
#include <queue>
#include <utility>
#include <set>
using std::pair;
using std::vector;
using namespace cs225;

SquareMaze::SquareMaze() {

}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    int index = y * W + x;
    switch (dir) {
        case 0: // Right
            return !Maze[index].RWall;
        case 1: // Down
            return !Maze[index].DWall;
        case 2: // Left
            return x != 0 && !Maze[index - 1].RWall;
        case 3: // Up
            return y != 0 && !Maze[index - W].DWall;
        default:
            return false;
    }
}

PNG * SquareMaze::drawMaze() const {
    PNG * canvas = new PNG(10 * W + 1, 10 * H + 1);

    // Blacken topmost and leftmost, except entrance
    for (unsigned i = 10; i < 10 * W + 1; i++) {
        canvas->getPixel(i, 0).l = 0;
    }
    for (unsigned i = 0; i < 10 * H + 1; i++) {
        canvas->getPixel(0, i).l = 0;
    }

    // Draw walls
    for (unsigned i = 0; i < W; i++) {
        for (unsigned j = 0; j < H; j++) {
            for (unsigned k = 0; k <= 10; k++) {
                if (Maze[j * W + i].RWall) {
                    canvas->getPixel((i + 1) * 10, j * 10 + k).l = 0;
                }
                if (Maze[j * W + i].DWall) {
                    canvas->getPixel(i * 10 + k, (j + 1) * 10).l = 0;
                }
            }
        }
    }

    return canvas;
}

PNG * SquareMaze::drawMazeWithSolution() {
    PNG * res = drawMaze();
    vector<int> path = solveMaze();
    unsigned currX = 0;
    unsigned currY = 0;
    for (unsigned i = 0; i < path.size(); i++) {
        int dx = 0, dy = 0;
        if (path[i] == 0) {
            dx = 1;
        } else if (path[i] == 1) {
            dy = 1;
        } else if (path[i] == 2) {
            dx = -1;
        } else if (path[i] == 3) {
            dy = -1;
        }

        for (int j = 0; j <= 10; j++) {
            int x = currX * 10 + 5 + j * dx;
            int y = currY * 10 + 5 + j * dy;

            if (x >= 0 && y >= 0) {
                res->getPixel(x, y).s = 1;
                res->getPixel(x, y).l = 0.5;
            }
        }

        currX += dx;
        currY += dy;
    }
    // Mark finish line
    for (int i = 1; i < 10; i++) {
        res->getPixel(currX*10+i, (currY+1)*10).l = 1;
    }
    return res;
}

void SquareMaze::makeMaze(int width, int height) {
    //Clear the old maze if there is one.
    if (Maze.size() > 0) {
        Maze.clear();
    }

    //Initialize the maze with all walls.
    Maze = vector<Cell>(height*width, Cell());
    W = width;
    H = height;

    //Initialize a Disjoint Sets data structure to prevent cycle.
    DisjointSets dsets;
    dsets.addelements(H*W);
    
    vector<unsigned int> random_V(2 * H * W);
    // Populate the vector with values from 0 to (2 * H * W) - 1
    for (unsigned int i = 0; i < random_V.size(); ++i) {
        random_V[i] = i;
    }
    // Randomization
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2 * H * W - 1);
    // Shuffle the vector
    for (unsigned int i = 0; i < random_V.size(); ++i) {
        // Generate a random index
        unsigned int random_index = dist(gen);
        // Swap the current element with the element at the random index
        std::swap(random_V[i], random_V[random_index]);
    }

    //Remove walls under conditions
    for (unsigned i = 0; i < random_V.size(); i++) {
        unsigned cellIndex = random_V[i] / 2;
        unsigned direction = random_V[i] % 2;
        
        switch (direction) {
            case 0: // Right
                if ((cellIndex + 1) % W != 0) {
                    if (dsets.find(cellIndex) != dsets.find(cellIndex + 1)) {
                        Maze[cellIndex].RWall = 0;
                        dsets.setunion(cellIndex, cellIndex + 1);
                    }
                }
                break;
            case 1: // Down
                if (cellIndex + 1 <= (H - 1) * W) {
                    if (dsets.find(cellIndex) != dsets.find(cellIndex + W)) {
                        Maze[cellIndex].DWall = 0;
                        dsets.setunion(cellIndex, cellIndex + W);
                    }
                }
                break;
        }
    }
}


void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    dir == 0 ? Maze[x + y * W].RWall = exists : Maze[x + y * W].DWall = exists;
}

vector<int> SquareMaze::solveMaze() {
    std::queue<unsigned int> FRONT;
    vector<int> PARENTS(H*W, -1);
    PARENTS[0] = -2;
    FRONT.push(0);
    unsigned current;
    unsigned target;
    while (!FRONT.empty()) {
        current = FRONT.front();
        FRONT.pop();
        
        // Define the possible moves (right, down, left, up) and their corresponding directions
        const int dx[] = {1, 0, -1, 0};
        const int dy[] = {0, 1, 0, -1};

        int x = current - (current / W) * W;
        int y = current / W;

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            int next = nx + ny * W;

            if (canTravel(x, y, dir) && (PARENTS
    [next] == -1)) {
                FRONT.push(next);
                PARENTS
        [next] = current;

                if (dir != 3 && (next / W) == (H - 1)) {
                    target = next;
                }
            }
        }
    }

    vector<int> traverse_;
    unsigned parent = PARENTS[target];
    while (target != 0) {
        int diff = target - parent;

        if (diff == 1) {
            traverse_.push_back(0);
        } else if (diff == static_cast<int>(W)) {
            traverse_.push_back(1);
        } else if (diff == -1) {
            traverse_.push_back(2);
        } else if (diff == static_cast<int>(-W)) {
            traverse_.push_back(3);
        }

        target = parent;
        parent = PARENTS
[parent];
    }
    std::reverse(traverse_.begin(), traverse_.end());
    return traverse_;
}

