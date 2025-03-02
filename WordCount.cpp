#include "WordCount.h"
#include <vector>
#include <cctype>  
using namespace std;

WordCount::WordCount() {
    for (size_t i = 0; i < CAPACITY; i++) {
        table[i] = vector<pair<string, int>>();
    }
}

size_t WordCount::hash(std::string word) const {
    size_t accumulator = 0;
    for (size_t i = 0; i < word.size(); i++) {
        accumulator += word.at(i);
    }
    return accumulator % CAPACITY;
}

bool WordCount::isWordChar(char c) {
    return isalnum(c) || c == '-' || c == '\'';
}

std::string WordCount::makeValidWord(std::string word) {
    string result = "";
    bool hasLetter = false;  

    for (size_t i = 0; i < word.size(); i++) {
        char c = word[i];
        if (isalnum(c)) {
            result += tolower(c);
            hasLetter = true;
        } else if ((c == '-' || c == '\'') 
                   && hasLetter 
                   && i + 1 < word.size() 
                   && isalnum(word[i + 1])) {
           
            result += c;
        }
    }

    return result;
}

int WordCount::incrWordCount(std::string word) {
    word = makeValidWord(word);
    if (word.empty()) return 0; 

    size_t index = hash(word); 
    for (auto& pair : table[index]) {
        if (pair.first == word) {
            pair.second++; 
            return pair.second;
        }
    }

    table[index].push_back(make_pair(word, 1));
    return 1;
}

int WordCount::getWordCount(std::string word) const {
    word = makeValidWord(word);
    if (word.empty()) return 0;

    size_t index = hash(word);
    for (const auto& pair : table[index]) {
        if (pair.first == word) {
            return pair.second;
        }
    }
    return 0;
}

int WordCount::getTotalWords() const {
    int total = 0;
    for (const auto& bucket : table) {
        for (const auto& pair : bucket) {
            total += pair.second;
        }
    }
    return total;
}

int WordCount::getNumUniqueWords() const {
    int count = 0;
    for (const auto& bucket : table) {
        count += bucket.size();
    }
    return count;
}

int WordCount::decrWordCount(std::string word) {
    word = makeValidWord(word);
    if (word.empty()) return -1;

    size_t index = hash(word);
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->first == word) {
            it->second--; 
            if (it->second <= 0) {
                table[index].erase(it);
                return 0;
            }
            return it->second;
        }
    }
    return -1; 
}


