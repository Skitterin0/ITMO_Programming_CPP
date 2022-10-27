#ifndef LAB4_COLOR_H
#define LAB4_COLOR_H

/*
 * 0 white
 * 1 yellow
 * 2 blue
 * 3 green
 * 4 red
 * 5 orange
 */

class CColor {
private:
    int edgeNum;
public:
    float red;
    float green;
    float blue;

    CColor();

    void SetNum(int n) {
        edgeNum = n;
        switch (n) {
            case 0:
                red = 1.0f;
                green = 1.0f;
                blue = 1.0f;
                break;
            case 1:
                red = 1.0f;
                green = 1.0f;
                blue = 0.0f;
                break;
            case 2:
                red = 0.0f;
                green = 0.0f;
                blue = 1.0f;
                break;
            case 3:
                red = 0.0f;
                green = 1.0f;
                blue = 0.0f;
                break;
            case 4:
                red = 1.0f;
                green = 0.0f;
                blue = 0.0f;
                break;
            case 5:
                red = 1.0f;
                green = 0.5f;
                blue = 0.0f;
                break;
        }
    }

    int GetNum() const{
        return edgeNum;
    }
};

#endif //LAB4_COLOR_H
