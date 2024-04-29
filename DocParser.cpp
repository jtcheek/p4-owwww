#include "DocParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <rapidjson/document.h>
#include "PorterStemmer.h" 

DocParser::DocParser(const std::string& name) : privateDoc(name), currentDoc(name) {}

void DocParser::parseJSON(const std::string& filename) 
{
    std::ifstream file(filename);
    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
    rapidjson::Document doc;
    doc.Parse(content.c_str());

    if (doc.HasMember("Text") && doc["Text"].IsString()) {
        std::string text = doc["Text"].GetString();
        std::vector<std::string> words = tokenize(text);
        this->removeStopWords(words); // Call the member function on the current instance
        this->stemWords(words);       // Call the member function on the current instance
        // Process words as needed
    }
}

std::string& DocParser::refString(std::string& rString) {
    return rString;
}

std::string DocParser::derefString(const std::string& string) {
    return string;
}

std::vector<std::string> DocParser::tokenize(const std::string& text) 
{
    std::vector<std::string> tokens;
    std::istringstream iss(text);
    std::string token;
    while (iss >> token) {
        
        token.erase(std::remove_if(token.begin(), token.end(), ::ispunct), token.end());
        
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

void DocParser::stemWords(std::vector<std::string>& words) 
{
    PorterStemmer stemmer;
    for (auto& word : words) {
        word = stemmer.stem(word);
    }
}

void DocParser::iterate(const std::string& name) 
{
    std::ifstream file(name);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + name);
    }
    std::string line;
    while (std::getline(file, line)) {
        std::cout << "Processing line: " << line << std::endl;
    }
    file.close();
}

