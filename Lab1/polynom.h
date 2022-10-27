#ifndef LAB1_POLYNOM_H
#define LAB1_POLYNOM_H
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#endif //LAB1_POLYNOM_H

class CPolynom {
public:
    explicit CPolynom(std::vector<double> coefs = {0}):
            coef_(move(coefs)) {}

    CPolynom(const CPolynom& other) = default;

    CPolynom& operator=(const CPolynom& other) {
        if (&other == this) {
            return *this;
        }

        coef_ = other.coef_;
        return *this;
    }

    bool operator==(const CPolynom& other) {
        if (coef_.size() != other.coef_.size()) {
            return false;
        }
        else {
            for (unsigned long i = 0; i < coef_.size(); i++) {
                if (coef_[i] != other.coef_[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    bool operator!=(const CPolynom& other) {
        return !operator==(other);
    }

    CPolynom operator+(const CPolynom& other) {
        CPolynom result;
        result.coef_.resize(fmax(coef_.size(), other.coef_.size()));
        unsigned long start = 0;

        if (coef_.size() > other.coef_.size()) {
            for (unsigned long i = 0; i < coef_.size() - other.coef_.size(); i++) {
                result.coef_[i] = coef_[i];
                ++start;
            }
            for (unsigned long i = 0; i < other.coef_.size(); i++) {
                result.coef_[i+start] = coef_[i+start] + other.coef_[i];
            }
        }
        else {
            for (unsigned long i = 0; i < other.coef_.size() - coef_.size(); i++) {
                result.coef_[i] = other.coef_[i];
                ++start;
            }
            for (unsigned long i = 0; i < coef_.size(); i++) {
                result.coef_[i+start] = coef_[i] + other.coef_[i+start];
            }
        }
        return result;
    }

    CPolynom& operator+=(const CPolynom& other) {
        if (coef_.size() > other.coef_.size()) {
            unsigned long diff = coef_.size() - other.coef_.size();
            for (unsigned long i = 0; i < other.coef_.size(); i++) {
                coef_[i+diff] += other.coef_[i];
            }
        }
        else {
            unsigned long diff = other.coef_.size() - coef_.size();
            std::vector<double> tmp = coef_;
            coef_.resize(other.coef_.size());
            for (unsigned long i = 0; i < diff; i++) {
                coef_[i] = other.coef_[i];
            }
            for (unsigned long i = 0; i < coef_.size() - diff; i++) {
                coef_[i+diff] = other.coef_[i+diff] + tmp[i];
            }
        }
        return *this;
    }

    CPolynom operator+() {
        return *this;
    }

    CPolynom operator-(const CPolynom& other) {
        CPolynom result;
        result.coef_.resize(fmax(coef_.size(), other.coef_.size()));
        unsigned long start = 0;
        if (coef_.size() > other.coef_.size()) {
            for (unsigned long i = 0; i < coef_.size() - other.coef_.size(); i++) {
                result.coef_[i] = coef_[i];
                ++start;
            }
            for (unsigned long i = 0; i < other.coef_.size(); i++) {
                result.coef_[i+start] = coef_[i+start] - other.coef_[i];
            }
        }
        else {
            for (unsigned long i = 0; i < other.coef_.size() - coef_.size(); i++) {
                result.coef_[i] = -other.coef_[i];
                ++start;
            }
            for (unsigned long i = 0; i < coef_.size(); i++) {
                result.coef_[i+start] = coef_[i] - other.coef_[i+start];
            }
        }
        return result;
    }

    CPolynom& operator-=(const CPolynom& other) {
        if (coef_.size() > other.coef_.size()) {
            unsigned long diff = coef_.size() - other.coef_.size();
            for (unsigned long i = 0; i < coef_.size(); i++) {
                coef_[i+diff] -= other.coef_[i];
            }
        }
        else {
            unsigned long diff = other.coef_.size() - coef_.size();
            std::vector<double> tmp = coef_;
            coef_.resize(other.coef_.size());
            for (unsigned long i = 0; i < diff; i++) {
                coef_[i] = -other.coef_[i];
            }
            for (unsigned long i = 0; i < coef_.size() - diff; i++) {
                coef_[i+diff] = tmp[i] - other.coef_[i+diff];
            }
        }
        return *this;
    }

    CPolynom operator-() {
        for (unsigned long i = 0; i < coef_.size(); i++) {
            coef_[i] = -coef_[i];
        }
        return *this;
    }

    CPolynom operator*(const CPolynom& other) {
        CPolynom result;
        result.coef_.resize(coef_.size() + other.coef_.size() - 1);

        for (unsigned long i = 0; i < coef_.size(); i++) {
            for (unsigned long j = 0; j < other.coef_.size(); j++) {
                result.coef_[i+j] = coef_[i] * other.coef_[j];
            }
        }
        return result;
    }

    CPolynom& operator*=(const CPolynom& other) {
        std::vector<double> result;
        result.resize(coef_.size() + other.coef_.size() - 1);

        for (unsigned long i = 0; i < coef_.size(); i++) {
            for (unsigned long j = 0; j < other.coef_.size(); j++) {
                result[i+j] = coef_[i] * other.coef_[j];
            }
        }

        coef_ = result;
        return *this;
    }

    CPolynom operator*(double number) {
        CPolynom result;
        result.coef_.resize(coef_.size());
        for (unsigned long i = 0; i < coef_.size(); i++) {
            result.coef_[i] = coef_[i] * number;
        }

        return result;
    }

    CPolynom& operator*=(double number) {
        for (unsigned long i = 0; i < coef_.size(); i++) {
            coef_[i] *= number;
        }

        return *this;
    }

    CPolynom operator/(double number) {
        CPolynom result ({coef_[0]/number});
        for (unsigned long i = 1; i < coef_.size(); i++) {
            result.coef_.push_back(coef_[i]/number);
        }

        return  result;
    }

    CPolynom& operator/=(double number) {
        for (unsigned long i = 0; i < coef_.size(); i++) {
            coef_[i]/=number;
        }

        return  *this;
    }

    friend std::ostream& operator<<(std::ostream& out, CPolynom& polynom) {
        unsigned long degree = polynom.coef_.size()-1;
        int isEmpty = true;
        for (unsigned long i = 0; i < polynom.coef_.size(); i++) {
            switch (isEmpty) {
                case 1:
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
                    break;
                case 0:
                    if (i == polynom.coef_.size()-2) {
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
                    else if (i == polynom.coef_.size()-1) {
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
                    break;
            }
        }

        out << '\n';
        return out;
    }

    friend std::istream& operator>>(std::istream& in, CPolynom& polynom) {
        polynom.coef_.clear();
        std::cout << "Enter the max degree of your polynom\n";
        int size;
        in >> size;
        std::cout << "Enter your polynom\n";
        for (unsigned long i = 0; i < size+1; i++) {
            char ch;
            in >> ch;
            if (ch > 47 && ch < 58) {
                polynom.coef_.push_back(ch-48);
            }
        }
        return in;
    }

    double operator[](const unsigned long index) {
        if (index < coef_.size()) {
            return coef_[index];
        }
        else {
            throw std::invalid_argument("list index out of range");
        }
    }

private:
    std::vector<double> coef_;
};

