#include <string>
#include <map>
#include <iostream>
#include <fstream>

class PTrie {
public:
    PTrie();
    PTrie(int freq);
    void add(std::string s, int freq, size_t i, size_t len);
    void print(int i) const;
    int f;
    std::map<std::string, PTrie> children;
};

void compile(std::ofstream& out, PTrie root);
PTrie load(std::ifstream& input);
