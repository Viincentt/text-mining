#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include "../trie/trie.hh"

int DLevenshtein(std::string anchor, std::string test) {
    auto anchorSize = anchor.size();
    auto testSize = test.size();
    // TODO boost matrix
    std::vector<std::vector<int>> d(anchorSize + 1, std::vector<int>(testSize + 1));
    for (size_t i = 0; i <= anchorSize; ++i)
        d[i][0] = i;
    for (size_t j = 0; j <= testSize; ++j)
        d[0][j] =j;
    for (size_t i = 0; i < anchorSize; ++i) {
        for (size_t j = 0; j < testSize; ++j) {
            auto cost = anchor[i] == test[j] ? 0 : 1;
            d[i + 1][j + 1] = std::min(
                                    std::min(1 + d[i][j + 1], 
                                             1 + d[i + 1][j]),
                                    cost + d[i][j]);
            if (i > 0 && j > 0 && anchor[i] == test[j - 1] && anchor[i - 1] == test[j])
                d[i + 1][j + 1] = std::min(d[i + 1][j + 1],
                                           1 + d[i - 1][j - 1]);
        }
    }
    return d[anchorSize][testSize];
}

void rec(const PTrie& root, const std::string& s, const int& dist, std::map<int, std::map<int, std::set<std::string>>>& m, std::string cur) {
    if (root.f != -1) {
        auto d = DLevenshtein(s, cur);
        if (d <= dist)
            m[d][root.f].emplace(cur);
    }
    for (const auto& elt: root.children)
        rec(elt.second, s, dist, m, cur + elt.first);
}

std::map<int, std::map<int, std::set<std::string>>> findWords(const PTrie& root, const std::string& s, const int& dist) {
    std::map<int, std::map<int, std::set<std::string>>> res;
    rec(root, s, dist, res, ""); 
    return res;
}

void print(std::map<int, std::map<int, std::set<std::string>>> res) {

    std::cout << "[";
    if (res.size() >= 1) {
        auto dist = res.begin();
        auto freq = dist->second.rbegin();
        auto word = freq->second.begin();
        std::cout << "{\"word\":\"" << *word << "\",\"freq\":" << freq->first << ",\"distance\":" << dist->first << "}"; 
        freq->second.erase(word);
    }
    for (const auto& dist: res) {
        for (auto freq = dist.second.rbegin(); freq != dist.second.rend(); ++freq) {
            for (const auto& word: freq->second) {
                std::cout << ",{\"word\":\"" << word << "\",\"freq\":" << freq->first << ",\"distance\":" << dist.first << "}"; 
            }
        }
    }
    std::cout << "]\n";
}

int main(int argc, char const *argv[])
{
    if (argc != 2) // TODO gestion d'erreur
        return 1;

    auto input = std::ifstream(argv[1]);
    const PTrie t = load(input);

    std::string approx;
    int dist;
    std::string word;

    for (; std::cin >> approx && approx == "approx" && std::cin >> dist && std::cin >> word;) {
        dist = dist >= 0 ? dist : 0;
        print(findWords(t, word, dist));
    }
    return 0;
}
