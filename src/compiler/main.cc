#include <iostream>
#include <fstream>
#include "../trie/trie.hh"



int main(int argc, char const *argv[])
{
    if (argc != 3)
        return 1; // TODO gestion d'erreur
    
    std::string word;
    int freq;
    auto trie = PTrie();
    
    std::ifstream words(argv[1]);
    while (words >> word && words >> freq) 
        trie.add(word, freq, 0, word.size());
    words.close();
    std::cout << "trie built\n";
    std::ofstream out(argv[2], std::ios::binary);
    compile(out, trie);
    out.close();
    std::cout << "compile finished\n";
    std::ifstream input(argv[2], std::ios::binary);
    PTrie t = load(input);
    input.close();
    std::cout << "retrieve finished\n";
    t.print(0);
    return 0;
}