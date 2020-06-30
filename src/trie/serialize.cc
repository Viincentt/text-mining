#include "trie.hh"


// Dumping Patricia Trie 
void compile(std::ofstream& out, PTrie root)
{
    out.write(reinterpret_cast<char *>(&root.f), sizeof(root.f));
    auto size = root.children.size();
    out.write(reinterpret_cast<char *>(&size), sizeof(size));
    for (auto& it: root.children) {
        compile(out, it.second);
        auto key = it.first;
        auto keySize = key.size();
        out.write(reinterpret_cast<char *>(&keySize), sizeof(keySize));
        out.write(key.c_str(), keySize);
    }
}

// Loading Patricia Trie
PTrie load(std::ifstream& input)
{
    int freq;
    input.read(reinterpret_cast<char *>(&freq), sizeof(freq));
    PTrie res(freq);
    size_t nb;
    input.read(reinterpret_cast<char *>(&nb), sizeof(nb));
    std::map<std::string, PTrie> m;
    for (size_t i = 0; i < nb; ++i) {
        auto child = load(input);
        size_t keySize;
        input.read(reinterpret_cast<char *>(&keySize), sizeof(keySize));
        std::string key(keySize, '\0');
        input.read(key.data(), keySize);
        m.insert({key, child});
    }
    res.children = m;
    return res;
}