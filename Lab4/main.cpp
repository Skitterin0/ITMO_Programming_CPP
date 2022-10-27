#include <iostream>
#include <fstream>
#include "cube.h"
#include <map>
#include "algo.h"

int main() {
    std::ifstream fin;

    CCube gan;

    std::cout << "Choose one of the following options:\n"
                 "1) Randomly shuffle Rubik's cube\n"
                 "2) Shuffle cube by yourself\n"
                 "3) Upload shuffle from file\n"
                 "Choose an option:" << std::endl;
    int button;
    std::cin >> button;

    std::cout << "Program's cube language:\n"
                 "Capital letter - rotating related cube's edge clockwise\n"
                 "lowercase letter represents counterclockwise rotation of edge\n"
                 "Capital letter with the square of lowercase letters under it\n"
                 "represents cube's edge as you would put it in front of you\n" << std::endl;

    std::string fileName, seq;

    switch (button) {
        case 1:
            std::cout << "Cube'll be randomly shuffled" << std::endl;
            randomShuffle(gan);
            break;
        case 2:
            std::cout << "Enter sequence of rotates:" <<std::endl;
            std::cin >> seq;
            for (unsigned char i : seq) {
                shuffle(gan, i);
            }
            break;
        case 3:
            std::cout << "Enter file name:" << std::endl;
            std::cin >> fileName;
            fin.open(fileName);
            if (!fin) {
                throw std::invalid_argument("file not found");
            }
            break;
        default:
            throw std::invalid_argument("command not found");
    }

    CAlgorythm solve;

    std::cout << gan;

    solve.whiteCross(gan);

    std::cout << "White cross solved\n" << gan;

    solve.F2L(gan);

    std::cout << gan;

    return 0;
}
