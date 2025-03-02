#include "WordCount.h"
#include "tddFuncs.h"
#include <iostream>

int main() {
    WordCount wc;

    ASSERT_EQUALS("isn't", wc.makeValidWord("isn't"));
    ASSERT_EQUALS("mother-in-law", wc.makeValidWord("mother-in-law"));
    ASSERT_EQUALS("apple", wc.makeValidWord("...apple***"));
    ASSERT_EQUALS("foo-bar", wc.makeValidWord("foo-bar-"));
    ASSERT_EQUALS("", wc.makeValidWord("-$%#"));

    wc.incrWordCount("foo");
    wc.incrWordCount("Foo"); 
    wc.incrWordCount("bar");
    wc.incrWordCount("BAR"); 
    wc.incrWordCount("foo-bar");
    
    ASSERT_EQUALS(2, wc.getWordCount("foo"));
    ASSERT_EQUALS(2, wc.getWordCount("bar"));
    ASSERT_EQUALS(1, wc.getWordCount("foo-bar"));
    ASSERT_EQUALS(5, wc.getTotalWords());
    ASSERT_EQUALS(3, wc.getNumUniqueWords());

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
