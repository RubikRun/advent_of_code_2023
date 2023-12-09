#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

namespace PartTwo {

    struct Hand {
        int r = 0;
        int g = 0;
        int b = 0;

        void print(std::ostream& stream) const {
            bool printedSth = false;
            if (r != 0) {
                stream << r << " red";
                printedSth = true;
            }
            if (g != 0) {
                if (printedSth) {
                    stream << ", ";
                }
                stream << g << " green";
                printedSth = true;
            }
            if (b != 0) {
                if (printedSth) {
                    stream << ", ";
                }
                stream << b << " blue";
            }
        }

        int getPower() const {
            return r * g * b;
        }
    };

    typedef Hand Bag;

    struct Game {
        std::vector<Hand> hands;
        int id = -1;

        void print(std::ostream& stream) const {
            stream << "Game " << id << ": ";
            for (int i = 0; i < hands.size(); i++) {
                hands[i].print(stream);
                if (i + 1 < hands.size()) {
                    stream << "; ";
                }
            }
        }

        Bag getMinBag() const {
            Bag bag;
            for (const Hand& hand : hands) {
                bag.r = std::max(bag.r, hand.r);
                bag.g = std::max(bag.g, hand.g);
                bag.b = std::max(bag.b, hand.b);
            }
            return bag;
        }
    };

    struct GameList {
        std::vector<Game> games;

        void print(std::ostream& stream) const {
            for (int i = 0; i < games.size(); i++) {
                games[i].print(stream);
                stream << "\n";
            }
        }

        int getSumOfPowersOfMinBags() const {
            int sum = 0;
            for (const Game& game : games) {
                sum += game.getMinBag().getPower();
            }
            return sum;
        }
    };

    Game readGameFromFile(std::ifstream& file) {
        Game game;
        Hand hand;
        std::string countStr;
        std::string color;
        while (file >> countStr >> color) {
            assert(color.length() >= 3);
            const int count = std::stoi(countStr);
            char endChar = 0;
            if (color.back() == ',' || color.back() == ';') {
                endChar = color.back();
                color.pop_back();
            }

            if (color == "red") {
                assert(hand.r == 0);
                hand.r = count;
            }
            else if (color == "green") {
                assert(hand.g == 0);
                hand.g = count;
            }
            else if (color == "blue") {
                assert(hand.b == 0);
                hand.b = count;
            }
            else {
                assert(false);
            }

            if (endChar == ';') {
                game.hands.push_back(hand);
                hand = Hand();
            }
            else if (endChar == 0) {
                game.hands.push_back(hand);
                break;
            }
        }
        return game;
    }

    GameList readGameListFromFile(std::ifstream& file) {
        GameList gameList;
        std::string gameWord;
        std::string gameIdStr;
        while (file >> gameWord >> gameIdStr) {
            assert(gameWord == "Game");
            assert(gameIdStr.back() == ':');
            gameIdStr.pop_back();
            const int gameId = std::stoi(gameIdStr);

            Game game = readGameFromFile(file);
            game.id = gameId;
            gameList.games.push_back(game);
        }
        return gameList;
    }

    bool solve() {
        std::ifstream file("input.txt");
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open input file.");
        }

        GameList gameList = readGameListFromFile(file);
        std::cout << "Answer to part 2 ----> " << gameList.getSumOfPowersOfMinBags() << std::endl;

        file.close();
        if (file.is_open()) {
            throw std::runtime_error("Cannot close input file.");
        }
        return true;
    }

} // namespace PartTwo