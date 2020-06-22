#include "trie.hh"

void trie::add(std::string s, int freq, int i, int len)
{
    if (i == len)
        f = freq;
    else if (i < len) {
        auto nextChar = s[i];
        auto child = children.find(nextChar);
        if (child == children.end()) {
            auto newChild = std::make_shared<trie>();
            children.emplace(nextChar, newChild);
            newChild->add(s, freq, i + 1, len);
        } else
            child->second->add(s, freq, i + 1, len);
    }
}

void trie::print(int i) 
{
    std::cout << "node: " << i << ", children: ";
    for (auto it = children.begin(); it != children.end(); ++it) {
        std::cout << it->first << " ";
    }
    if (f.has_value())
        std::cout << "frequence: " << f.value() << " ";
    std::cout << std::endl;
    for (auto it = children.begin(); it != children.end(); ++it) {
        it->second->print(i + 1);
    }
}

// -------------------
// Constructors 
PTrie::PTrie() 
    : root(std::make_shared<PTrie::Node>()),
    nbWords(0)
{}

PTrie::Node::Node(int freq)
    : f(freq),
    children(std::map<std::string, std::shared_ptr<Node>>())
{}

PTrie::Node::Node() 
    : children(std::map<std::string, std::shared_ptr<Node>>())
{}

// Print
void PTrie::print() {
    root->print(0);
}
void PTrie::Node::print(int i) {
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
    if (f.has_value())
        std::cout << "frequence: " << f.value() << " ";
    std::cout << std::endl;
    for (auto it = children.begin(); it != children.end(); ++it)
        it->second->print(i + 1);
}

// Add
void PTrie::add(std::string s, size_t freq)
{
    nbWords++;
    root->add(s, freq, 0, s.size());
}

void PTrie::Node::add(std::string s, int freq, size_t i, size_t len)
{
    if (i < len)
    {
        std::optional<std::map<std::string, std::shared_ptr<Node>>::iterator> best_fit;
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
                    best_fit.value()->second->add(s, freq, i + keySize, len);
                else
                    best_fit.value()->second->f = freq;
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
                    children[commonFirstPart] = std::make_shared<Node>(freq);
                else
                {
                    children[commonFirstPart] = std::make_shared<Node>();
                    children[commonFirstPart]->children[sSecondPart] = std::make_shared<Node>(freq);
                }
                children[commonFirstPart]->children[branchSecondPart] = oldChild;
            }
        }
        else // No child or no child starting the same way
            children.emplace(s.substr(i), std::make_shared<Node>(freq));
    }
}

// Misc
int PTrie::Node::nbWords(){
    auto res = f.has_value() ? 1 : 0;
    for (auto it = children.begin(); it != children.end(); ++it)
        res += it->second->nbWords();
    return res;
}

bool PTrie::checkNbWords(){
    std::cout << "checking number of words,... ";
    auto gt = nbWords;
    auto predict = root->nbWords();
    if (gt != predict)
    {
        std::cout << "ground truth: " << gt << ", predicted: " << predict << "\n";
        return false;
    }
    std::cout << "oki\n";
    return true;
}

std::shared_ptr<PTrie::Node> PTrie::getRoot() {
    return root;
}