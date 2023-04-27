#ifndef INDEXENTRY_H
#define INDEXENTRY_H

#include <utility>
#include<vector>
#include <iostream>
#include<unordered_map>
#include <set>
using namespace std;

class IndexEntry{
public:

    string Word;
    unordered_map<string,int> uuidMap;

    IndexEntry(string word, const string& docName, int count = 1){
        Word = word;
        uuidMap[docName]=count;
    }
    IndexEntry();

    // constructor ONLY for operator==
    explicit IndexEntry(string word): Word(word){}
//    IndexEntry(string word, const int num): Word(std::move(word)),numDocs(num) {}

    // add doc to DocNames if word exists
    void addDocToIdxEntry(const string&);


//operator< takes an IndexEntry called s as its argument and returns  true true if this InexEntry's Word field is less than s's word field
    bool operator< (const IndexEntry& s) const{
        return this->Word < s.Word;
    }
//operator> takes an IndexEntry called s as its argument and returns true if this IndexEntry's word field is greater than s's word field
    bool operator> (const IndexEntry& s) const {
        return this->Word > s.Word;
    }
//second method called operator== takes an IndexEntry called s as its argument returns true if indexentry's word field is less than s's word field
    bool operator== (const IndexEntry& s) const {
        return this->Word == s.Word;
    }

    friend std::ostream& operator<< (std::ostream&os, const IndexEntry&s){
        os << s.Word<<","<<s.uuidMap.size();
        for(const auto & docName : s.uuidMap){
            os<<","<<docName.first<<","<<docName.second;
        }
        os<<endl;
        return os;
    }

    set<string> getDocNamesSet(){
        set<string> DocNamesSet;
        for (auto& item: uuidMap) {
            DocNamesSet.emplace(item.first);
        }
        return DocNamesSet;
    }

    int getNumDocs() const { return uuidMap.size(); }
    string getWord(){ return Word;}
    void docNamesMapInsert(const string&, const int&);
};
#endif