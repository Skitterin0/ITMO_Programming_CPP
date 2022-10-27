
#ifndef LAB4_ALGO_H
#define LAB4_ALGO_H

#include "cube.h"

std::string solution;

class CAlgorythm : public CCube {
private:
    std::vector<edge> currOr;

    static void crossOpp(CCube& cube) {
        solution.append("RDDrDDR");
        cube.R();
        cube.D();
        cube.D();
        cube.r();
        cube.D();
        cube.D();
        cube.R();
    }

    static void crossPew(CCube& cube) {
        solution.append("RdrDR");
        cube.R();
        cube.d();
        cube.r();
        cube.D();
        cube.R();
    }

    static void pew(CCube& cube) {
        solution.append("RUru");
        cube.R();
        cube.U();
        cube.r();
        cube.u();
    }

    static void revPew(CCube& cube) {
        solution.append("URur");
        cube.U();
        cube.R();
        cube.u();
        cube.r();
    }

    static void lpew(CCube& cube) {
        solution.append("luLU");
        cube.l();
        cube.u();
        cube.L();
        cube.U();
    }

    static void lrevPew(CCube& cube) {
        solution.append("ulUl");
        cube.u();
        cube.l();
        cube.U();
        cube.L();
    }

    static void FfirstL(CCube& cube, int pos1, int pos2, unsigned char col1, unsigned char col2) {
        while ((cube.GetColor(pos1/100, 1, 1) != col1 || cube.GetColor(pos2/100, 1, 1) != col2) &&
               (cube.GetColor(pos1/100, 1, 1) != col2 || cube.GetColor(pos2/100, 1, 1) != col1)) {
            solution.append("ED");
            cube.E();
            cube.D();
        }
    }

