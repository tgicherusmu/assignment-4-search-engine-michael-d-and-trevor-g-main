#ifndef _PORTER2_STEMMER_H_
#define _PORTER2_STEMMER_H_

#include <vector>
#include <string>
#include "../util/string_view.h"

namespace Porter2Stemmer
{
void stem(std::string& word);

void trim(std::string& word);

namespace internal
{
size_t firstNonVowelAfterVowel(const std::string& word, size_t start);

size_t getStartR1(const std::string& word);

size_t getStartR2(const std::string& word, size_t startR1);

void changeY(std::string& word);

void step0(std::string& word);

bool step1A(std::string& word);

void step1B(std::string& word, size_t startR1);

void step1C(std::string& word);

void step2(std::string& word, size_t startR1);

void step3(std::string& word, size_t startR1, size_t startR2);

void step4(std::string& word, size_t startR2);

void step5(std::string& word, size_t startR1, size_t startR2);

inline bool isShort(const std::string& word);

bool special(std::string& word);

bool isVowel(char ch);

bool isVowelY(char ch);

bool endsWith(meta::util::string_view word, meta::util::string_view str);

bool endsInDouble(const std::string& word);

bool replaceIfExists(std::string& word, meta::util::string_view suffix,
                     meta::util::string_view replacement, size_t start);

bool isValidLIEnding(char ch);

bool containsVowel(const std::string& word, size_t start, size_t end);
}
}

#endif