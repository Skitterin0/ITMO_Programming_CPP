#ifndef LAB1_GEOMETRY_H
#define LAB1_GEOMETRY_H
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#endif //LAB1_GEOMETRY_H


double Pi = 3.14;

class CPoint {
public:
    double coordX_;
    double coordY_;

    CPoint(double coordX = 0, double coordY = 0) :
            coordX_(coordX), coordY_(coordY) {}

    CPoint(const CPoint &other) = default;

    CPoint& operator=(const CPoint &other) {
        if (&other == this) {
            return *this;
        }
        coordX_ = other.coordX_;
        coordY_ = other.coordY_;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, CPoint &point) {
        out << "[X = " << point.coordX_ << "; " << "Y = " << point.coordY_ << "]\n";

        return out;
    }
};

class CPolyline {
public:
    std::vector<CPoint> points_;

    explicit CPolyline(std::vector<CPoint> points = {{0, 0}, {0, 2}, {2, 2}}) :
            points_(move(points)) {}

    CPolyline(const CPolyline &other) = default;

    CPolyline& operator=(const CPolyline &other) {
        if (&other == this) {
            return *this;
        }

        points_ = other.points_;
        return *this;
    }
};

class CClosedPoly: public CPolyline {
public:
    CClosedPoly() : CPolyline() {
        points_.push_back(CPolyline::points_[0]);
    }

    explicit CClosedPoly(std::vector<CPoint> points) : CPolyline(move(points)) {
        if (&CPolyline::points_[0] != &CPolyline::points_[CPolyline::points_.size()-1]) {
            throw std::invalid_argument("This polyline isn't closed");
        }
    }

    CClosedPoly(const CClosedPoly &other) = default;

    double Perimeter() {
        double perimeter = 0;
        double currX, currY, nextX, nextY;
        for (int i = 0; i < points_.size() - 1; i++) {
            currX = points_[i].coordX_;
            currY = points_[i].coordY_;
            nextX = points_[i + 1].coordX_;
            nextY = points_[i + 1].coordY_;
            perimeter += sqrt(pow(nextX - currX, 2) + pow(nextY - currY, 2));
        }

        return perimeter;
    }
};

class CPolygon {
public:
    std::vector<CPoint> points_;

    explicit CPolygon(std::vector<CPoint> points = {{0,0}, {0,1}, {1,1}}):
            points_(move(points)) {}

    CPolygon(const CPolygon& other) = default;

    CPolygon& operator=(const CPolygon& other) {
        if (&other == this) {
            return *this;
        }

        points_ = other.points_;
        return *this;
    }

    double Perimeter() {
        double perimeter = 0;
        double currX, currY, nextX, nextY;
        for (int i = 0; i < points_.size() - 1; i++) {
            currX = points_[i].coordX_;
            currY = points_[i].coordY_;
            nextX = points_[i + 1].coordX_;
            nextY = points_[i + 1].coordY_;
            perimeter += sqrt(pow(nextX - currX, 2) + pow(nextY - currY, 2));
        }
        currX = points_[0].coordX_;
        currY = points_[0].coordY_;
        perimeter += sqrt(pow(currX - nextX, 2) + pow(currY - nextY, 2));

        return perimeter;
    }

    double Area () {
        double currX, currY, nextX, nextY;
        double result = 0;
        for (int i = 0; i < points_.size() - 1; i++) {
            currX = points_[i].coordX_;
            currY = points_[i].coordY_;
            nextX = points_[i+1].coordX_;
            nextY = points_[i+1].coordY_;
            result += (currX + nextX) * (currY - nextY);
        }
        currX = points_[0].coordX_;
        currY = points_[0].coordY_;
        result += (currX + nextX) * (nextY - currY);

        return fabs(result)/2.0;
    }
};

double VectorCos (CPoint a, CPoint b, CPoint c) {
    double vec1X, vec1Y, vec2X, vec2Y;
    vec1X = b.coordX_ - a.coordX_;
    vec1Y = b.coordY_ - a.coordY_;
    vec2X = c.coordX_ - b.coordX_;
    vec2Y = c.coordY_ - b.coordY_;
    double len1 = sqrt(pow(vec1X,2) + pow(vec1Y,2));
    double len2 = sqrt(pow(vec2X,2) + pow(vec2Y,2));

    return (vec1X*vec2X + vec1Y*vec2Y)/(len1*len2);
}

class CTriangle: public CPolygon {
public:
    CTriangle() : CPolygon() {}

    explicit CTriangle(std::vector<CPoint> points) : CPolygon(move(points)) {
        if (CPolygon::points_.size() != 3) {
            throw std::invalid_argument("It isn't a triangle");
        }
        else {
            bool isTriangle = true;
            if (VectorCos(points_[0], points_[1], points_[2]) == 1) {
                isTriangle = false;
            }
            if (!isTriangle) {
                throw std::invalid_argument("It isn't a triangle");
            }
        }
    }

    CTriangle(const CTriangle& other) = default;

};

class CTrapezoid: public CPolygon {
public:
    CTrapezoid() : CPolygon() {
        points_.emplace_back(1,-1);
    }

    explicit CTrapezoid(std::vector<CPoint> points) : CPolygon(move(points)) {
        if (points_.size() != 4) {
            throw std::invalid_argument("It isn't a trapezoid");
        }
        else {
            int isParallel = 0;
            CPoint a (points_[1].coordX_ - points_[0].coordX_, points_[1].coordY_ - points_[0].coordY_);
            CPoint b (points_[3].coordX_ - points_[2].coordX_, points_[3].coordY_ - points_[2].coordY_);

            if (a.coordX_ * b.coordY_ == a.coordY_ * b.coordX_) {
                isParallel++;

            }

            a = (points_[2].coordX_ - points_[1].coordX_, points_[2].coordY_ - points_[1].coordY_);
            b = (points_[0].coordX_ - points_[3].coordX_, points_[0].coordY_ - points_[3].coordY_);

            if (a.coordX_ * b.coordY_ == a.coordY_ * b.coordX_) {
                isParallel++;

            }

            if (isParallel != 1) {
                throw std::invalid_argument("It isn't a trapezoid");
            }
        }
    }

    CTrapezoid(const CTrapezoid& other) = default;
};

class CRegPoly {
public:
    unsigned int edgeSize_;
    unsigned int rootNumber_;

    explicit CRegPoly (unsigned  int edgeSize = 1, unsigned int rootNumber = 3):
            edgeSize_(edgeSize), rootNumber_(rootNumber) {}

    CRegPoly (const CRegPoly& other) = default;

    CRegPoly& operator=(const CRegPoly& other) {
        if (&other == this) {
            return *this;
        }

        edgeSize_ = other.edgeSize_;
        rootNumber_ = other.rootNumber_;
        return *this;
    }

    double Perimeter () const {
        return (edgeSize_ * rootNumber_);
    }

    double Area() const {
        if (rootNumber_ == 3) {
            return (pow(edgeSize_,2) * sqrt(3) / 4);
        }
        else {
            double ctg = 1 / tanh(Pi / rootNumber_);
            return ((double)rootNumber_ / 4 * pow(edgeSize_, 2) * ctg);
        }
    }
};
