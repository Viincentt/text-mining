#include <iostream>
#include <fstream>
#include "../trie/trie.hh"

void compile(std::ofstream& out, PTrie root)
{
    out.write(reinterpret_cast<char *>(&root.f), sizeof(root.f));
    auto size = root.children.size();
    out.write(reinterpret_cast<char *>(&size), sizeof(size));
    for (auto& it: root.children) {
        auto key = it.first;
        out.write(reinterpret_cast<char *>(&key), sizeof(key));
        compile(out, it.second);
    }
}
PTrie get(std::ifstream& input){
    int freq;
    input.read(reinterpret_cast<char *>(&freq), sizeof(freq));
    PTrie res(freq);
    size_t nb;
    input.read(reinterpret_cast<char *>(&nb), sizeof(nb));
    std::map<std::string, PTrie> m;
    for (size_t i = 0; i < nb; ++i){
        std::string key;
        input.read(reinterpret_cast<char *>(&key), sizeof(key));
        m.insert({key, get(input)});
    }
    res.children = m;
    return res;
}
int main(int argc, char const *argv[])
{
    if (argc != 3)
        return 1;
    
    std::string word;
    int freq;
    auto trie = PTrie();
    
    std::ifstream words(argv[1]);
    while (words >> word && words >> freq) 
        trie.add(word, freq, 0, word.size());
    words.close();
    std::cout << "trie built\n";
    // trie.print(0);
    std::ofstream out(argv[2], std::ios::binary);
    compile(out, trie);
    out.close();
    std::cout << "compile finished\n";
    std::ifstream input(argv[2], std::ios::binary);
    PTrie t = get(input);
    input.close();
    std::cout << "retrieve finished\n";
    t.print(0);
    return 0;
}