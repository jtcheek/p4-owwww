#ifndef INDEXER_H
#define INDEXER_H

#include "AvlTree.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

template<typename Comparable, typename Value>
class Indexer
{
private:
    AvlTree<Comparable, std::vector<std::string>> termIndex;
    AvlTree<Comparable, std::vector<std::string>> orgIndex;
    AvlTree<Comparable, std::vector<std::string>> personIndex;

public:
    Indexer() {}

    void indexDocument(const std::string& docIdentifier, const std::string& content);

    void insertWord(const Comparable& word, const std::string& docIdentifier, 
                    AvlTree<Comparable, std::vector<std::string>>& index);

    void displayIndex(const AvlTree<Comparable, std::vector<std::string>>& index) const;

    void saveIndex(const AvlTree<Comparable, std::vector<std::string>>& index, 
                   const std::string& filename);

    void loadIndex(AvlTree<Comparable, std::vector<std::string>>& index, const std::string& filename);
};

#endif // INDEXER_H
