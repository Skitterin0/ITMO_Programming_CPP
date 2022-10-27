#ifndef LAB2_CURRENCY_H
#define LAB2_CURRENCY_H

#include <vector>
#include <string>
#include <json.h>
#include <algorithm>
#include <cmath>
#include <windows.h>

enum color{
    BROWN = 6,
    WHITE = 7,
    GREEN = 10,
    RED = 12
};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void swapcolor (std::ostream& stream, color newColor, const std::string& str) {
    SetConsoleTextAttribute(hConsole, newColor);
    stream << str;
    SetConsoleTextAttribute(hConsole, WHITE);
}

static void conversion (std::ostream& stream, const std::string& str, const std::string& name, double value) {
    stream << str;
    swapcolor(stream, BROWN, name);
    stream << " is " << value << "\n";
}

class CCurrency {
private:
    const std::string abb_;
    std::vector<double> values_;

public:
    explicit CCurrency(const Json::Value& curr):
    abb_(curr["CharCode"].asString())
    {
        push(curr);
    }

    void push(Json::Value curr) {
        int precision = 1000;
        values_.push_back(round(curr["Value"].asDouble()/curr["Nominal"].asDouble() * precision) / precision);
    }

    [[nodiscard]] double median () const{
        std::vector<double> tmp = values_;
        std::nth_element(tmp.begin(), tmp.begin() + (int)(tmp.size()/2), tmp.end());
        double result;

        switch (tmp.size() % 2) {
            case 1:
                result = tmp[tmp.size()/2];
                break;
            default:
                double first = tmp[tmp.size()/2];
                std::nth_element(tmp.begin(), tmp.begin() + (int)(tmp.size()/2 - 1), tmp.end());
                result = (first + tmp[tmp.size()/2 - 1])/2;
                break;
        }

        return result;
    }

    [[nodiscard]] double avg () const{
        double result = 0;
        for (double i : values_) {
            result += i;
        }

        return result/(double)values_.size();
    }

    friend const std::ostream& operator<<(std::ostream& out,const CCurrency& curr) {
        out << "1 ";
        swapcolor(out, BROWN, curr.abb_);
        out << " equals to " << curr.values_.back();
        swapcolor(out, BROWN, " RUB ");
        return out;
    }

    void print (std::ostream& stream) {
        conversion(stream, "Average value of ", abb_, avg());
        conversion(stream, "Median value of ", abb_, median());
        stream << "\n";
    }
};
#endif
