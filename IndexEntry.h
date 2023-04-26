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
//    set<string>DocNamesSet;
//    int numDocs;
    //CODE REVIEW COMMENT: get rid of numDocs and DocNameSet
    //string word;
    //double tf;
    //vector<int> positions;

    // constructors
    // IndexEntry(string word, const string& docName): Word(std::move(word)){
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

//    IndexEntry(const std::string& w, double t, const std::vector<int>& p);
    //std::string getWord() const;
    //double getTF() const;
    //std::vector<int> getPositions() const;

    bool operator< (const IndexEntry& s) const{
        return this->Word < s.Word;
    }
    bool operator> (const IndexEntry& s) const {
        return this->Word > s.Word;
    }
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
    //int getCount() const { return count; }
    string getWord(){ return Word;}

//    void docNameSetInsert(const string&);
    void docNamesMapInsert(const string&, const int&);
    //CODE REVIEW COMMENT: make everything public in class because we already have getters
};


#endif
