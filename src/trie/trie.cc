#include "trie.hh"

// -------------------
// Constructors 
PTrie::PTrie(int freq)
    : f(freq),
    children(std::map<std::string, PTrie>())
{}

PTrie::PTrie() 
    : f(-1),
    children(std::map<std::string, PTrie>())
{}

// Print
void PTrie::print(int i) const {
    for (auto j = 0; j < i; ++j)
        std::cout << "    ";
    if (children.size() > 0)
    {
        std::cout << "children: ";
        for (auto it = children.begin(); it != children.end(); ++it)
        {
            std::cout << it->first << " ";
        }
    }
    if (f != -1)
        std::cout << "frequence: " << f << " ";

    std::cout << std::endl;
    for (auto it = children.begin(); it != children.end(); ++it)
        it->second.print(i + 1);
}

// Add
void PTrie::add(std::string s, int freq, size_t i, size_t len)
{
    if (i < len)
    {
        std::optional<std::map<std::string, PTrie>::iterator> best_fit;
        for (auto it = children.begin(); it != children.end() && !best_fit.has_value(); ++it)
        {
            if (it->first[0] == s[i])
                best_fit = it;
        }
        if (best_fit.has_value())
        {
            auto keySize = best_fit.value()->first.size();
            if (s.substr(i, keySize) == best_fit.value()->first) // matching branch is fully contained in the inserting word
            {
                if (i + keySize < len)
                    best_fit.value()->second.add(s, freq, i + keySize, len);
                else
                    best_fit.value()->second.f = freq;
            } else {
                size_t k = 1;
                for (; i + k - 1 < len && k < keySize && s.substr(i, k) == best_fit.value()->first.substr(0, k); ++k);
                --k;
                auto commonFirstPart = s.substr(i, k);
                auto branchSecondPart = best_fit.value()->first.substr(k);
                auto sSecondPart = s.substr(i + k);
                
                auto handler = children.extract(best_fit.value()->first);
                handler.key() = commonFirstPart;
                children.insert(std::move(handler));

                auto oldChild = children[commonFirstPart];
                if (sSecondPart == "")
                    children[commonFirstPart] = PTrie(freq);
                else
                {
                    children[commonFirstPart] = PTrie();
                    children[commonFirstPart].children[sSecondPart] = PTrie(freq);
                }
                children[commonFirstPart].children[branchSecondPart] = oldChild;
            }
        }
        else // No child or no child starting the same way
            children.emplace(s.substr(i), PTrie(freq));
    }
}
