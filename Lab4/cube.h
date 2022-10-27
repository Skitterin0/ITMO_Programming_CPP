#ifndef LAB4_CUBE_H
#define LAB4_CUBE_H

#include <vector>
#include <random>
#include <map>

typedef std::vector<char> raw;
typedef std::vector<raw> edge;

/*
 * 0 white
 * 1 yellow
 * 2 blue
 * 3 green
 * 4 red
 * 5 orange
 */

class CCube {
private:
    std::vector<edge> orientation_;
    //0D 1U 2L 3R 4F 5B

    void RotateEdge(int e) {
        edge tmpEdge;
        tmpEdge.assign(3, {0, 0, 0});
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                tmpEdge[j][2-i] = orientation_[e][i][j];
            }
        }
        orientation_[e] = tmpEdge;
    }

    void Rotate(int f, int l, int d, int r, int u) {
        int j;
        if (f == 0 || f == 3) {
            j = 2;
        }
        else {
            j = 0;
        }

        RotateEdge(f);

        if (f == 2 || f ==3) {
            for (int i = 0; i < 3; ++i) {
                char tmpElem = orientation_[l][i][j];
                orientation_[l][i][j] = orientation_[d][i][j];
                orientation_[d][i][j] = orientation_[r][abs(i-2)][abs(j-2)];
                orientation_[r][abs(i-2)][abs(j-2)] = orientation_[u][i][j];
                orientation_[u][i][j] = tmpElem;
            }
        }
        else if (f == 0 || f ==1) {
            for (int i = 0; i < 3; ++i) {
                char tmpElem = orientation_[l][j][i];
                orientation_[l][j][i] = orientation_[d][j][i];
                orientation_[d][j][i] = orientation_[r][j][i];
                orientation_[r][j][i] = orientation_[u][j][i];
                orientation_[u][j][i] = tmpElem;
            }
        }
    }

    const std::vector<int> neighbours_ [6][3][3] = {
            {{{222, 420}, {421}, {320, 422}},
                 {{221}, {}, {321}},
                 {{322, 520}, {521}, {522, 220}}},
            {{{502, 200}, {501}, {500, 302}},
                 {{201}, {}, {301}},
                 {{400, 202}, {401}, {402, 300}}},
            {{{502, 100}, {110}, {400, 120}},
                 {{512}, {}, {410}},
                 {{522, 020}, {010}, {420, 000}}},
            {{{402, 122}, {112}, {500, 102}},
                 {{412}, {}, {510}},
                 {{422, 002}, {012}, {520, 022}}},
            {{{202, 120}, {121}, {122, 300}},
                 {{212}, {}, {310}},
                 {{222, 000}, {001}, {320, 002}}},
            {{{302, 102}, {101}, {100, 200}},
                 {{312}, {}, {210}},
                 {{322, 022}, {021}, {220, 020}}}};

public:
    CCube() {
        orientation_.resize(6);
        const char colors[6] = {'w', 'y', 'b', 'g', 'r', 'o'};


        for (int i = 0; i < 6; ++i) {
            orientation_[i].resize(3);
            for (int j = 0; j < 3; ++j) {
                orientation_[i][j].resize(3);
                for (int k = 0; k < 3; ++k) {
                    orientation_[i][j][k] = colors[i];
                }
            }
        }
    }

    /*
     * or[4][0][0] && or[2][0][2] && or[1][0][2]
     * or[4][2][0] && or[2][2][2] && or[0][0][0]
     * or[4][2][2] && or[3][0][0] && or[1][][]
     * or[4][0][2] && or[3][2][0] && or[0][][]
     *
     * or[5][0][0] && or[3][][] && or[1][][]
     * or[5][2][0] && or[3][][] && or[0][][]
     * or[5][2][2] && or[2][][] && or[1][][]
     * or[5][0][2] && or[2][][] && or[0][][]
     *
     *
     *
     */


    CCube(std::vector<edge>& orientation) :
        orientation_(std::move(orientation)) {
            std::map<char, char[2]> corner;
            int rib[6][6] = {{-60,-60,0,0,0,0},
                           {-60,-60,0,0,0,0},
                           {0,0,-60,-60,0,0},
                           {0,0,-60,-60,0,0},
                           {0,0,0,0,-60,-60},
                           {0,0,0,0,-60,-60}};

            int count [] = {0, 0, 0, 0, 0, 0};

            for (int i = 0; i < 6; ++i) {
                ++count[orientation_[i][1][1]];
            }

            for (int i = 2; i < 6; ++i) {
                for (int j = 0; j < 3; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        if (abs(j-k) == 1) {

                        }
                    }
                }
            } //ribs

            for (int i = 4; i < 6; ++i) {
                for (int j = 0; j <3; j += 2) {
                    for (int k = 0; k < 3; k += 2) {

                    }
                }
            } //corners
        }

    ~CCube() = default;

