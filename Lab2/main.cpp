#include <iostream>
#include <curl.h>
#include <conio.h>
#include <json.h>
#include <ctime>
#include "currency.h"

size_t request (const char* in, size_t size, size_t num, std::string& str) {
    size_t newLen = size * num;
    str.append(in, newLen);
    return newLen;
}

void print (double value1, double value2, const CCurrency& output) {
    if (value1 < value2) {
        std::cout << output;
        swapcolor(std::cout, GREEN, "\u2191\n");
    }
    else {
        std::cout << output;
        swapcolor(std::cout, RED, "\u2193\n");
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.cbr-xml-daily.ru/daily_json.js");

    std::string data;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, request);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

    std::string input;
    int interval;
    std::cout << "Enter interval of requests\n";
    std::cin >> input;
    for (long long i = input.size()-1; i >=0; --i) {
        if (input[i] < '0' || input [i] > '9') {
            throw std::invalid_argument("interval can't be non-digit\n");
        }
        interval += (input[i]-'0') * pow(10,input.size()-i-1);
    }
    if (interval == 0) {
        throw std::invalid_argument("interval can't be 0\n");
    }

    std::vector<CCurrency> valutes;
    Json::Value jsonData;
    Json::Reader jsonReader;

    time_t start = time(nullptr);
    time_t now = start + interval;
    while(!kbhit()) {
        if (difftime(now, start) >= interval) {
            start = now;
            curl_easy_perform(curl);

            int code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
            if(code != 200) {
                std::cout << "REQUEST ERROR\n";
                continue;
            }

            jsonReader.parse(data, jsonData);
            int pos = 0;
            if (valutes.empty()) {
                for (const Json::Value &i: jsonData["Valute"]) {
                    valutes.emplace_back(i);
                    print(i["Value"].asDouble(), i["Previous"].asDouble(), valutes.back());
                }
                std::cout << "------------------------------------------------------------------------------\n";
            }
            else {
                for (const Json::Value &i : jsonData["Valute"]) {
                    valutes[pos].push(i);
                    print(i["Value"].asDouble(), i["Previous"].asDouble(), valutes[pos]);
                    ++pos;
                }
                std::cout << "------------------------------------------------------------------------------\n";
            }
        }
        now = time(nullptr);
    }

    for (CCurrency& i : valutes) {
        i.print(std::cout);
    }

    return 0;
}
