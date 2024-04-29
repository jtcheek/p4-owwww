#include "Indexer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

extern std::vector<std::string> tokenize(const std::string &str);

template<typename Comparable, typename Value>
void Indexer<Comparable, Value>::indexDocument(const std::string& docIdentifier, const std::string& content)
{
    auto words = tokenize(content); 

    for (const auto& word : words)
    {
        insertWord(word, docIdentifier, termIndex); 
    }
}

template<typename Comparable, typename Value>
void Indexer<Comparable, Value>::insertWord(const Comparable& word, const std::string& docIdentifier, 
                                     AvlTree<Comparable, std::vector<std::string>>& index)
{
    if (!index.contains(word)) 
    {
        index.insert(word, std::vector<std::string>{docIdentifier});
    } else 
    {
        auto& documents = index.find(word); 
        if (std::find(documents.begin(), documents.end(), docIdentifier) == documents.end()) {
            documents.push_back(docIdentifier);
        }
    }
}

template<typename Comparable, typename Value>
void Indexer<Comparable, Value>::saveIndex(const AvlTree<Comparable, std::vector<std::string>>& index, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) 
    {
        throw std::runtime_error("Unable to open file for writing.");
    }


    for (auto& node : index) 
    {
        outFile << node.key << ";" << join(node.values, ',') << std::endl;
    }
    outFile.close();
}

template<typename Comparable, typename Value>
void Indexer<Comparable, Value>::loadIndex(AvlTree<Comparable, std::vector<std::string>>& index, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Unable to open file for reading.");
    }

    std::string line;
    while (getline(inFile, line)) {
        auto parts = split(line, ';');
        Comparable key = parts[0];
        std::vector<std::string> values = split(parts[1], ',');
        index.insert(key, values);
    }
    inFile.close();
}

// Explicit template instantiation
template class Indexer<std::string, std::vector<std::string>>;
