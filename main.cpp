#include <iostream>
#include <vector>
#include <algorithm>


class Earth {

public:
    Earth() {};
    Earth(const int r) : radius(r) {

        grid = new cell*[2*radius+1];
        for(int i = 0; i <= 2*radius; ++i)
            grid[i] = new cell[2*radius+1];

        for (int y = - radius; y <= radius; ++y) {
            for (int x = - radius; x <= radius; ++x) {
                cell c(x, y, false);
                if ( (x*x + y*y) < radius*radius ) {
                    c.alive = true;
                    cellInventory.push_back(c);
                }
                //std::cout << c.y << " " << c.x << " " << c.alive << std::endl;
                grid[y+radius][x+radius] = c;
            }
        }
    };

    struct cell {
        cell() {};
        cell(int x, int y, bool alive) : x(x), y(y), alive(alive) {};
        int x, y;
        bool alive;
    };

    cell getCell(int x, int y) { return grid[y][x]; }

    void setCell(int x, int y, bool alive) {
        grid[y+radius][x+radius].alive = alive;
    }

    void killCell(int x, int y) {
        setCell(x, y, false);
        for(std::vector<Earth::cell>::iterator it = cellInventory.begin(); it < cellInventory.end(); ++it) {
            if (it->x == x && it->y == y ) {
                cellInventory.erase(it);
                break;
            }
        }
    }

    void show() {
        for (int y = - radius; y <= radius; ++y) {
            for (int x = - radius; x <= radius; ++x) {
                std::cout << grid[y+radius][x+radius].alive << " ";
            }
            std::cout << std::endl;
        }
        /*for (auto &c : cellInventory) {
            std::cout << c.y << " " << c.x << " " << c.alive << std::endl;
        }*/
    }

    const int radius = 0;
    cell** grid;
    std::vector<cell> cellInventory;
};

class creature : public Earth {
    cell location;
};


int main() {

    Earth e(4);
    e.killCell(0, 0);
    e.show();

    return 0;
}
