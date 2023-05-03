#include "QueryEngine.h"
#include "porter2_stemmer.h"
#include <iostream>
#include <string.h>

using namespace std;

//changeWord takes a string called word as its argument and sets the class variable Word to this value, then calls the function getStemmedWord
void QueryEngine::changeWord(const string&word){
    Word = word;
    getStemmedWord();
}
//function getStemmedWord ges the getStemmedWord of the word stoed in the class varibale word it first trims this word by removing any non alphabetic charccter and converts all alphabetsic character sto lowercase using the porter libarry
string QueryEngine::getStemmedWord() {
    // get stemmed version of word
    Porter2Stemmer::trim(Word);
    Porter2Stemmer::stem(Word);
    return Word;
}
