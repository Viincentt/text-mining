#include "trie.hh"

// Loading lightweight patricia trie
FTrie load(std::ifstream& input) {
    int freq;
    size_t nbChildren;
    size_t keySize;
    input.read(reinterpret_cast<char *>(&keySize), sizeof(keySize));
    std::string key(keySize, '\0');
    input.read(key.data(), keySize);
    input.read(reinterpret_cast<char *>(&freq), sizeof(freq));
    input.read(reinterpret_cast<char *>(&nbChildren), sizeof(nbChildren));
    FTrie root(freq, key);
    for (size_t i = 0; i < nbChildren; ++i)
        root.children.push_back(load(input));
    return root;
}

// Dumping Patricia Trie 
void compile(std::ofstream& out, PTrie root, std::string key)
{
    size_t keySize = key.size();
    out.write(reinterpret_cast<char *>(&keySize), sizeof(keySize));
    out.write(key.c_str(), keySize);
    out.write(reinterpret_cast<char *>(&root.f), sizeof(root.f));
    auto nbChildren = root.children.size();
    out.write(reinterpret_cast<char *>(&nbChildren), sizeof(nbChildren));
    for (auto& it: root.children)
        compile(out, it.second, it.first);
}