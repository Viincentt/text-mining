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
    auto trie = std::make_shared<PTrie>();
    while (words >> word) {
        words >> freq;
        trie->add(word, freq);
    }
    words.close();
    // trie->print();
    // trie->checkNbWords();
    // std::cout << "Size of Structure: " << sizeof(*(trie->getRoot())) << "\n";
    // std::ofstream out(argv[2], std::ios::out | std::ios::binary);
    // TODO binariser l'arbre ???
    return 0;
}