    static void Fsecl(CCube& cube, unsigned char colf, unsigned char colu) {
        while (cube.GetColor(4, 1, 1) != colf) {
            solution.append("ED");
            cube.E();
            cube.D();
        }
    }

public:
    void whiteCross(CCube& cube) {
        currOr = cube.GetOrientation();

        int pos = 0;
        for (int i = 0; i < 6; ++i) {
            if (currOr[i][1][1] == 'w') {
                pos = i;
                break;
            }
        }
//setting the white center down
        if (pos != 0) {
            switch (pos) {
                case 1:
                    solution.append("MM");
                    cube.M();
                    cube.M();
                    break;
                case 2:
                    solution.push_back('s');
                    cube.s();
                    break;
                case 3:
                    solution.push_back('S');
                    cube.S();
                    break;
                case 4:
                    solution.push_back('m');
                    cube.m();
                    break;
                case 5:
                    solution.push_back('M');
                    cube.M();
                    break;
            }
            currOr = cube.GetOrientation();
        }
//creating a white 'cross'
        for (int i = 1; i < 6; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    if (abs(j-k) == 1 && currOr[i][j][k] == 'w') {
                        switch (i) {
                            case 1:
                                while (cube.GetColor(1, 2, 1) != 'w') {
                                    solution.push_back('U');
                                    cube.U();
                                }
                                while (cube.GetColor(0, 0, 1) == 'w') {
                                    solution.push_back('D');
                                    cube.D();
                                }
                                solution.append("FF");
                                cube.F();
                                cube.F();
                                break;
                            case 2:
                                if (j == 2 && k == 1) {
                                    solution.push_back('l');
                                    cube.l();
                                }
                                while (cube.GetColor(0, 1, 0) == 'w') {
                                    solution.push_back('D');
                                    cube.D();
                                }
                                while (cube.GetColor(2, 1, 2) != 'w') {
                                    solution.push_back('L');
                                    cube.L();
                                }
                                solution.append("Df");
                                cube.D();
                                cube.f();
                                break;
                            case 3:
                                if (j == 2 && k == 1) {
                                    solution.push_back('R');
                                    cube.R();
                                }
                                while (cube.GetColor(0, 1, 2) == 'w') {
                                    solution.push_back('D');
                                    cube.D();
                                }
                                while (cube.GetColor(3, 1, 0) != 'w') {
                                    solution.push_back('L');
                                    cube.L();
                                }
                                solution.append("dF");
                                cube.d();
                                cube.F();
                                break;
                            case 4:
                                if (j == 2 && k == 1) {
                                    solution.push_back('F');
                                    cube.F();
                                }
                                while (cube.GetColor(0, 0, 1) == 'w') {
                                    solution.push_back('D');
                                    cube.D();
                                }
                                while (cube.GetColor(4, 1, 0) != 'w') {
                                    solution.push_back('F');
                                    cube.F();
                                }
                                solution.append("dL");
                                cube.d();
                                cube.L();
                                break;
                            case 5:
                                if (j == 2 && k == 1) {
                                    solution.push_back('B');
                                    cube.B();
                                }
                                while (cube.GetColor(0, 2, 1) == 'w') {
                                    solution.push_back('D');
                                    cube.D();
                                }
                                while (cube.GetColor(5, 1, 0) != 'w') {
                                    solution.push_back('B');
                                    cube.B();
                                }
                                solution.append("dR");
                                cube.d();
                                cube.R();
                                break;
                        }
                        i = 1;
                        j = 0;
                        k = 0;
                        currOr = cube.GetOrientation();
                    }
                }
            }
        }

        char trueF = currOr[4][1][1];
        char trueL = currOr[2][1][1];
        char trueR = currOr[3][1][1];
        char trueB = currOr[5][1][1];

        char currF = currOr[4][2][1];
        char currL = currOr[2][2][1];
        char currR = currOr[3][2][1];
        char currB = currOr[5][2][1];

        while (trueF != currF || trueB != currB || trueR != currR || trueL != currL) {

            bool F = (trueF == currF);
            bool L = (trueL == currL);
            bool R = (trueR == currR);
            bool B = (trueB == currB);

            if (F && B && !L) {
                crossOpp(cube);
            }
            else if (L && R && !F) {
                solution.push_back('D');
                cube.D();
                crossOpp(cube);
                solution.push_back('d');
                cube.d();
            }
            else if (F && L && !R) {
                crossPew(cube);
            }
            else if (F && R && !L) {
                solution.push_back('d');
                cube.d();
                crossPew(cube);
                solution.push_back('D');
                cube.D();
            }
            else if (L && B && !R) {
                solution.push_back('D');
                cube.D();
                crossPew(cube);
                solution.push_back('d');
                cube.d();
            }
            else if (B && R && !L) {
                solution.append("DD");
                cube.D();
                cube.D();
                crossPew(cube);
                solution.append("DD");
                cube.D();
                cube.D();
            }
            else {
                solution.push_back('D');
                cube.D();
            }

            currF = cube.GetColor(4, 2, 1);
            currL = cube.GetColor(2, 2, 1);
            currR = cube.GetColor(3, 2, 1);
            currB = cube.GetColor(5, 2, 1);
        }
    }

    void F2L (CCube& cube) {
        //putting white corners in place
        currOr = cube.GetOrientation();
        std::vector<int> nei;

        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 3; j += 2) {
                for (int k = 0; k < 3; k += 2) {
                    if (currOr[i][j][k] == 'w') {
                        nei = cube.GetNeighbours(i, j, k);
                        int pos1 = nei[0];
                        char col1 = cube.GetColor(pos1/100, (pos1/10)%10, pos1%10);
                        int pos2 = nei[1];
                        char col2 = cube.GetColor(pos2/100, (pos2/10)%10, pos2%10);

                        switch (i) {
                            case 0:
                                if (currOr[pos1/100][2][1] == col1 && currOr[pos2/100][2][1] == col2 ||
                                    currOr[pos2/100][2][1] == col1 && currOr[pos1/100][2][1] == col2) {
                                    continue;
                                }

                                switch (pos1/100 + pos2/100) {
                                    case 6:
                                        solution.append("FUf");
                                        cube.F();
                                        cube.U();
                                        cube.f();
                                        break;
                                    case 7:
                                        if (pos1/100 == 3 || pos1/100 == 4) {
                                            solution.append("RUr");
                                            cube.R();
                                            cube.U();
                                            cube.r();
                                        }
                                        else {
                                            solution.append("LUl");
                                            cube.L();
                                            cube.U();
                                            cube.l();
                                        }
                                        break;
                                    case 8:
                                        solution.append("BUb");
                                        cube.B();
                                        cube.U();
                                        cube.b();
                                        break;
                                }
                                break;
                            case 1:
                                while (cube.GetColor(1, 2, 2) != 'w') {
                                    solution.push_back('U');
                                    cube.U();
                                }

                                FfirstL(cube, pos1, pos2, col1, col2);

                                for (int n = 0; n < 3; ++n) {
                                    pew(cube);
                                }

                                break;
                            case 2:
                                switch (j) {
                                    case 0:
                                        switch (k) {
                                            case 0:
                                                solution.append("UU");
                                                cube.U();
                                                cube.U();
                                                FfirstL(cube, pos1, pos2, col1, col2);
                                                pew(cube);
                                                break;
                                            case 2:
                                                FfirstL(cube, pos1, pos2, col1, col2);
                                                lpew(cube);
                                                break;
                                        }
                                        break;
                                    case 2:
                                        switch (k) {
                                            case 0:
                                                solution.append("ED");
                                                cube.E();
                                                cube.D();
                                                lrevPew(cube);
                                                FfirstL(cube, pos1, pos2, col1, col2);
                                                lrevPew(cube);
                                                break;
                                            case 2:
                                                lpew(cube);
                                                FfirstL(cube, pos1, pos2, col1, col2);
                                                lpew(cube);
                                                break;
                                        }
                                        break;
                                }
                                break;
                            case 3:
                                switch (j) {
                                    case 0:
                                        switch (k) {
                                            case 0:
                                                FfirstL(cube, pos1, pos2, col1, col2);
                                                pew(cube);
                                                break;
                                            case 2:
                                                solution.push_back('U');
                                                cube.U();
                                                FfirstL(cube, pos1, pos2, col1, col2);
                                                revPew(cube);
                                                break;
                                        }
                                        break;
                                    case 2:
                                        switch (k) {
                                            case 0:
                                                pew(cube);
                                                FfirstL(cube, pos1, pos2, col1, col2);
                                                pew(cube);
                                                break;
                                            case 2:
                                                solution.append("ed");
                                                cube.e();
                                                cube.d();
                                                revPew(cube);
                                                FfirstL(cube, pos1, pos2, col1, col2);
                                                revPew(cube);
                                                break;
                                        }
                                        break;
                                }
                                break;
                            case 4:
                                switch (j) {
                                    case 0:
                                        switch (k) {
                                            case 0:
                                                FfirstL(cube, pos1, pos2, col1, col2);
                                                lrevPew(cube);
                                                break;
                                            case 2:
                                                FfirstL(cube, pos1, pos2, col1, col2);
                                                revPew(cube);
                                                break;
                                        }
                                        break;
                                    case 2:
                                        switch (k) {
                                            case 0:
                                                lrevPew(cube);
                                                FfirstL(cube, pos1, pos2, col1, col2);
                                                lrevPew(cube);
                                                break;
                                            case 2:
                                                revPew(cube);
                                                FfirstL(cube, pos1, pos2, col1, col2);
                                                revPew(cube);
                                                break;
                                        }
                                        break;
                                }
                                break;
                            case 5:
                                switch (j) {
                                    case 0:
                                        solution.append("UU");
                                        cube.U();
                                        cube.U();
                                        break;
                                    case 2:
                                        solution.append("EDED");
                                        cube.E();
                                        cube.D();
                                        cube.E();
                                        cube.D();
                                        break;
                                }
                                break;
                        }

                        currOr = cube.GetOrientation();
                        i = 0;
                        j = 0;
                        k = 0;
                    }
                }
            }
        }

        //putting 2 layer ribs in place
//        for (int i = 1; i < 6; ++i) {
//            for (int j = 0; j < 3; ++j) {
//                for (int k = 0; k < 3; ++k) {
//                    if (abs(j-k) == 1) {
//                        nei = cube.GetNeighbours(i, j, k);
//                        int pos = nei[0];
//                        char col1 = cube.GetColor(i, j, k);
//                        char col2 = cube.GetColor(pos / 100, (pos / 10) % 10, pos % 10);
//
//                        if (col2 == 'w') {
//                            continue;
//                        }
//
//                        switch (i) {
//                            case 1:
//                                while(cube.GetColor(4, 0, 1) != col2 || cube.GetColor(1, 2, 1) != col1) {
//                                    solution.push_back('U');
//                                    cube.U();
//                                }
//                                Fsecl(cube, col2, col1);
//                                break;
//                            default:
//                                break;
//                        }
//
//                        currOr = cube.GetOrientation();
//                        i = 0;
//                        j = 0;
//                        k = 0;
//                    }
//                }
//            }
//        }
    }
};

#endif
