#include <string>
#include <map>
#include <optional>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
/*
class pTrie{
    public:
        pTrie(std::string s);
        pTrie(std::string s, int f);
        void add(std::string s, int f, int i, int len);
        std::string s;
        int freq;
        std::vector<std::shared_ptr<pTrie>> children;
};
*/

class PTrie {
public:
    PTrie();
    PTrie(int freq);
    void add(std::string s, int freq, size_t i, size_t len);
    void print(int i);
    int f;
    std::map<std::string, PTrie> children;
};
void compile(std::ofstream& out, PTrie root);
PTrie load(std::ifstream& input);