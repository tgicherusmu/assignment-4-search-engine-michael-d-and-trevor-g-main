#ifndef INDEXENTRY_H
#define INDEXENTRY_H

#include <utility>
#include<vector>
#include <iostream>
#include<unordered_map>
#include <set>
using namespace std;

class IndexEntry{
private:

    string Word;
    unordered_map<string,int> DocNames;
    set<string>DocNamesSet;
    int numDocs;

public:
    // constructors
    // IndexEntry(string word, const string& docName): Word(std::move(word)){
    IndexEntry(string word, const string& docName){
        DocNames[docName]=1;
    }
    IndexEntry();
    // constructor ONLY for operator==
    explicit IndexEntry(string word): Word(std::move(word)){}
    IndexEntry(string word, const int num): Word(std::move(word)),numDocs(num) {}

    // add doc to DocNames if word exists
    void addDocToIdxEntry(const string&);



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
        os << s.Word<<","<<s.numDocs;
        for(const auto & docName : s.DocNames){
            os<<","<<docName.first<<","<<docName.second;
        }
        os<<endl;
        return os;
    }
    set<string>& getDocNamesSet(){ return DocNamesSet;}
    int getNumDocs() const { return numDocs; }
    //int getCount() const { return count; }
    string getWord(){ return Word;}

    void docNameSetInsert(const string&);
    void docNamesMapInsert(const string&, const int&);

};


#endif
