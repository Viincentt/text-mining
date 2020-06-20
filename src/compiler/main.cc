#include <iostream>
#include <fstream>
#include "../trie/trie.hh"
int main(int argc, char const *argv[])
{
    /*
    gestion d'args
    open txt file
    creation patricia trie
    binarisation
    todo might leak because of ifstream ???
    */
    if (argc != 3)
        return 1;

    std::ifstream words(argv[1]);
    std::string word;
    int freq;
    auto root = std::make_shared<trie>();
    while (words >> word) {
        words >> freq;
        root->add(word, freq, 0, word.size());
    }
    words.close();
    root->print(0);
    // std::ofstream out(argv[2], std::ios::out | std::ios::binary);
    // TODO binariser l'arbre ???
    return 0;
}