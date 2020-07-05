#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

class FTrie {
    public:
        FTrie(int freq, std::string key);
        void print(int i) const;
        int freq;
        std::string key;
        std::vector<FTrie> children;
};
class PTrie {
public:
    PTrie();
    PTrie(int freq);
    void add(std::string s, int freq, size_t i, size_t len);
    void print(int i) const;
    int f;
    std::map<std::string, PTrie> children;
};

FTrie load(std::ifstream& input);
void compile(std::ofstream& out, PTrie root, std::string key);
