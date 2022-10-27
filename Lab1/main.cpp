#include <iostream>
#include "polynom.h"
#include "geometry.h"

int main() {
    CPolynom a ({2,-2}); // 2x+2
    CPolynom b ({2,-2}); // x^2+x+1;
    CPolynom c = a/2;
    bool Q = a==b;
    std::cout << a[1];
//    vector<CPoint> vector1 {{0, 0}, {3, 0}, {0, 3}};
//    vector<CPoint> vector2 {{0, 0}, {0, 2}, {2, 2}, {4, 0}};
//    CTriangle tri1(vector1);
//    CClosedPoly cp1;
//    CRegPoly f1;
//    CRegPoly f2 (1, 4);
//    CPolygon p1;
//    CTrapezoid tr1 (vector1);
//    CTrapezoid tra2 (vector2);
//    std::cout << tra2.Area() << '\n';
//    std::cout << f2.Perimeter() << '\n' << f2.Area();
//    CPolygon* figures[5];
//    figures[0] = new CTrapezoid;
//    figures[1] = new CTriangle;
//    std::cout << figures[0]->Area() << ' ' << figures[1]->Perimeter();

    return 0;
}

