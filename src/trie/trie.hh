#include <string>
#include <map>
#include <optional>
#include <memory>
#include <iostream>

class trie{
    public:
        trie() = default;
        void add(std::string s, int freq, int i, int len);
        void print(int i);
    private:
        std::optional<int> f;
        std::map<char, std::shared_ptr<trie>> children;
};

class PTrie {
    public:
    class Node {
        public:
            Node();
            Node(int freq);
            void add(std::string s, int freq, size_t i, size_t len);
            void print(int i);
            int nbWords();
        private:
            std::optional<int> f;
            std::map<std::string, std::shared_ptr<Node>> children;
    };
    PTrie();
    void add(std::string s, size_t freq);
    void print();
    bool checkNbWords();
    std::shared_ptr<Node> getRoot();
    private:
        std::shared_ptr<Node> root;
        int nbWords;
};