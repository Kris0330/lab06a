#include "WordCount.h"
#include <vector>
#include <cctype>   // for std::tolower
#include <algorithm> // for std::find_if

using namespace std;

// Default constructor
WordCount::WordCount() {
    // table 是固定大小的陣列，不需要 resize()
}

// Hash function (已給定，不可更改)
size_t WordCount::hash(std::string word) const {
    size_t accumulator = 0;
    for (size_t i = 0; i < word.size(); i++) {
        accumulator += word.at(i);
    }
    return accumulator % CAPACITY;
}

// 判斷是否為有效單詞字元 (a-z, A-Z, 0-9)
bool WordCount::isWordChar(char c) {
    return isalnum(c); // 只允許字母與數字
}

// 轉換單詞成標準格式（全部轉小寫，只保留有效字元）
std::string WordCount::makeValidWord(std::string word) {
    string result = "";
    for (char c : word) {
        if (isWordChar(c)) {
            result += tolower(c); // 轉小寫
        }
    }
    return result;
}

// 增加單詞次數 (若存在則 +1，不存在則新增)
int WordCount::incrWordCount(std::string word) {
    word = makeValidWord(word);
    if (word.empty()) return 0; // 空字串則不處理

    size_t index = hash(word); // 取得 hash index
    for (auto& pair : table[index]) {
        if (pair.first == word) {
            pair.second++; // 若單詞已存在則 +1
            return pair.second;
        }
    }

    // 若單詞不存在，新增到 table[index]
    table[index].push_back(make_pair(word, 1));
    return 1;
}

// 取得單詞次數 (若不存在回傳 0)
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

// 取得所有單詞的總次數
int WordCount::getTotalWords() const {
    int total = 0;
    for (const auto& bucket : table) {
        for (const auto& pair : bucket) {
            total += pair.second; // 累加所有出現次數
        }
    }
    return total;
}

// 取得唯一單詞的數量
int WordCount::getNumUniqueWords() const {
    int count = 0;
    for (const auto& bucket : table) {
        count += bucket.size(); // 每個 bucket 內的單詞數量
    }
    return count;
}

// 減少單詞計數 (若單詞存在則 -1，若減至 0 則刪除)
int WordCount::decrWordCount(std::string word) {
    word = makeValidWord(word);
    if (word.empty()) return -1;

    size_t index = hash(word);
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->first == word) {
            it->second--; // 計數 -1
            if (it->second <= 0) {
                table[index].erase(it); // 若減到 0 則刪除
                return 0;
            }
            return it->second;
        }
    }
    return -1; // 若找不到該單詞則回傳 -1
}

