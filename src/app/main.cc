#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <err.h>
#include "../trie/trie.hh"

// Damerau-Levenshtein
int DLevenshtein(const std::string& anchor, const std::string& test) {
    auto anchorSize = anchor.size();
    auto testSize = test.size();
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

// DFS of Patricia trie
void rec(const FTrie& root, const std::string& s, const int& dist, std::map<int, std::map<int, std::set<std::string>>>& m, const std::string& cur) {
    if (root.freq != -1) {
        auto d = DLevenshtein(s, cur);
        if (d <= dist)
            m[d][root.freq].emplace(cur);
    }
    for (const auto& elt: root.children)
        rec(elt, s, dist, m, cur + elt.key);
}

std::map<int, std::map<int, std::set<std::string>>> findWords(const FTrie& root, const std::string& s, const int& dist) {
    std::map<int, std::map<int, std::set<std::string>>> res;
    for (const auto &child : root.children)
        rec(child, s, dist, res, child.key);
    return res;
}

void recOneWord(const FTrie& root, const std::string& s, size_t i) {
    if (i >= s.size()) {
        std::cout << "[{\"word\":\"" << s << "\",\"freq\":" << root.freq << ",\"distance\":0}]";
        return;
    }
    for (const auto& child: root.children) {
        auto size = child.key.size();
        if (child.key == s.substr(i, size))
            recOneWord(child, s, i + size);
    }
}

// Print result as json
void print(std::map<int, std::map<int, std::set<std::string>>> res)
{
    std::cout << "[";
    if (res.size() >= 1)
    {
        auto dist = res.begin();
        auto freq = dist->second.rbegin();
        auto word = freq->second.begin();
        std::cout << "{\"word\":\"" << *word << "\",\"freq\":" << freq->first << ",\"distance\":" << dist->first << "}";
        freq->second.erase(word);
    }
    for (const auto &dist : res)
    {
        for (auto freq = dist.second.rbegin(); freq != dist.second.rend(); ++freq)
        {
            for (const auto &word : freq->second)
                std::cout << ",{\"word\":\"" << word << "\",\"freq\":" << freq->first << ",\"distance\":" << dist.first << "}";
        }
    }
    std::cout << "]\n";
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
        errx(1, "Usage ./TextMiningApp /path/to/dict.bin");

    auto input = std::ifstream(argv[1], std::ios::binary);
    const FTrie t = load(input);
    input.close();
    std::string approx;
    int dist;
    std::string word;
    size_t size;

    for (; std::cin >> approx && approx == "approx" && std::cin >> dist && std::cin >> word;) {
        if (dist != 0) {
            print(findWords(t, word, dist)); 
        } else {
            for (const auto& child: t.children) {
                size = child.key.size();
                if (child.key == word.substr(0, size))
                    recOneWord(child, word, size);
            }
        }
    }
    return 0;
}