//    void Z() {
//        edge tmp = orientation_[4];
//        orientation_[4] = orientation_[3];
//        orientation_[3] = orientation_[5];
//        orientation_[5] = orientation_[2];
//        orientation_[2] = tmp;
//        RotateEdge(1);
//        for (int i = 0; i < 3; ++i) {
//            RotateEdge(0);
//        }
//    }

    void R() {
        Rotate(3, 4, 0, 5, 1);
    }

    void r() {
        for (int i = 0; i < 3; ++i) {
            R();
        }
    }

    void L() {//поменять
        Rotate(2, 4, 1, 5, 0);
    }

    void l() {
        for (int i = 0; i < 3; ++i) {
            L();
        }
    }

    void U() {
        Rotate(1, 2, 4, 3, 5);
    }

    void u() {
        for (int i = 0; i < 3; ++i) {
            U();
        }
    }

    void D() {
        Rotate(0, 5, 3, 4, 2);
    }

    void d() {
        for (int i = 0; i < 3; ++i) {
            D();
        }
    }

    void F() {
        //Rotate(4, 2, 0, 3, 1);

        RotateEdge(4);

        for (int i = 0; i < 3; ++i) {
            char tmpElem = orientation_[2][i][2];
            orientation_[2][i][2] = orientation_[0][0][i];
            orientation_[0][0][i] = orientation_[3][2-i][0];
            orientation_[3][2-i][0] = orientation_[1][2][2-i];
            orientation_[1][2][2-i] = tmpElem;
        }
    }

    void f() {
        for (int i = 0; i < 3; ++i) {
            F();
        }
    }

    void B() {
//        //Rotate(5, 3, 0, 2, 1);

        RotateEdge(5);

        for (int i = 0; i < 3; ++i) {
            char tmpElem = orientation_[3][i][2];
            orientation_[3][i][2] = orientation_[0][2][2-i];
            orientation_[0][2][2-i] = orientation_[2][2-i][0];
            orientation_[2][2-i][0] = orientation_[1][0][i];
            orientation_[1][0][i] = tmpElem;
        }
    }

    void b() {
        for (int i = 0; i < 3; ++i) {
            B();
        }
    }

    void M() { //между L и R
        for (int i = 0; i < 3; ++i) {
            char tmpElem = orientation_[4][i][1];
            orientation_[4][i][1] = orientation_[0][i][1];
            orientation_[0][i][1] = orientation_[5][abs(i-2)][1];
            orientation_[5][abs(i-2)][1] = orientation_[1][i][1];
            orientation_[1][i][1] = tmpElem;
        }
    }

    void m() {
        for (int i = 0; i < 3; ++i) {
            M();
        }
    }

    void S() {
        for (int i = 0; i < 3; ++i) {
            char tmpElem = orientation_[1][1][i];
            orientation_[1][1][i] = orientation_[2][abs(i-2)][1];
            orientation_[2][abs(i-2)][1] = orientation_[0][1][abs(i-2)];
            orientation_[0][1][abs(i-2)] = orientation_[3][i][1];
            orientation_[3][i][1] = tmpElem;
        }

    }//между F и B

    void s() {
        for (int i = 0; i < 3; ++i) {
            S();
        }
    }

    void E() {
        for (int i = 0; i < 3; ++i) {
            char tmpElem = orientation_[4][1][i];
            orientation_[4][1][i] = orientation_[3][1][i];
            orientation_[3][1][i] = orientation_[5][1][i];
            orientation_[5][1][i] = orientation_[2][1][i];
            orientation_[2][1][i] = tmpElem;
        }

    }//между U и D

    void e() {
        for (int i = 0; i < 3; ++i) {
            E();
        }
    }

    [[nodiscard]] const std::vector<edge>& GetOrientation() const {
        return orientation_;
    };

    [[nodiscard]] char GetColor(int i, int j, int k) const {
        return orientation_[i][j][k];
    };

    [[nodiscard]] std::vector<int> GetNeighbours (int i, int j, int k) {
        return neighbours_[i][j][k];
    };

    friend std::ostream& operator<<(std::ostream& out, CCube& cube) {
        out << " D \t U \t L \t R \t F \t B" << std::endl;
        std::vector<edge> orientation = cube.GetOrientation();

        for (int k = 0; k < 3; ++k) {
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 3; ++j) {
                    out << orientation[i][k][j];
                }
                out << '\t';
            }
            out << std::endl;
        }

        out << std::endl;
        return out;
    };
};

void shuffle(CCube& cube, unsigned char num) {
    switch (num) {
        case 'R':
            cube.R();
            break;
        case 'r':
            cube.r();
            break;
        case 'L':
            cube.L();
            break;
        case 'l':
            cube.l();
            break;
        case 'U':
            cube.U();
            break;
        case 'u':
            cube.u();
            break;
        case 'D':
            cube.D();
            break;
        case 'd':
            cube.d();
            break;
        case 'F':
            cube.F();
            break;
        case 'f':
            cube.f();
            break;
        case 'B':
            cube.B();
            break;
        case 'b':
            cube.b();
            break;
        case 'M':
            cube.M();
            break;
        case 'm':
            cube.m();
            break;
        case 'S':
            cube.S();
            break;
        case 's':
            cube.s();
            break;
        case 'E':
            cube.E();
            break;
        case 'e':
            cube.e();
            break;
        default:
            break;
    }
}

void randomShuffle(CCube& cube) {
    char move [] = {'R', 'r', 'L', 'l', 'U', 'u',
                    'D', 'd', 'F', 'f', 'B', 'b',
                    'M', 'm', 'S', 's', 'E', 'e'};

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 18);

    for (int i = 0; i < 16; ++i) {
        int a = dist(mt);
        shuffle(cube, move[a]);
    }
}

#endif