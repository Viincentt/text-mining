#include <iostream>
#include <fstream>
#include <err.h>
#include "../trie/trie.hh"



int main(int argc, char const *argv[])
{
    if (argc < 3 )
        errx(1, "Usage ./TextMiningApp /path/to/dict.bin");
    std::string word;
    int freq;
    auto trie = PTrie();
    
    std::ifstream words(argv[1]);
    while (words >> word && words >> freq) 
        trie.add(word, freq, 0, word.size());
    words.close();
    std::ofstream out(argv[2], std::ios::binary);
    compile(out, trie, std::string(""));
    out.close();
    return 0;
}