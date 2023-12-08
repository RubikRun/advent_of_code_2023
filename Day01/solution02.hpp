#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace PartTwo {
    const int DIGIT_WORDS_COUNT = 9;
    const std::string DIGIT_WORDS[DIGIT_WORDS_COUNT] = {
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    int fromDigit(char c) {
        return c - '0';
    }

    bool compareSubstring(const std::string& str, int beginIdx, const std::string& otherStr) {
        if (str.length() - beginIdx < otherStr.length()) {
            return false;
        }
        for (int i = 0; i < otherStr.length(); i++) {
            if (str[beginIdx + i] != otherStr[i]) {
                return false;
            }
        }
        return true;
    }

    int fromDigitWord(const std::string& str, int beginIdx) {
        for (int digit = 0; digit < DIGIT_WORDS_COUNT; digit++) {
            const std::string& digitWord = DIGIT_WORDS[digit];
            if (compareSubstring(str, beginIdx, digitWord)) {
                return digit + 1;
            }
        }
        return -1;
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
            firstDigit = fromDigitWord(str, i);
            if (firstDigit != -1) {
                break;
            }
        }
        for (int i = str.length() - 1; i >= 0; i--) {
            char c = str[i];
            if (isDigit(c)) {
                lastDigit = fromDigit(c);
                break;
            }
            lastDigit = fromDigitWord(str, i);
            if (lastDigit != -1) {
                break;
            }
        }
        return firstDigit * 10 + lastDigit;
    }

    bool solve() {
        std::ifstream file("input02.txt");
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open input file.");
        }

        int sum = 0;
        std::string line;
        while (std::getline(file, line)) {
            sum += getFirstLastDigitNumber(line);
        }
        std::cout << "Answer to part 2 ----> " << sum << std::endl;

        file.close();
        if (file.is_open()) {
            throw std::runtime_error("Cannot close input file.");
        }
        return true;
    }

} // namespace PartTwo