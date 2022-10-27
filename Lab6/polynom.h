#ifndef LAB6_POLYNOM_H
#define LAB6_POLYNOM_H

#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

#endif

template<typename ARRAY>
class CPolynom;

template<class T, int size_>
class CPolynom<T[size_]> {
private:
    T coef_[size_];

public:

    constexpr long long calculate(const int x) const {
        unsigned int degree = size_-1;
        long long result = 0;

        for (int i = 0; i < size_; ++i) {
            result += coef_[i] * pow(x, degree--);
        }

        return result;
    }

    constexpr explicit CPolynom(T other[size_]) {
        for(int i = 0; i < size_; ++i) {
            coef_[i] = other[i];
        }
    }

    constexpr CPolynom(const CPolynom& other) = default;

    constexpr CPolynom& operator=(const CPolynom& other) {
        if (&other == this) {
            return *this;
        }

        coef_ = other.coef_;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, CPolynom& polynom) {
        unsigned long degree = size_-1;
        int isEmpty = true;
        for (unsigned long i = 0; i < size_; ++i) {
            if (isEmpty) {
                switch (degree) {
                    case 0:
                        if (polynom.coef_[i] == 0) {
                            --degree;
                            continue;
                        }
                        else if (polynom.coef_[i] == 1) {
                            out << "1";
                        }
                        else if (polynom.coef_[i] == -1) {
                            out << "-1";
                        }
                        else {
                            if (polynom.coef_[i] > 0) {
                                out << polynom.coef_[i];
                            }
                            else {
                                out << polynom.coef_[i];
                            }
                        }
                        break;
                    case 1:
                        if (polynom.coef_[i] == 0) {
                            --degree;
                            continue;
                        }
                        else if (polynom.coef_[i] == 1) {
                            out << "x" << " ";
                        }
                        else if (polynom.coef_[i] == -1) {
                            out << "-x" << " ";
                        }
                        else {
                            if (polynom.coef_[i] > 0) {
                                out << polynom.coef_[i] << "x ";
                            }
                            else {
                                out << polynom.coef_[i] << "x ";
                            }
                        }
                        break;
                    default:
                        if (polynom.coef_[i] == 0) {
                            --degree;
                            continue;
                        }
                        else if (polynom.coef_[i] == 1) {
                            out << "x^" << degree-- << " ";
                        }
                        else if (polynom.coef_[i] == -1) {
                            out << "-x^" << degree-- << " ";
                        }
                        else {
                            out << polynom.coef_[i] << "x^" << degree-- << " ";
                        }
                        break;
                }
                isEmpty = false;
            }
            else {
                if (i == size_-2) {
                    if (polynom.coef_[i] == 0) {
                        continue;
                    }
                    else if (polynom.coef_[i] == 1) {
                        out << "+x" << " ";
                    }
                    else if (polynom.coef_[i] == -1) {
                        out << "-x" << " ";
                    }
                    else {
                        if (polynom.coef_[i] > 0) {
                            out << "+" << polynom.coef_[i] << "x ";
                        }
                        else {
                            out << polynom.coef_[i] << "x ";
                        }
                    }
                }
                else if (i == size_-1) {
                    if (polynom.coef_[i] == 0) {
                    }
                    else if (polynom.coef_[i] == 1) {
                        out << "+1";
                    }
                    else if (polynom.coef_[i] == -1) {
                        out << "-1";
                    }
                    else {
                        if (polynom.coef_[i] > 0) {
                            out << "+" << polynom.coef_[i];
                        }
                        else {
                            out << polynom.coef_[i];
                        }
                    }
                }
                else {
                    if (polynom.coef_[i] == 0) {
                        degree--;
                    }
                    else if (polynom.coef_[i] == 1) {
                        out << "+x^" << degree-- << " ";
                    }
                    else if (polynom.coef_[i] == -1) {
                        out << "-x^" << degree-- << " ";
                    }
                    else {
                        if (polynom.coef_[i] > 0) {
                            out << "+" << polynom.coef_[i] << "x^" << degree-- << " ";
                        }
                        else {
                            out << polynom.coef_[i] << "x^" << degree-- << " ";
                        }
                    }
                }
            }
        }

        out << std::endl;
        return out;
    }

    int operator[](const unsigned long index) {
        if (index < size_) {
            return coef_[index];
        }
        else {
            throw std::invalid_argument("list index out of range");
        }
    }
};