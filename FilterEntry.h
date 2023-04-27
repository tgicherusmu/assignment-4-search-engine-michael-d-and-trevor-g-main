//
// Created by Trevor Gicheru on 4/26/23.
//

#ifndef FILTERENTRY_H
#define FILTERENTRY_H

#include<string>
#include<iostream>
#include<unordered_set>
using namespace std;

class FilterEntry{
public:
    string name;
    unordered_set<string> uuidSet;

    FilterEntry()=default;
    FilterEntry(const string& Name, const string& uuid){
        name = Name;
        uuidSet.emplace(uuid);
    };

    bool operator< (const FilterEntry& s) const{
        return this->name < s.name;
    }
    bool operator> (const FilterEntry& s) const {
        return this->name > s.name;
    }
    bool operator== (const FilterEntry& s) const {
        return this->name == s.name;
    }

    friend std::ostream& operator<< (std::ostream&os, const FilterEntry&s){
        os << s.name<<","<<s.uuidSet.size();
        for(const auto & docName : s.uuidSet){
            os<<","<<docName;
        }
        os<<endl;
        return os;
    }
};

#endif