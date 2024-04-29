#ifndef DOC_PARSER_H
#define DOC_PARSER_H

#include <istream>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>
#include "AvlTree.h"
#include "Indexer.h"
#include "rapidjson/document.h"
#include "PorterStemmer.h" 

class DocParser {
private:
    struct Doc {
        std::string name;
        std::vector<std::string> terms;
        std::unordered_set<int> objects;
        double ratio = 0.0;

        bool good() const { return true; }
        Doc(std::string n) : name(std::move(n)) {}
    };

    Doc privateDoc;
    Doc currentDoc;

public:
    const std::string WORDS = "TEXT";
    const std::string PERSONS = "PERSONS";
    const std::string ORGS = "ORGANIZATIONS";

    DocParser(const std::string& name);

    std::string& refString(std::string& rString);
    std::string derefString(const std::string& string);

    void parseJSON(const std::string& filename);
    void iterate(const std::string& name);

    std::vector<std::string> tokenize(const std::string& text);
    void stemWords(std::vector<std::string>& words);

};

#endif // DOC_PARSER_H
