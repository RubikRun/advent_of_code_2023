#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace PartOne {
    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    int fromDigit(char c) {
        return c - '0';
    }

    int getFirstLastDigitNumber(const std::string& str) {
        int firstDigit = -1;
        int lastDigit = -1;
        for (int i = 0; i < str.length(); i++) {
            char c = str[i];
            if (isDigit(c)) {
                firstDigit = fromDigit(c);
                break;
            }
        }
        for (int i = str.length() - 1; i >= 0; i--) {
            char c = str[i];
            if (isDigit(c)) {
                lastDigit = fromDigit(c);
                break;
            }
        }
        return firstDigit * 10 + lastDigit;
    }

    bool solve() {
        std::ifstream file("input01.txt");
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open input file.");
        }

        int sum = 0;
        std::string line;
        while (std::getline(file, line)) {
            sum += getFirstLastDigitNumber(line);
        }
        std::cout << "Answer to part 1 ----> " << sum << std::endl;

        file.close();
        if (file.is_open()) {
            throw std::runtime_error("Cannot close input file.");
        }
        return true;
    }

} // namespace PartOne