#include "WordCount.h"
#include "tddFuncs.h"
#include <iostream>

int main() {
    WordCount wc;

    wc.incrWordCount("apple");
    wc.incrWordCount("Apple"); 
    wc.incrWordCount("banana");

    ASSERT_EQUALS(2, wc.getWordCount("apple"));
    ASSERT_EQUALS(1, wc.getWordCount("banana"));
    ASSERT_EQUALS(3, wc.getTotalWords());
    ASSERT_EQUALS(2, wc.getNumUniqueWords());

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
